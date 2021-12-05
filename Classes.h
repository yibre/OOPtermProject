#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include "Language.h" // 현주는 여기 cpp

using namespace std;

class Account;
class ATM;
class User;
class Bank;
class Bill;

/***********************	Abstract	***********************/

class NamedObj {
private:
	string name;
	string name_EN;
public:
	NamedObj(string name, string name_EN) : name(name), name_EN(name_EN) {}
	string getName(bool isKor = true) { if (isKor) return name; else return name_EN; }
};

/***********************	Database	***********************/

// 쓸 수 있으면 map 쓰는게 제일 좋을듯
class Database {
private:
	Account* accountList[100]; // 계좌 리스트
	static Translation* languagePack;
	static int listsize;
	static Database* instance; // 한 번만 생성되는 instance
	static vector<vector<string> > atmhisEN; // atm 어드민이 볼 수 있는 거래 내역
	static vector<vector<string> > atmhisKR;
	static vector<vector<string> > sessionhisEN; // 세션 종료 후 유저가 받는 내역
	static vector<vector<string> > sessionhisKR;
	static bool sessionProceeding; // 세션이 진행 중일땐 false임
	static int transactionOrder;
	static int totalSessionNum; // 한 세션이 시작된 후 몇 번의 거래가 이루어졌는가, clearSessionHistory에서 사용
	static int currentOrderNum;
public:
	Database() {};
	virtual ~Database() {};
	static Database* getInstance() {
		if (!instance) { instance = new Database(); }
		return instance;
	}
	void addAccountList(Account*);
	Account* getAccountByNum(int index);
	void addATMHistory(int type, int before, int after, Account* acc, Account* receiver, int transferAmount, int ATMremainBill, int* atmCashNum); // receiver 대신에 toAcc 쓰면 통일성 더 좋을것같다 (-현주)
	void addSessionHistory(string type, int before, int after, Account* acc, Account* receiver, int transferAmount);
	vector<vector<string> > getATMHistoryKR() { return atmhisKR; }
	vector<vector<string> > getATMHistoryEN() { return atmhisEN; }
	void printATMHistory();
	bool isHistoryEmpty() { if (atmhisKR.size() == 0) { return true; } else { return false; } }
	void printSessionHistory();
	void sizeincrease() { listsize++; };
	int getDatabaseSize() { return listsize; };
	int getIndexFromID(int); // 계좌번호 받아서 index return
	void clearSessionHistory();
	void changeLanguage(string Lang) {
		this->languagePack->changeLanguage(Lang);
	}
};

/***********************	  User  	***********************/

class User : public NamedObj {
private:
public:
	User(string name, string name_EN) : NamedObj(name, name_EN) {}
};

/***********************	  Bill  	***********************/

class Bill {
private:
	int paperCash[4];
	static int value[4];
	//Translation* languagePack = new Translation();
public:
	Bill(int c50k, int c10k, int c5k, int c1k);
	//~Bill() { delete languagePack; }
	int getTotalNum();
	int getSum();
	int* getCashNumArray() { return paperCash; }
	void printBill(bool isKor);
	// Bill& operator+(const Bill& bill);
	Bill& operator+=(const Bill& rhs);
	// Bill& operator-(const Bill& bill);
	Bill& operator-=(const Bill& rhs);
	// Bill& operator*(int mul);
	bool operator<=(const Bill& bill);
	bool operator>=(const Bill& bill);
	bool operator<(const Bill& bill);
	bool operator>(const Bill& bill);
};

/***********************	  Bank  	***********************/

class Bank : public NamedObj {
private:
public:
	Bank(string name, string name_EN) : NamedObj(name, name_EN) {}
};

/***********************	Account 	***********************/

class Account {
private:
	Database* database;
	int ID; // ID는 0부터 시작해 1씩 늘려감, 순수 숫자(계좌번호)
	static int numID; // 어떤 ID를 부여할것인가
	Bank* ownerBank;
	User* owner;
	int password; // password는 순수 integer 구성, 카드와 동일
	int balance; // 잔액

public:
	Account();
	Account(Bank* bank, User* owner, int pw, int balance);
	~Account() {}
	int getID() { return ID; } // 계좌번호를 return
	bool checkPassword(int); // int 타입의 패스워드를 받아 해당 패스워드가 맞는지 확인
	void changeBalance(int money);
	int getBalance() { return balance; }
	Bank* getBank() { return ownerBank; }
	User* getOwner() { return owner; }
	bool isPrimary(ATM*);
};

/***********************	  ATM   	***********************/

class ATM {
private:
	Database* database;
	int ID;
	static int numID;
	Bank* ownerBank;
	string adminID;
	int adminpw;
	int remainCheck = 0; // atm 내부 수표 총액
	int remainCheckNum = 0; // atm 내부 수표 갯수
	int maxWithdrawal = 300000;
	int maxCashNumber = 100;
	bool engSupport;
	bool multiBank;
	Bill* remainBill;
	Translation* languagePack;

public:
	// ATM() { numID = 0; }
	ATM(Bank* bank, string adminID, int adminPW, Bill* bill, int check, bool engSupport, bool multiBank);
	~ATM() { delete languagePack; }
	// bool checkID(char); // 쓰이는 곳 현재 없음
	bool deposit(int type, Bill money, int check[], int checkNum, int checkSum, Account* acc); // 입금함수, 입금액 (type1 : 현금 type2 : 수표)
	bool withdrawal(Bill money, Account* acc); // 출금함수, 출금액
	bool checkPW(int);
	bool transfer(int type, int money, Account* fromAcc, Account* toAcc, Bill& bill); // int fee 없애는거 고려
	// void IncreaseID() { numID++; }
	// int getNumID() { return numID; } // ???
	int getID() { return ID; } // 이 ATM의 ID를 return
	int getATMremainCash() { return remainBill->getSum(); }
	int getATMremainCheckNum() { return remainCheckNum; }
	void insertCash(Bill cash) { *this->remainBill += cash; }
	int fee(int, Account*, Account*);
	void printATMremainCashNum() { this->remainBill->printBill(this->languagePack->isKor()); };
	bool compareBill(Bill subject) { return (*(this->remainBill) >= subject); }
	Bank* getBank() { return ownerBank; }
	bool isMultiBank() { return multiBank; }
	bool isEnglishSupport() { return engSupport; }
	void changeLanguage(string Lang) { this->languagePack->changeLanguage(Lang); }
	Bill insertedBill = Bill{ 0,0,0,0 }; // 함수 아니고 변수임; 현재 투입구에 계류중인 현금
};

/*******************	Other Functions 	*******************/

bool checkExit(string); // ?
#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <map>

using namespace std;

class Account;
class ATM;
class User;
class Bank;
class Bill;


/***********************	Database	***********************/

// 쓸 수 있으면 map 쓰는게 제일 좋을듯
class Database {
private:
	Account* accountList[100]; // 계좌 리스트
	static int listsize;
	static Database* instance; // 한 번만 생성되는 instance
	static vector<vector<string> > atmhis; // atm 어드민이 볼 수 있는 거래 내역
	static vector<vector<string> > sessionhis; // 세션 종료 후 유저가 받는 내역
	static bool sessionEnd; // 세션이 진행 중일땐 false임
	static int transactionOrder;
public:
	Database() {};
	virtual ~Database() {};
	static Database* getInstance() {
		if (!instance) { instance = new Database(); }
		return instance;
	}
	void addAccountList(Account*);
	Account* getAccountByNum(int index);
	// void addATMHistory(string transactionType, int money, Account* account, Account* recieverAcc);
	vector<vector<string> > getATMHistory() { return atmhis; }
	vector<vector<string> > getSessionHistory() { return sessionhis; }
	void addHistory(string, int, Account*, Account*);
	void printHistory();
	// void printATMHistory();
	void sizeincrease() { listsize++; };
	int getDatabaseSize() { return listsize; };
	int getIndexFromID(int);
	// void printSessionHistory();
	void clearSessionHistory();
};

/***********************	  User  	***********************/

class User {
private:
	string ID; // user는 U1, U2, U3 이렇게 시작
	string name;

public:
	User() { ID = "U0"; name = "john doe"; }
	User(string ID, string name) { this->ID = ID; this->name = name; }
	~User() {};
	string getUserName() { return name; }
};

/***********************	  Bank  	***********************/

class Bank {
private:
	string ID; // bank는 B1, B2, B3 이렇게 시작
	static int addID; // 0부터 시작해서 1씩 증가
	string name;
	Account* accountlist[100];

public:
	Bank() { ID = "B1"; name = "uriBank"; }
	Bank(string name) { this->name = name; }
	~Bank() { };
	string getBankName() { return name; }
};

/***********************	Account 	***********************/

class Account { // Bank와 User를 상속해도 될듯
private:
	Database* database;
	int ID; // ID는 0부터 시작해 1씩 늘려감, 순수 숫자(계좌번호?)
	static int numID; // 어떤 ID를 부여할것인가
	Bank* ownerBank;
	User* owner;
	int password; // password는 순수 integer 구성, 카드와 동일
	int balance; // 잔액

public:
	Account();
	Account(Bank* bank, User* owner, int pw, int balance);
	~Account() {}
	int getID() { return ID; }
	bool checkPassword(int); // int 타입의 패스워드를 받아 해당 패스워드가 맞는지 확인
	void deposit(int type, int money); // 입금, 입금액 타입(캐시, 수표) 입금액 인풋,};
	void remittance(int, int); // 송금 계좌번호, 액수 <- transfer로 이름 바꾸는거 건의(현주)
	void withdrawal(int money); // 출금
	void changeBalance(int money);
	void increaseID() { numID++; }
	int getNumID() { return numID; }
	int getBalance() { return balance; }
	Bank* getBank() { return ownerBank; }
	User* getOwner() { return owner; }
	bool isPrimary(ATM*);
};

/***********************	  ATM   	***********************/

class ATM { // Bank를 상속해도 될듯
private:
	string ID; // atm은 A1 A2 A3 이렇게 시작
	static int numID; // id 부여용 넘버, 0부터 시작해서 1씩 증가
	Bank* ownerBank;
	string adminID;
	int adminpw;
	int remainCash; // atm 내부 현금 총액; Bill.sum()으로 대체해보기
	int remainCheck = 0; // atm 내부 수표 총액
	int remainCheckNum = 0; // atm 내부 수표 갯수
	int maxWithdrawal = 300000;
	int maxCashNumber = 100;
	bool engSupport;
	Bill* remainBill;

public:
	ATM() { numID = 0; }
	ATM(Bank* bank, string adminID, int adminPW, int cash, int check, bool engSupport);
	~ATM() {}
	bool checkID(char);
	bool checkpw(int);
	bool deposit(int type, int money, int paperNum, Account* acc); // 입금함수, 입금액 (type1 : 현금 type2 : 수표)
	bool withdrawal(int money, Account* acc); // 출금함수, 출금액
	bool transfer(int type, int money, Account* fromAcc, Account* toAcc); // int fee 없애는거 고려
	void IncreaseID() { numID++; }
	int getNumID() { return numID; }
	int getATMremainCash() { return remainCash; }
	int getATMremainCheckNum() { return remainCheckNum; }
	int insertCash(int cash) { remainCash += cash; return remainCash; } // 이걸로 통일할까? 아니면 void로 분화?
	int fee(int, Account*, Account*);
	Bank* getBank() { return ownerBank; }
};

/***********************	  Bill  	***********************/

class Bill {
private:
	int b1k = 0; // 천원권
	int b5k = 0; // 오천원권
	int b10k = 0; // 만원권
	int b50k = 0; // 오만원권
	// check도 액수 안다면 넣을 수 있다(현금들 기본 0으로 하고 check수만 넣는 C'tor)

public:
	Bill() {}
	Bill(int n1k, int n5k, int n10k, int n50k);
	// Bill(const Bill& rhs); // copy C'tor (필요한가?)
	int sum();
	void acceptCash() {/*구현필요*/ } // 현금 투입시
	// 멤버변수 하나라도 0 안 되게 하기
	void withdraw(/*구현필요*/) {/*구현필요*/ } // 출금시

};

/*******************	Other Functions 	*******************/

bool checkExit(string); // ?
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


// 쓸 수 있으면 map 쓰는게 제일 좋을듯
class Database {
private:
	Account* accountList[100]; // 계좌 리스트
	static int listsize;
	static Database* instance; // 한 번만 생성되는 instance
	vector<vector<string> > atmhis; // atm 어드민이 볼 수 있는 거래 내역
	vector<vector<string> > sessionhis; // 세션 종료 후 유저가 받는 내역

public:
	Database() {};
	virtual ~Database() {};
	static Database* getInstance() {
		if (!instance) { instance = new Database(); }
		return instance;
	}
	void addAccountList(Account*);
	void sizeincrease() { listsize++; };
	int getDatabaseSize() { return listsize; };
	int getIndexFromID(int);
	Account* getAccountByNum(int index);

	// history 를 보관하는 2d 어레이
	/*

		Account* getAccountByNum(int index) {
		cout << "this come from a get account by num fun" << endl;
		return accountList[index];
	} // 계좌번호로 account pointer를 가져옴
	number	username	userid	거래타입(입출송)	거래계좌id	상대계좌id	거래액수	거래전잔액	거래후잔액	날짜
	----------------------
	1		김수한무		3		송금				1			3			
	----------------------
	2		거북이와두루미	4		출금 			7			NULL		10
	-----------------------
	3
	*/
};

class User {
private:
	string ID; // user는 U1, U2, U3 이렇게 시작
	string name;

public:
	User() { ID = "U0"; name = "john doe"; }
	User(string ID, string name) { this->ID = ID; this->name = name; }
	~User() {};
	string getName() { return name; }
};

class Bank {
private:
	string ID; // bank는 B1, B2, B3 이렇게 시작
	static int addID; // 0부터 시작해서 1씩 증가
	string name;
	Account* accountlist[100];
	// primary 여부 필요할듯(수수료 관련) (현주)

public:
	Bank() { ID = "B1"; name = "uriBank"; }
	Bank(string name) { this->name = name; }
	~Bank() { };
	string getBankName() { return name; }
};

class Account {
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
	bool checkPassward(int); // int 타입의 패스워드를 받아 해당 패스워드가 맞는지 확인
	void deposit(int type, int money); // 입금, 입금액 타입(캐시, 수표) 입금액 인풋,};
	void remittance(int, int); //송금 계좌번호, 액수 <- transfer로 이름 바꾸는거 건의(현주)
	void withdrawal(int money); // 출금
	void increaseID() { numID++; }
	int getNumID() { return numID; }
	int getBalance() { return balance; }
	Bank* getBank() { return ownerBank; }
	User* getOwner() { return owner; }
};

class ATM {
private:
	string ID; // atm은 A1 A2 A3 이렇게 시작
	static int numID; // id 부여용 넘버, 0부터 시작해서 1씩 증가
	Bank* ownerBank;
	string adminID;
	int adminpw;
	int remainCash; // atm 내부 현금 총액
	int remainCheck = 0; // atm 내부 수표 총액
	int remainCheckNum = 0; // atm 내부 수표 갯수
	int maxWithdrawal = 300000;
	int maxCashNumber = 100;
	bool engSupport;

public:
	ATM() { numID = 0; }
	ATM(Bank* bank, string adminID, int adminPW, int cash, int check, bool engSupport);
	~ATM() {}
	bool checkID(char);
	bool checkpw(int);
	bool deposit(int type, int money, int paperNum, Account* acc); // 입금함수, 입금액 (type1 : 현금 type2 : 수표)
	bool withdrawal(int money, Account* acc); // 출금함수, 출금액
	bool transfer(int money, Account* fromAcc, Account* toAcc);
	void IncreaseID() { numID++; }
	int getNumID() { return numID; }
	int getATMremainCash() { return remainCash; }
	int getATMremainCheckNum() { return remainCheckNum; }
	int insertCash(int cash) { remainCash += cash; return remainCash; } // 이걸로 통일할까? 아니면 void로 분화?
	Bank* getBank() { return ownerBank; }
};

bool checkExit(string);
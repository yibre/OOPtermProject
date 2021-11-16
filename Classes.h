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

// �� �� ������ map ���°� ���� ������
class Database {
private:
	Account* accountList[100]; // ���� ����Ʈ
	static int listsize;
	static Database* instance; // �� ���� �����Ǵ� instance
	static vector<vector<string> > atmhis; // atm ������ �� �� �ִ� �ŷ� ����
	static vector<vector<string> > sessionhis; // ���� ���� �� ������ �޴� ����
	static bool sessionEnd; // ������ ���� ���϶� false��
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
	string ID; // user�� U1, U2, U3 �̷��� ����
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
	string ID; // bank�� B1, B2, B3 �̷��� ����
	static int addID; // 0���� �����ؼ� 1�� ����
	string name;
	Account* accountlist[100];

public:
	Bank() { ID = "B1"; name = "uriBank"; }
	Bank(string name) { this->name = name; }
	~Bank() { };
	string getBankName() { return name; }
};

/***********************	Account 	***********************/

class Account { // Bank�� User�� ����ص� �ɵ�
private:
	Database* database;
	int ID; // ID�� 0���� ������ 1�� �÷���, ���� ����(���¹�ȣ?)
	static int numID; // � ID�� �ο��Ұ��ΰ�
	Bank* ownerBank;
	User* owner;
	int password; // password�� ���� integer ����, ī��� ����
	int balance; // �ܾ�

public:
	Account();
	Account(Bank* bank, User* owner, int pw, int balance);
	~Account() {}
	int getID() { return ID; }
	bool checkPassword(int); // int Ÿ���� �н����带 �޾� �ش� �н����尡 �´��� Ȯ��
	void deposit(int type, int money); // �Ա�, �Աݾ� Ÿ��(ĳ��, ��ǥ) �Աݾ� ��ǲ,};
	void remittance(int, int); // �۱� ���¹�ȣ, �׼� <- transfer�� �̸� �ٲٴ°� ����(����)
	void withdrawal(int money); // ���
	void changeBalance(int money);
	void increaseID() { numID++; }
	int getNumID() { return numID; }
	int getBalance() { return balance; }
	Bank* getBank() { return ownerBank; }
	User* getOwner() { return owner; }
	bool isPrimary(ATM*);
};

/***********************	  ATM   	***********************/

class ATM { // Bank�� ����ص� �ɵ�
private:
	string ID; // atm�� A1 A2 A3 �̷��� ����
	static int numID; // id �ο��� �ѹ�, 0���� �����ؼ� 1�� ����
	Bank* ownerBank;
	string adminID;
	int adminpw;
	int remainCash; // atm ���� ���� �Ѿ�; Bill.sum()���� ��ü�غ���
	int remainCheck = 0; // atm ���� ��ǥ �Ѿ�
	int remainCheckNum = 0; // atm ���� ��ǥ ����
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
	bool deposit(int type, int money, int paperNum, Account* acc); // �Ա��Լ�, �Աݾ� (type1 : ���� type2 : ��ǥ)
	bool withdrawal(int money, Account* acc); // ����Լ�, ��ݾ�
	bool transfer(int type, int money, Account* fromAcc, Account* toAcc); // int fee ���ִ°� ���
	void IncreaseID() { numID++; }
	int getNumID() { return numID; }
	int getATMremainCash() { return remainCash; }
	int getATMremainCheckNum() { return remainCheckNum; }
	int insertCash(int cash) { remainCash += cash; return remainCash; } // �̰ɷ� �����ұ�? �ƴϸ� void�� ��ȭ?
	int fee(int, Account*, Account*);
	Bank* getBank() { return ownerBank; }
};

/***********************	  Bill  	***********************/

class Bill {
private:
	int b1k = 0; // õ����
	int b5k = 0; // ��õ����
	int b10k = 0; // ������
	int b50k = 0; // ��������
	// check�� �׼� �ȴٸ� ���� �� �ִ�(���ݵ� �⺻ 0���� �ϰ� check���� �ִ� C'tor)

public:
	Bill() {}
	Bill(int n1k, int n5k, int n10k, int n50k);
	// Bill(const Bill& rhs); // copy C'tor (�ʿ��Ѱ�?)
	int sum();
	void acceptCash() {/*�����ʿ�*/ } // ���� ���Խ�
	// ������� �ϳ��� 0 �� �ǰ� �ϱ�
	void withdraw(/*�����ʿ�*/) {/*�����ʿ�*/ } // ��ݽ�

};

/*******************	Other Functions 	*******************/

bool checkExit(string); // ?
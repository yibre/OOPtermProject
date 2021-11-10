#include "Classes.h"

Database* Database::instance;

void Database::addAccountList(Account* newAccount, int index) {
	accountList[index] = newAccount;
}


Account* Database::getAccountByNum(int index) {
	cout << "this come from a get account by num fun" << endl;
	return accountList[index];
}

Account::Account() {
	database = Database::getInstance();
	numID=0;
}

int Account::numID;

Account::Account(Bank* bank, User* owner, int pw, int balance) {
	this->ownerBank = bank;
	this->owner = owner;
	this->password = pw;
	this->balance = balance;
	this->ID = numID;
	increaseID(); // id를 부여한 뒤에는 static id를 1 추가함
}

ATM::ATM(Bank* bank, string adminID, int adminPW, int cash, int check, bool engSupport) {
	this->engSupport = engSupport;
	this->ownerBank = bank;
	this->adminID = adminID;
	this->adminpw = adminPW;
	this->remainCash = cash;
	this->remainCheck = check;
}

// Bank::Bank(string name) { this->name = name; }
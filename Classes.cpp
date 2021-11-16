#include "Classes.h"

/***********************	Database	***********************/

Database* Database::instance;
int Database::listsize = 0;
bool Database::sessionEnd;
int Database::transactionOrder = 1;
vector<vector<string > > Database::atmhis;
vector<vector<string > > Database::sessionhis;

void Database::addAccountList(Account* newAccount) {
	accountList[this->listsize] = newAccount;
	sizeincrease();
}

int Database::getIndexFromID(int ID) {
	int index = -1;
	for (int i = 0; i < getDatabaseSize(); i++) {
		if (this->accountList[i]->getID() == ID) {
			index = i;
			break;
		}
	}
	return index;
}

//isValid(int 계좌번호) 같은 함수 있었으면 좋겠다 

Account* Database::getAccountByNum(int index) { // 계좌번호 입력하면 계좌 찾아주는 함수; 계좌 유무 확인 옵션 원함(현주)
	// cout << "Debug: This comes from a get account by num fun" << endl;
	return accountList[index]; // 이대로면 최대 index 초과하는 숫자 들어와도 dummy 뱉을듯? exception handling 원함(현주)
}

void Database::addHistory(string transactionType, int money, Account* account, Account* recieverAcc) {
	int order = transactionOrder;
	transactionOrder++;
	string username = account->getOwner()->getUserName();
	int before = account->getBalance();
	int after;
	string receiverName = "-";
	if (transactionType == "입금") {
		after = before + money;
	}
	else if (transactionType == "출금") {
		after = before - money;
	}
	else if (transactionType == "송금") {
		receiverName = recieverAcc->getOwner()->getUserName();
		after = before - money;
	}
	vector<string> temp;
	temp.push_back(to_string(order));
	temp.push_back(username);
	temp.push_back(to_string(account->getID()));
	temp.push_back(transactionType);
	temp.push_back(to_string(before));
	temp.push_back(to_string(after));
	temp.push_back(receiverName);
	// vector<string> temp{ to_string(order), username, to_string(account->getID()), transactionType, to_string(before), to_string(after), receiverName };
	sessionhis.push_back(temp);
}

void Database::printHistory() {
	vector<string> column;
	column.push_back("순서");
	column.push_back("계좌주");
	column.push_back("계좌번호");
	column.push_back("거래 타입");
	column.push_back("거래 전 잔액");
	column.push_back("거래 후 잔액");
	column.push_back("송금시 수신인");
	for (int i = 0; i < column.size(); i++) {
		cout << column[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < sessionhis.size(); i++) {
		for (int j = 0; j < column.size(); j++) {
			cout << sessionhis[i][j] << " ";
		}
		cout << "\n" << endl;
	}
}

void Database::clearSessionHistory() {
	cout << sessionhis.size() << endl;
	for (int i = 0; i < sessionhis.size()+1; i++) {
		cout << i << endl;
		sessionhis.pop_back();
	}
}
/***********************	  User  	***********************/


/***********************	  Bank  	***********************/

// Bank::Bank(string name) { this->name = name; }

/***********************	Account 	***********************/

Account::Account() {
	database = Database::getInstance();
	numID = 0;
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

bool Account::checkPassword(int uswerAnswer) {
	if (this->password == uswerAnswer) { return true; }
	else { return false; }
}

void Account::deposit(int type, int money) { // 입금, 입금액 타입(캐시, 수표) 입금액 인풋,
	this->balance += money;
} // 현재는 type이 하는 일이 없다

void Account::withdrawal(int money) { // 출금
	this->balance -= money;
}

/*	건의(윤성이에게 현주가)	*/

void Account::changeBalance(int money) {
	this->balance += money;
}

/*
로 해서 계좌금액 바꾸는 함수 하나 두고(money가 양수이면 더하기, 음수이면 빼기)
입출송금에 모두 공통으로 사용하면 어떨지?
*/

bool Account::isPrimary(ATM* A) {
	if (this->ownerBank->getBankName() == A->getBank()->getBankName()) { return true; }
	// BankID로 같은지 아닌지 확인할 수도 있지만 현재 ID 구현이 덜 돼 있는 상태인듯
	return false;
}

/***********************	  ATM   	***********************/

ATM::ATM(Bank* bank, string adminID, int adminPW, int cash, int check, bool engSupport) {
	this->engSupport = engSupport;
	this->ownerBank = bank;
	this->adminID = adminID;
	this->adminpw = adminPW;
	this->remainCash = cash;
	this->remainCheck = check;
}


bool ATM::deposit(int type, int money, int paperNum, Account* acc) { // 입금함수, 입금액 (type1 : 현금 type2 : 수표)
	int fee = 0;
	if (this->getBank() != acc->getBank()) { fee = 500; }
	if (type == 1 && paperNum > 50) {
		cout << "최대 입금 가능 장 수를 초과하였습니다. 다시 시도해주십시오." << endl; // 입금 가능 최대 장 수를 제한해야하는데 어떻게 구현해야할까?
		return false;
	}
	if (type == 2 && paperNum > 30) {
		cout << "최대 입금 가능 장 수를 초과하였습니다. 다시 시도해주십시오." << endl; // 입금 가능 최대 장 수를 제한해야하는데 어떻게 구현해야할까?
		return false;
	}
	acc->deposit(type, money - fee);
	if (type == 1) { this->remainCash += money; }
	else { this->remainCheck += money; this->remainCheckNum += paperNum; }
	cout << money - fee << "원이 입금되었습니다." << endl;
	cout << "수수료 : " << fee << " 원" << endl;
	cout << "잔액 : " << acc->getBalance() << " 원" << endl;
	return true;
}

bool ATM::withdrawal(int money, Account* acc) { // 출금함수, 출금액
	int fee = 500;
	if (this->getBank() != acc->getBank()) { fee = 1000; }
	if ((money + fee) > acc->getBalance()) {
		cout << "계좌에 잔액이 부족합니다. 다시 시도해주십시오." << endl;
		return false;
	}
	if (money > this->remainCash) {
		cout << "ATM 기기에 현금이 부족합니다. 다시 시도해주십시오." << endl;
		return false;
	}
	if (money > this->maxWithdrawal) {
		cout << "1회 최대 출금 금액(30만원)을 초과하였습니다. 다시 시도해주십시오." << endl;
		return false;
	}
	acc->withdrawal(money + fee);
	this->remainCash -= money;
	cout << money << "원이 출금되었습니다. 투입구를 확인해주십시오." << endl;
	cout << "수수료 : " << fee << " 원" << endl;
	cout << "잔액 : " << acc->getBalance() << " 원" << endl;
	return true;
}

bool ATM::transfer(int type, int money, Account* fromAcc, Account* toAcc) {
	cout << "Debug: ATM::transfer called" << endl;
	cout << "Debug: (송금 전)\nfrom account [" << fromAcc->getID() << "]\t 현재 잔액: [";
	cout << fromAcc->getBalance() << "]원\nto account [" << toAcc->getID() << "]\t 현재 잔액: [";
	cout << toAcc->getBalance() << "]원" << endl;

	int fee = this->fee(7, fromAcc, toAcc);

	if (type == 1) {
		if (fromAcc->getBalance() >= fee) {
			fromAcc->changeBalance(-fee);
			toAcc->changeBalance(money);

			cout << "\t" << money << "원이 [" << toAcc->getOwner()->getUserName();
			cout << "] 님에게 송금 완료되었습니다." << endl;

			cout << "Debug: (송금 후)\nfrom account [" << fromAcc->getID() << "]\t 현재 잔액: [";
			cout << fromAcc->getBalance() << "]원\nto account [" << toAcc->getID() << "]\t 현재 잔액: [";
			cout << toAcc->getBalance() << "]원" << endl;
		}
		else { cout << "Debug: 잔액 부족" << endl; return false; }
	}
	else if (type == 2) {
		if (fromAcc->getBalance() >= (money + fee)) {
			fromAcc->changeBalance(-(money + fee));
			toAcc->changeBalance(money);

			cout << "\t" << money << "원이 [" << toAcc->getOwner()->getUserName();
			cout << "] 님에게 송금 완료되었습니다." << endl;

			cout << "Debug: (송금 후)\nfrom account [" << fromAcc->getID() << "]\t 현재 잔액: [";
			cout << fromAcc->getBalance() << "]원\nto account [" << toAcc->getID() << "]\t 현재 잔액: [";
			cout << toAcc->getBalance() << "]원" << endl;
		}
		else { cout << "Debug: 잔액 부족" << endl; return false; }
	}


	// transaction history 저장
	return true;
}

int ATM::fee(int transactionType, Account* a1, Account* a2 = nullptr) { // 송금일 때만 a2 필요
	if (transactionType == 5) { // deposit
		if (a1->isPrimary(this)) { return 0; }
		else { return 500; }
	}
	else if (transactionType == 6) { // withdrawal
		if (a1->isPrimary(this)) { return 500; }
		else { return 1000; }
	}
	else if (transactionType == 7) { // transfer
		if (a1->isPrimary(this) && a2->isPrimary(this)) { return 1500; } // prim-prim
		else if (a1->isPrimary(this) || a2->isPrimary(this)) { return 2000; } // prim-nonp
		else { return 2500; } // nonp-nonp
	}
	else { cout << "Debug: Wrong transactionType in int ATM::fee(int, Bank*, Bank*)" << endl; exit(0); }
}

/***********************	  Bill  	***********************/

Bill::Bill(int n1k, int n5k, int n10k, int n50k) : b1k(n1k), b5k(n5k), b10k(n10k), b50k(n50k) {}

int Bill::sum() { return b1k + b5k + b10k + b50k; }


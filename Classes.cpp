#include "Classes.h"

/***********************	Database	***********************/

Database* Database::instance;
int Database::listsize = 0;
bool Database::sessionProceeding = false;
int Database::transactionOrder = 1;
int Database::totalSessionNum = 0;
int Database::currentOrderNum = 0;
vector<vector<string > > Database::atmhisEN;
vector<vector<string > > Database::atmhisKR;
Translation* Database::languagePack = new Translation();


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

Account* Database::getAccountByNum(int index) { // 계좌번호 입력하면 계좌 찾아주는 함수
	return accountList[index];
}

void Database::addATMHistory(int transactionType, int before, int after, Account* account, 
	Account* receiverAcc, int transferAmount, int ATMremainCash, int* atmCashNum) {
	int order = transactionOrder;

	if (transactionOrder == 1) {
		vector<string> column;
		column.push_back("[순서]"); column.push_back("[계좌주]"); column.push_back("[계좌번호]");
		column.push_back("[거래 타입]"); column.push_back("[거래 전 잔액]"); column.push_back("[거래 후 잔액]");
		column.push_back("[수신 계좌]"); column.push_back("[송금액]"); column.push_back("[ATM 내 현금 잔액]");
		column.push_back("[ATM 50k]"); column.push_back("[ATM 10k]"); column.push_back("[ATM 5k]");
		column.push_back("[ATM 1k]"); atmhisKR.push_back(column); 
		
		vector<string> column2;
		column2.push_back("[Order]"); column2.push_back("[Acc. holder]"); column2.push_back("[Acc. No.]");
		column2.push_back("[Transaction]"); column2.push_back("[Balance (before)]");
		column2.push_back("[Balance (changed)]"); column2.push_back("[Recipient]");
		column2.push_back("[Transferred amount]"); column2.push_back("[Cash in ATM]");
		column2.push_back("[ATM 50k]"); column2.push_back("[ATM 10k]"); column2.push_back("[ATM 5k]");
		column2.push_back("[ATM 1k]"); atmhisEN.push_back(column2);
	}

	cout << languagePack->getSentence("Database_addHistory0") << totalSessionNum << endl;
	cout << languagePack->getSentence("Database_addHistory1") << transactionOrder << endl;
	transactionOrder++;
	currentOrderNum++;
	string usernameKR = account->getOwner()->getName();
	string usernameEN = account->getOwner()->getName(false);
	string receiverName = "-";
	string transactionTypeKR;
	string transactionTypeEN;
	if (transactionType == 1) {
		transactionTypeKR = "입금";
		transactionTypeEN = "deposit";
	}
	else if (transactionType == 2) {
		transactionTypeKR = "출금";
		transactionTypeEN = "withdrawal";
	}
	else if (transactionType == 3) {
		transactionTypeKR = "송금";
		transactionTypeEN = "transfer";
		receiverName = to_string(receiverAcc->getID());
	}
	vector<string> tempKR;
	tempKR.push_back(to_string(order));
	tempKR.push_back(usernameKR);
	tempKR.push_back(to_string(account->getID()));
	tempKR.push_back(transactionTypeKR);
	tempKR.push_back(to_string(before));
	tempKR.push_back(to_string(after));
	tempKR.push_back(receiverName);
	tempKR.push_back(to_string(transferAmount));
	tempKR.push_back(to_string(ATMremainCash));
	tempKR.push_back(to_string(atmCashNum[0]));
	tempKR.push_back(to_string(atmCashNum[1]));
	tempKR.push_back(to_string(atmCashNum[2]));
	tempKR.push_back(to_string(atmCashNum[3]));
	vector<string> tempEN;
	tempEN.push_back(to_string(order));
	tempEN.push_back(usernameEN);
	tempEN.push_back(to_string(account->getID()));
	tempEN.push_back(transactionTypeEN);
	tempEN.push_back(to_string(before));
	tempEN.push_back(to_string(after));
	tempEN.push_back(receiverName);
	tempEN.push_back(to_string(transferAmount));
	tempEN.push_back(to_string(ATMremainCash));
	tempEN.push_back(to_string(atmCashNum[0]));
	tempEN.push_back(to_string(atmCashNum[1]));
	tempEN.push_back(to_string(atmCashNum[2]));
	tempEN.push_back(to_string(atmCashNum[3]));

	atmhisEN.push_back(tempEN);
	atmhisKR.push_back(tempKR);
}

void Database::printATMHistory() {
	if (languagePack->isKor()) {
		for (int i = 0; i < atmhisKR.size(); i++) {
			for (int j = 0; j < 13; j++) {
				cout << atmhisKR[i][j] << "\t";
			}
			cout << "\n" << endl;
		}
	}
	else {
		for (int i = 0; i < atmhisEN.size(); i++) {
			for (int j = 0; j < 13; j++) {
				cout << atmhisEN[i][j] << "\t";
			}
			cout << "\n" << endl;
		}
	}
}

void Database::printSessionHistory() {
	if (currentOrderNum == 0) { return; }
	int start = atmhisEN.size() - currentOrderNum;
	vector<string> column;
	column.push_back(languagePack->getSentence("Database_printSessionHistory0.1"));
	column.push_back(languagePack->getSentence("Database_printSessionHistory0.2"));
	column.push_back(languagePack->getSentence("Database_printSessionHistory0.3"));
	column.push_back(languagePack->getSentence("Database_printSessionHistory0.4"));
	column.push_back(languagePack->getSentence("Database_printSessionHistory0.5"));
	column.push_back(languagePack->getSentence("Database_printSessionHistory0.6"));
	column.push_back(languagePack->getSentence("Database_printHistory0.8"));

	for (int i = 0; i < column.size(); i++) {
		cout << column[i] << " ";
	}
	cout << endl;
	for (int i = start; i < atmhisEN.size(); i++) {
		for (int j = 1; j < column.size() + 1; j++) {
			if (languagePack->isKor()) cout << atmhisKR[i][j] << "\t";
			else cout << atmhisEN[i][j] << "\t";
		}
		cout << "\n" << endl;
	}
}

void Database::clearSessionHistory() {
	totalSessionNum++;
	currentOrderNum = 0;
}

/***********************	Account 	***********************/

Account::Account() {
	database = Database::getInstance();
}

int Account::numID = 10000;

Account::Account(Bank* bank, User* owner, int pw, int balance) {
	this->ownerBank = bank;
	this->owner = owner;
	this->password = pw;
	this->balance = balance;
	this->ID = numID;
	numID++; // id를 부여한 뒤에는 static id를 1 추가함
}

bool Account::checkPassword(int uswerAnswer) {
	if (this->password == uswerAnswer) { return true; }
	else { return false; }
}

void Account::changeBalance(int money) {
	this->balance += money;
}

bool Account::isPrimary(ATM* A) {
	if (this->ownerBank->getName() == A->getBank()->getName()) { return true; }
	return false;
}

/***********************	  ATM   	***********************/

int ATM::numID = 100; // static int numID 초기화 (3자리 고유번호 주기 위해; 변동가능)

ATM::ATM(Bank* bank, string adminID, int adminPW, Bill* bill, int check, bool engSupport = 1, bool multiBank = 1) {
	database = Database::getInstance();

	this->ID = this->numID; // static int를 ID로 배정
	this->numID++;

	this->engSupport = engSupport;
	this->multiBank = multiBank;
	this->ownerBank = bank;
	this->adminID = adminID;
	this->adminpw = adminPW;
	this->remainBill = bill;
	this->remainCheck = check;
	this->languagePack = new Translation();
}


bool ATM::deposit(int type, Bill money, int check[], int checkNum, int checkSum, Account* acc) { // 입금함수, 입금액 (type1 : 현금 type2 : 수표)
	int fee = this->fee(5, acc, nullptr);
	int before = acc->getBalance();
	if (type == 1) {
		acc->changeBalance(money.getSum() - fee);
		*this->remainBill += money;
		database->addATMHistory(1,
			before, acc->getBalance(), acc, acc, 0, this->remainBill->getSum(), this->remainBill->getCashNumArray());
	}
	else if (type == 2) {
		acc->changeBalance(checkSum - fee);
		this->remainCheck += checkSum;
		this->remainCheckNum += checkNum;
		database->addATMHistory(1,
			before, acc->getBalance(), acc, acc, 0, this->remainBill->getSum(), this->remainBill->getCashNumArray());
	}
	return true;
}

bool ATM::withdrawal(Bill money, Account* acc) { // 출금함수, 출금액
	int fee = this->fee(6, acc, nullptr);
	int before = acc->getBalance();
	acc->changeBalance(-(money.getSum() + fee));
	*this->remainBill -= money;

	database->addATMHistory(2,
		before, acc->getBalance(), acc, acc, 0, this->remainBill->getSum(), this->remainBill->getCashNumArray());

	return true;
}

bool ATM::transfer(int type, int money, Account* fromAcc, Account* toAcc, Bill& bill) {

	int fee = this->fee(7, fromAcc, toAcc);
	int before = fromAcc->getBalance();

	if (type == 1) { // cash transfer
		if (fromAcc->getBalance() >= fee) {
			fromAcc->changeBalance(-fee);
			toAcc->changeBalance(money);

			// 송금 확인되어 반환의 여지 없을 때 remainCash transactionBill만큼 늘리기
			*this->remainBill += bill;
			bill = Bill{ 0,0,0,0 };

			int after = fromAcc->getBalance();
			database->addATMHistory(3,
				before, fromAcc->getBalance(), fromAcc, toAcc, money, this->remainBill->getSum(), this->remainBill->getCashNumArray());
		}
		else { cout << languagePack->getSentence("ATM_transfer3"); return false; }
	}
	else if (type == 2) { // account transfer
		if (fromAcc->getBalance() >= (money + fee)) {
			fromAcc->changeBalance(-(money + fee));
			toAcc->changeBalance(money);

			int after = fromAcc->getBalance();
			database->addATMHistory(3,
				before, fromAcc->getBalance(), fromAcc, toAcc, money, this->remainBill->getSum(), this->remainBill->getCashNumArray());
		}
		else { return false; }
	}
	return true;
}

bool ATM::checkPW(int password) {
	if (password == adminpw) { return true; }
	else { return false; }
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
	else {
		exit(0);
	}
}

/***********************	  Bill  	***********************/

int Bill::value[4] = { 50000,10000,5000,1000 };

Bill::Bill(int c50k = 0, int c10k = 0, int c5k = 0, int c1k = 0) : paperCash{ c50k, c10k, c5k, c1k } {}

int Bill::getSum() {
	int sum = 0;
	for (int i = 0; i < 4; i++) {
		sum += value[i] * paperCash[i];
	}
	return sum;
}

int Bill::getTotalNum() {
	int sum = 0;
	for (int i : paperCash) {
		sum += i;
	}
	return sum;
}

Bill& Bill::operator+=(const Bill& rhs) {
	this->paperCash[0] += rhs.paperCash[0];
	this->paperCash[1] += rhs.paperCash[1];
	this->paperCash[2] += rhs.paperCash[2];
	this->paperCash[3] += rhs.paperCash[3];
	return *this;
}

Bill& Bill::operator-=(const Bill& rhs) {
	this->paperCash[0] -= rhs.paperCash[0];
	this->paperCash[1] -= rhs.paperCash[1];
	this->paperCash[2] -= rhs.paperCash[2];
	this->paperCash[3] -= rhs.paperCash[3];
	return *this;
}

bool Bill::operator<=(const Bill& bill) {
	bool case1 = paperCash[0] <= bill.paperCash[0];
	bool case2 = paperCash[1] <= bill.paperCash[1];
	bool case3 = paperCash[2] <= bill.paperCash[2];
	bool case4 = paperCash[3] <= bill.paperCash[3];
	return (case1 && case2 && case3 && case4);
}

bool Bill::operator>=(const Bill& bill) {
	bool case1 = paperCash[0] >= bill.paperCash[0];
	bool case2 = paperCash[1] >= bill.paperCash[1];
	bool case3 = paperCash[2] >= bill.paperCash[2];
	bool case4 = paperCash[3] >= bill.paperCash[3];
	return (case1 && case2 && case3 && case4);
}
bool Bill::operator<(const Bill& bill) {
	bool case1 = paperCash[0] < bill.paperCash[0];
	bool case2 = paperCash[1] < bill.paperCash[1];
	bool case3 = paperCash[2] < bill.paperCash[2];
	bool case4 = paperCash[3] < bill.paperCash[3];
	return (case1 && case2 && case3 && case4);
}

bool Bill::operator>(const Bill& bill) {
	bool case1 = paperCash[0] > bill.paperCash[0];
	bool case2 = paperCash[1] > bill.paperCash[1];
	bool case3 = paperCash[2] > bill.paperCash[2];
	bool case4 = paperCash[3] > bill.paperCash[3];
	return (case1 && case2 && case3 && case4);
}

void Bill::printBill(bool isKor) {
	if (isKor) {
		cout << "\t금액 : ";
		for (int i = 0; i < 4; i++) {
			cout << "[" << this->value[i] << "원 : " << this->paperCash[i] << "장] ";
		}
		cout << endl;
		cout << "\t총 액수 : " << this->getSum() << "원\n";
	}
	else {
		cout << "\tAmount : ";
		for (int i = 0; i < 4; i++) {
			cout << "[" << this->value[i] << " won : " << this->paperCash[i] << " bill(s)] ";
		}
		cout << endl;
		cout << "\tTotal amount : " << this->getSum() << " won\n";
	}
}
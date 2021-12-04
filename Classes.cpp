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
vector<vector<string > > Database::sessionhisEN, sessionhisKR;
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

//isValid(int 계좌번호) 같은 함수 있었으면 좋겠다 

Account* Database::getAccountByNum(int index) { // 계좌번호 입력하면 계좌 찾아주는 함수; 계좌 유무 확인 옵션 원함(현주)
	// cout << "Debug: This comes from a get account by num fun" << endl;
	return accountList[index]; // 이대로면 최대 index 초과하는 숫자 들어와도 dummy 뱉을듯? exception handling 원함(현주)
}

void Database::addATMHistory(int transactionType, int before, int after, Account* account, Account* receiverAcc, int transferAmount, int ATMremainCash) { // classes.h에서와 변수이름 다르다
	int order = transactionOrder;

	if (transactionOrder == 1) {
		vector<string> column;
		column.push_back("[순서]");
		column.push_back("[계좌주]");
		column.push_back("[계좌번호]");
		column.push_back("[거래 타입]");
		column.push_back("[거래 전 잔액]");
		column.push_back("[거래 후 잔액]");
		column.push_back("[송금 시 수신인]");
		column.push_back("[송금 금액]");
		column.push_back("[ATM 내 현금 잔액]");
		atmhisKR.push_back(column);
		vector<string> column2;
		column2.push_back("[Order]");
		column2.push_back("[Account holder]");
		column2.push_back("[Account number]");
		column2.push_back("[Transcation type]");
		column2.push_back("[Balance before the transaction]");
		column2.push_back("[Balance after the transaction]");
		column2.push_back("[Recipient when transfer]");
		column2.push_back("[TransferAmount]");
		column2.push_back("[Cash balance in ATM]");
		atmhisEN.push_back(column2);
	}

	cout << languagePack->getSentence("Database_addHistory0") << totalSessionNum << endl;
	cout << languagePack->getSentence("Database_addHistory1") << transactionOrder << endl;
	transactionOrder++;
	currentOrderNum++;
	//totalSessionNum++;
	string usernameKR = account->getOwner()->getName();
	string usernameEN = account->getOwner()->getName(false);
	string receiverNameKR = "-";
	string receiverNameEN = "-";
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
		receiverNameKR = receiverAcc->getOwner()->getName(true);
		receiverNameEN = receiverAcc->getOwner()->getName(false);
	}
	vector<string> tempKR;
	tempKR.push_back(to_string(order));
	tempKR.push_back(usernameKR);
	tempKR.push_back(to_string(account->getID()));
	tempKR.push_back(transactionTypeKR);
	tempKR.push_back(to_string(before));
	tempKR.push_back(to_string(after));
	tempKR.push_back(receiverNameKR);
	tempKR.push_back(to_string(transferAmount));
	tempKR.push_back(to_string(ATMremainCash));
	vector<string> tempEN;
	tempEN.push_back(to_string(order));
	tempEN.push_back(usernameEN);
	tempEN.push_back(to_string(account->getID()));
	tempEN.push_back(transactionTypeEN);
	tempEN.push_back(to_string(before));
	tempEN.push_back(to_string(after));
	tempEN.push_back(receiverNameEN);
	tempEN.push_back(to_string(transferAmount));
	tempEN.push_back(to_string(ATMremainCash));

	atmhisEN.push_back(tempEN);
	atmhisKR.push_back(tempKR);
}

void Database::printATMHistory() {
	/*
	vector<string> column;
	column.push_back(languagePack->getSentence("Database_printHistory0.1"));
	column.push_back(languagePack->getSentence("Database_printHistory0.2"));
	column.push_back(languagePack->getSentence("Database_printHistory0.3"));
	column.push_back(languagePack->getSentence("Database_printHistory0.4"));
	column.push_back(languagePack->getSentence("Database_printHistory0.5"));
	column.push_back(languagePack->getSentence("Database_printHistory0.6"));
	column.push_back(languagePack->getSentence("Database_printHistory0.7"));
	column.push_back(languagePack->getSentence("Database_printHistory0.8"));
	column.push_back(languagePack->getSentence("Database_printHistory0.9"));
	for (int i = 0; i < column.size(); i++) {
		cout << column[i] << " ";
	}
	cout << endl;*/
	if (languagePack->isKor()) {
		for (int i = 0; i < atmhisKR.size(); i++) {
			for (int j = 0; j < 9; j++) {
				cout << atmhisKR[i][j] << "\t";
			}
			cout << "\n" << endl;
		}
	}
	else {
		for (int i = 0; i < atmhisEN.size(); i++) {
			for (int j = 0; j < 9; j++) {
				cout << atmhisEN[i][j] << "\t";
			}
			cout << "\n" << endl;
		}
	}
}

void Database::addSessionHistory(string type, int before, int after, Account* acc, Account* receiver, int transferAmount) {
	// 거래 순서, 나간 금액, 들어온 금액, 계좌잔액
	cout << languagePack->getSentence("Database_addSessionHistory0") << acc->getOwner()->getName() << endl;
	vector<string> column;

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

	// cout << sessionhis.size() << endl;
	// for (int i = 0; i < sessionhis.size() + 1; i++) {
		// cout << i << endl;
		// sessionhis.pop_back();
	// }
}
/***********************	  User  	***********************/


/***********************	  Bank  	***********************/

// Bank::Bank(string name) { this->name = name; }

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

/*	건의(윤성이에게 현주가)	*/

void Account::changeBalance(int money) {
	this->balance += money;
}

/*
로 해서 계좌금액 바꾸는 함수 하나 두고(money가 양수이면 더하기, 음수이면 빼기)
입출송금에 모두 공통으로 사용하면 어떨지?
*/

bool Account::isPrimary(ATM* A) {
	if (this->ownerBank->getName() == A->getBank()->getName()) { return true; }
	// BankID로 같은지 아닌지 확인할 수도 있지만 현재 ID 구현이 덜 돼 있는 상태인듯
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
		// cout << money.getSum() - fee << languagePack->getSentence("ATM_deposit0");
		database->addATMHistory(1,
			before, acc->getBalance(), acc, acc, 0, this->remainBill->getSum());
	}
	else if (type == 2) {
		acc->changeBalance(checkSum - fee);
		this->remainCheck += checkSum;
		this->remainCheckNum += checkNum;
		// cout << checkSum - fee << languagePack->getSentence("ATM_deposit1");
		database->addATMHistory(1,
			before, acc->getBalance(), acc, acc, 0, this->remainBill->getSum());
	}

	//cout << languagePack->getSentence("ATM_deposit2.1") << fee << languagePack->getSentence("ATM_deposit2.2");
	//cout << languagePack->getSentence("ATM_deposit3.1") << acc->getBalance() << languagePack->getSentence("ATM_deposit3.2");
	return true;
}

bool ATM::withdrawal(Bill money, Account* acc) { // 출금함수, 출금액
	int fee = this->fee(6, acc, nullptr);
	int before = acc->getBalance();
	acc->changeBalance(-(money.getSum() + fee));
	*this->remainBill -= money;

	database->addATMHistory(2,
		before, acc->getBalance(), acc, acc, 0, this->remainBill->getSum());

	return true;
}

bool ATM::transfer(int type, int money, Account* fromAcc, Account* toAcc, Bill& bill) {

	// cout << languagePack->getSentence("ATM_transfer0.1");
	// cout << fromAcc->getID() << languagePack->getSentence("ATM_transfer0.2");
	// cout << fromAcc->getBalance() << languagePack->getSentence("ATM_transfer0.3") << toAcc->getID() << languagePack->getSentence("ATM_transfer0.4");
	// cout << toAcc->getBalance() << languagePack->getSentence("ATM_transfer0.5");

	int fee = this->fee(7, fromAcc, toAcc);
	int before = fromAcc->getBalance();

	if (type == 1) { // cash transfer
		if (fromAcc->getBalance() >= fee) {
			fromAcc->changeBalance(-fee);
			toAcc->changeBalance(money);

			// 송금 확인되어 반환의 여지 없을 때 remainCash transactionBill만큼 늘리기
			*this->remainBill += bill;
			bill = Bill{ 0,0,0,0 };

			// cout << "\t" << money << languagePack->getSentence("ATM_transfer1.2") << toAcc->getOwner()->getName();
			// cout << languagePack->getSentence("ATM_transfer1.3");

			// cout << languagePack->getSentence("ATM_transfer2.1") << fromAcc->getID() << languagePack->getSentence("ATM_transfer2.2");
			// cout << fromAcc->getBalance() << languagePack->getSentence("ATM_transfer2.3") << toAcc->getID() << languagePack->getSentence("ATM_transfer2.4");
			// cout << toAcc->getBalance() << languagePack->getSentence("ATM_transfer2.5");

			int after = fromAcc->getBalance();
			database->addATMHistory(3,
				before, fromAcc->getBalance(), fromAcc, toAcc, money, this->remainBill->getSum());
			// database->addHistory("송금", before, after, fromAcc, toAcc);
		}
		else { cout << languagePack->getSentence("ATM_transfer3"); return false; }
	}
	else if (type == 2) { // account transfer
		if (fromAcc->getBalance() >= (money + fee)) {
			fromAcc->changeBalance(-(money + fee));
			toAcc->changeBalance(money);

			// cout << "\t" << money << languagePack->getSentence("ATM_transfer1.2") << toAcc->getOwner()->getName();
			// cout << languagePack->getSentence("ATM_transfer1.3");

			// cout << languagePack->getSentence("ATM_transfer2.1") << fromAcc->getID() << languagePack->getSentence("ATM_transfer2.2");
			// cout << fromAcc->getBalance() << languagePack->getSentence("ATM_transfer2.3") << toAcc->getID() << languagePack->getSentence("ATM_transfer2.4");
			// cout << toAcc->getBalance() << languagePack->getSentence("ATM_transfer2.5");

			int after = fromAcc->getBalance();
			database->addATMHistory(3,
				before, fromAcc->getBalance(), fromAcc, toAcc, money, this->remainBill->getSum());
			// database->addHistory("송금", before, after, fromAcc, toAcc);

		}
		else {
			// cout << languagePack->getSentence("ATM_transfer3"); // debug
			return false;
		}
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
	else { cout << languagePack->getSentence("ATM_fee0"); exit(0); } // ???
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

/*
Bill& Bill::operator+(const Bill& bill) {
	int num1 = paperCash[0] + bill.paperCash[0];
	int num2 = paperCash[1] + bill.paperCash[1];
	int num3 = paperCash[2] + bill.paperCash[2];
	int num4 = paperCash[3] + bill.paperCash[3];
	Bill result = Bill{ num1, num2, num3, num4 };
	return result;
	// 컴파일러 경고뜸 (warning: reference to local variable 'result' returned)
	// return type 왜 Bill&인지? 그냥 Bill 해도 충분하지 않나?

}
*/

Bill& Bill::operator+=(const Bill& rhs) {
	this->paperCash[0] += rhs.paperCash[0];
	this->paperCash[1] += rhs.paperCash[1];
	this->paperCash[2] += rhs.paperCash[2];
	this->paperCash[3] += rhs.paperCash[3];
	return *this;
	// 작동 확인 완료되었는지?
}

/*
Bill& Bill::operator-(const Bill& bill) {
	int num1 = paperCash[0] - bill.paperCash[0];
	int num2 = paperCash[1] - bill.paperCash[1];
	int num3 = paperCash[2] - bill.paperCash[2];
	int num4 = paperCash[3] - bill.paperCash[3];
	Bill result = Bill{ num1, num2, num3, num4 };
	return result;
	// 컴파일러 경고뜸 (warning: reference to local variable 'result' returned)
	// return type 왜 Bill&인지? 그냥 Bill 해도 충분하지 않나?
}
*/

Bill& Bill::operator-=(const Bill& rhs) {
	this->paperCash[0] -= rhs.paperCash[0];
	this->paperCash[1] -= rhs.paperCash[1];
	this->paperCash[2] -= rhs.paperCash[2];
	this->paperCash[3] -= rhs.paperCash[3];
	return *this;
	// 작동 확인 완료되었는지?
}

/*
Bill& Bill::operator*(const int mul) {
	int num1 = paperCash[0] * mul;
	int num2 = paperCash[1] * mul;
	int num3 = paperCash[2] * mul;
	int num4 = paperCash[3] * mul;
	Bill result = Bill{ num1, num2, num3, num4 };
	return result;
	// 컴파일러 경고뜸 (warning: reference to local variable 'result' returned)
	// return type 왜 Bill&인지? 그냥 Bill 해도 충분하지 않나?
}
*/

bool Bill::operator<=(const Bill& bill) {
	bool case1 = paperCash[0] <= bill.paperCash[0];
	bool case2 = paperCash[1] <= bill.paperCash[1];
	bool case3 = paperCash[2] <= bill.paperCash[2];
	bool case4 = paperCash[3] <= bill.paperCash[3];
	return (case1 & case2 & case3 & case4);
	// bool이어서 상관없긴 한데 논리연산 && 아니고 비트단위연산 & 쓴 건 의도된 것인가?
}

bool Bill::operator>=(const Bill& bill) {
	bool case1 = paperCash[0] >= bill.paperCash[0];
	bool case2 = paperCash[1] >= bill.paperCash[1];
	bool case3 = paperCash[2] >= bill.paperCash[2];
	bool case4 = paperCash[3] >= bill.paperCash[3];
	return (case1 & case2 & case3 & case4);
	// bool이어서 상관없긴 한데 논리연산 && 아니고 비트단위연산 & 쓴 건 의도된 것인가?
}
bool Bill::operator<(const Bill& bill) {
	bool case1 = paperCash[0] < bill.paperCash[0];
	bool case2 = paperCash[1] < bill.paperCash[1];
	bool case3 = paperCash[2] < bill.paperCash[2];
	bool case4 = paperCash[3] < bill.paperCash[3];
	return (case1 & case2 & case3 & case4);
	// bool이어서 상관없긴 한데 논리연산 && 아니고 비트단위연산 & 쓴 건 의도된 것인가?
}

bool Bill::operator>(const Bill& bill) {
	bool case1 = paperCash[0] > bill.paperCash[0];
	bool case2 = paperCash[1] > bill.paperCash[1];
	bool case3 = paperCash[2] > bill.paperCash[2];
	bool case4 = paperCash[3] > bill.paperCash[3];
	return (case1 & case2 & case3 & case4);
	// bool이어서 상관없긴 한데 논리연산 && 아니고 비트단위연산 & 쓴 건 의도된 것인가?
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

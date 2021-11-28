#include "Classes.h"

/***********************	Database	***********************/

Database* Database::instance;
int Database::listsize = 0;
bool Database::sessionProceeding = false;
int Database::transactionOrder = 1;
int Database::totalSessionNum = 0;
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

void Database::addHistory(string transactionType, int before, int after, Account* account, Account* receiverAcc) { // classes.h에서와 변수이름 다르다
	int order = transactionOrder;

	cout << "total session number is " << totalSessionNum << endl;
	cout << "transaction order is : " << transactionOrder << endl;
	transactionOrder++;
	totalSessionNum++;
	string username = account->getOwner()->getUserName();
	string receiverName = "-";
	if (transactionType == "transfer" || transactionType == "송금") {
		receiverName = receiverAcc->getOwner()->getUserName();
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
	atmhis.push_back(temp);
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
	for (int i = 0; i < atmhis.size(); i++) {
		for (int j = 0; j < column.size(); j++) {
			cout << atmhis[i][j] << " ";
		}
		cout << "\n" << endl;
	}
}

void Database::addSessionHistory(string, int, Account* myAcc) {
	// 거래 순서, 나간 금액, 들어온 금액, 계좌잔액
	cout << "거래계좌: " << myAcc->getOwner()->getUserName() << endl;
	vector<string> column;

}

void Database::printSessionHistory() {
	int start = atmhis.size() - totalSessionNum;
	vector<string> column;
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
	for (int i = start; i < atmhis.size(); i++) {
		for (int j = 1; j < column.size(); j++) {
			cout << atmhis[i][j] << " ";
		}
		cout << "\n" << endl;
	}
}

void Database::clearSessionHistory() {
	totalSessionNum = 0;
	
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

ATM::ATM(Bank* bank, string adminID, int adminPW, Bill* bill, int check, bool engSupport = 1, bool multiBank = 1) {
	database = Database::getInstance();
	
	this->engSupport = engSupport;
	this->multiBank = multiBank;
	this->ownerBank = bank;
	this->adminID = adminID;
	this->adminpw = adminPW;
	this->remainBill = bill;
	this->remainCheck = check;
}


bool ATM::deposit(int type, Bill money, int check[], int checkNum, int checkSum, Account* acc) { // 입금함수, 입금액 (type1 : 현금 type2 : 수표)
	int fee = this->fee(5, acc, nullptr);

	if (type == 1) {
		acc->changeBalance(money.getSum());
		*this->remainBill += money;
		cout << money.getSum() - fee << "원이 입금되었습니다." << endl;
	}
	else if (type == 2) {
		acc->changeBalance(checkSum);
		this->remainCheck += checkSum;
		this->remainCheckNum += checkNum;
		cout << checkSum - fee << "원이 입금되었습니다." << endl;
	}
	database->addHistory("입금", acc->getBalance(), money.getSum() - fee, acc, acc);

	cout << "수수료 : " << fee << " 원" << endl;
	cout << "잔액 : " << acc->getBalance() << " 원" << endl;
	return true;
}

bool ATM::withdrawal(Bill money, Account* acc) { // 출금함수, 출금액
	int fee = this->fee(6, acc, nullptr);
	int before = acc->getBalance();
	acc->changeBalance(-(money.getSum() + fee));
	*this->remainBill -= money;
	cout << money.getSum() << "원이 출금되었습니다. 투입구를 확인해주십시오." << endl;
	cout << "수수료 : " << fee << " 원" << endl;
	cout << "잔액 : " << acc->getBalance() << " 원" << endl;

	database->addHistory("출금", before, acc->getBalance(), acc, acc);

	return true;
}

bool ATM::transfer(int type, int money, Account* fromAcc, Account* toAcc, Bill& bill) {
	cout << "Debug: ATM::transfer called" << endl;
	cout << "Debug: (송금 전)\nfrom account [" << fromAcc->getID() << "]\t 현재 잔액: [";
	cout << fromAcc->getBalance() << "]원\nto account [" << toAcc->getID() << "]\t 현재 잔액: [";
	cout << toAcc->getBalance() << "]원" << endl;

	int fee = this->fee(7, fromAcc, toAcc);
	int before = fromAcc->getBalance();

	if (type == 1) { // cash transfer
		if (fromAcc->getBalance() >= fee) {
			fromAcc->changeBalance(-fee);
			toAcc->changeBalance(money);
			
			// 송금 확인되어 반환의 여지 없을 때 remainCash transactionBill만큼 늘리기
			*(this->remainBill) += bill;
			bill = Bill{0,0,0,0};

			cout << "\t" << money << "원이 [" << toAcc->getOwner()->getUserName();
			cout << "] 님에게 송금 완료되었습니다." << endl;

			cout << "Debug: (송금 후)\nfrom account [" << fromAcc->getID() << "]\t 현재 잔액: [";
			cout << fromAcc->getBalance() << "]원\nto account [" << toAcc->getID() << "]\t 현재 잔액: [";
			cout << toAcc->getBalance() << "]원" << endl;

			int after = fromAcc->getBalance();
			database->addHistory("송금", before, after, fromAcc, toAcc);
		}
		else { cout << "Debug: 잔액 부족" << endl; return false; }
	}
	else if (type == 2) { // account transfer
		if (fromAcc->getBalance() >= (money + fee)) {
			fromAcc->changeBalance(-(money + fee));
			toAcc->changeBalance(money);

			cout << "\t" << money << "원이 [" << toAcc->getOwner()->getUserName();
			cout << "] 님에게 송금 완료되었습니다." << endl;

			cout << "Debug: (송금 후)\nfrom account [" << fromAcc->getID() << "]\t 현재 잔액: [";
			cout << fromAcc->getBalance() << "]원\nto account [" << toAcc->getID() << "]\t 현재 잔액: [";
			cout << toAcc->getBalance() << "]원" << endl;

			int after = fromAcc->getBalance();
			database->addHistory("송금", before, after, fromAcc, toAcc);

		}
		else { cout << "Debug: 잔액 부족" << endl; return false; }
	}

	return true;
}

bool ATM::checkPW(int password) {
	if (password == adminpw) { return true; }
	else return false;
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

Bill& Bill::operator+=(const Bill& rhs) {
	this->paperCash[0] += rhs.paperCash[0];
	this->paperCash[1] += rhs.paperCash[1];
	this->paperCash[2] += rhs.paperCash[2];
	this->paperCash[3] += rhs.paperCash[3];
	return *this;
	// 작동 확인 완료되었는지?
}

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

Bill& Bill::operator-=(const Bill& rhs) {
	this->paperCash[0] -= rhs.paperCash[0];
	this->paperCash[1] -= rhs.paperCash[1];
	this->paperCash[2] -= rhs.paperCash[2];
	this->paperCash[3] -= rhs.paperCash[3];
	return *this;
	// 작동 확인 완료되었는지?
}

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

void Bill::printBill() {
	cout << "금액 : ";
	for (int i = 0; i < 4; i++) {
		cout << this->value[i] << "원 : " << this->paperCash[i] << "장 ";
	}
	cout << endl;
	cout << "총 액수 : " << this->getSum() << "원" << endl;
}

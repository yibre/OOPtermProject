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

//isValid(int ���¹�ȣ) ���� �Լ� �־����� ���ڴ� 

Account* Database::getAccountByNum(int index) { // ���¹�ȣ �Է��ϸ� ���� ã���ִ� �Լ�; ���� ���� Ȯ�� �ɼ� ����(����)
	// cout << "Debug: This comes from a get account by num fun" << endl;
	return accountList[index]; // �̴�θ� �ִ� index �ʰ��ϴ� ���� ���͵� dummy ������? exception handling ����(����)
}

void Database::addHistory(string transactionType, int money, Account* account, Account* recieverAcc) {
	int order = transactionOrder;
	transactionOrder++;
	string username = account->getOwner()->getUserName();
	int before = account->getBalance();
	int after;
	string receiverName = "-";
	if (transactionType == "�Ա�") {
		after = before + money;
	}
	else if (transactionType == "���") {
		after = before - money;
	}
	else if (transactionType == "�۱�") {
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
	column.push_back("����");
	column.push_back("������");
	column.push_back("���¹�ȣ");
	column.push_back("�ŷ� Ÿ��");
	column.push_back("�ŷ� �� �ܾ�");
	column.push_back("�ŷ� �� �ܾ�");
	column.push_back("�۱ݽ� ������");
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
	increaseID(); // id�� �ο��� �ڿ��� static id�� 1 �߰���
}

bool Account::checkPassword(int uswerAnswer) {
	if (this->password == uswerAnswer) { return true; }
	else { return false; }
}

void Account::deposit(int type, int money) { // �Ա�, �Աݾ� Ÿ��(ĳ��, ��ǥ) �Աݾ� ��ǲ,
	this->balance += money;
} // ����� type�� �ϴ� ���� ����

void Account::withdrawal(int money) { // ���
	this->balance -= money;
}

/*	����(�����̿��� ���ְ�)	*/

void Account::changeBalance(int money) {
	this->balance += money;
}

/*
�� �ؼ� ���±ݾ� �ٲٴ� �Լ� �ϳ� �ΰ�(money�� ����̸� ���ϱ�, �����̸� ����)
����۱ݿ� ��� �������� ����ϸ� ���?
*/

bool Account::isPrimary(ATM* A) {
	if (this->ownerBank->getBankName() == A->getBank()->getBankName()) { return true; }
	// BankID�� ������ �ƴ��� Ȯ���� ���� ������ ���� ID ������ �� �� �ִ� �����ε�
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


bool ATM::deposit(int type, int money, int paperNum, Account* acc) { // �Ա��Լ�, �Աݾ� (type1 : ���� type2 : ��ǥ)
	int fee = 0;
	if (this->getBank() != acc->getBank()) { fee = 500; }
	if (type == 1 && paperNum > 50) {
		cout << "�ִ� �Ա� ���� �� ���� �ʰ��Ͽ����ϴ�. �ٽ� �õ����ֽʽÿ�." << endl; // �Ա� ���� �ִ� �� ���� �����ؾ��ϴµ� ��� �����ؾ��ұ�?
		return false;
	}
	if (type == 2 && paperNum > 30) {
		cout << "�ִ� �Ա� ���� �� ���� �ʰ��Ͽ����ϴ�. �ٽ� �õ����ֽʽÿ�." << endl; // �Ա� ���� �ִ� �� ���� �����ؾ��ϴµ� ��� �����ؾ��ұ�?
		return false;
	}
	acc->deposit(type, money - fee);
	if (type == 1) { this->remainCash += money; }
	else { this->remainCheck += money; this->remainCheckNum += paperNum; }
	cout << money - fee << "���� �ԱݵǾ����ϴ�." << endl;
	cout << "������ : " << fee << " ��" << endl;
	cout << "�ܾ� : " << acc->getBalance() << " ��" << endl;
	return true;
}

bool ATM::withdrawal(int money, Account* acc) { // ����Լ�, ��ݾ�
	int fee = 500;
	if (this->getBank() != acc->getBank()) { fee = 1000; }
	if ((money + fee) > acc->getBalance()) {
		cout << "���¿� �ܾ��� �����մϴ�. �ٽ� �õ����ֽʽÿ�." << endl;
		return false;
	}
	if (money > this->remainCash) {
		cout << "ATM ��⿡ ������ �����մϴ�. �ٽ� �õ����ֽʽÿ�." << endl;
		return false;
	}
	if (money > this->maxWithdrawal) {
		cout << "1ȸ �ִ� ��� �ݾ�(30����)�� �ʰ��Ͽ����ϴ�. �ٽ� �õ����ֽʽÿ�." << endl;
		return false;
	}
	acc->withdrawal(money + fee);
	this->remainCash -= money;
	cout << money << "���� ��ݵǾ����ϴ�. ���Ա��� Ȯ�����ֽʽÿ�." << endl;
	cout << "������ : " << fee << " ��" << endl;
	cout << "�ܾ� : " << acc->getBalance() << " ��" << endl;
	return true;
}

bool ATM::transfer(int type, int money, Account* fromAcc, Account* toAcc) {
	cout << "Debug: ATM::transfer called" << endl;
	cout << "Debug: (�۱� ��)\nfrom account [" << fromAcc->getID() << "]\t ���� �ܾ�: [";
	cout << fromAcc->getBalance() << "]��\nto account [" << toAcc->getID() << "]\t ���� �ܾ�: [";
	cout << toAcc->getBalance() << "]��" << endl;

	int fee = this->fee(7, fromAcc, toAcc);

	if (type == 1) {
		if (fromAcc->getBalance() >= fee) {
			fromAcc->changeBalance(-fee);
			toAcc->changeBalance(money);

			cout << "\t" << money << "���� [" << toAcc->getOwner()->getUserName();
			cout << "] �Կ��� �۱� �Ϸ�Ǿ����ϴ�." << endl;

			cout << "Debug: (�۱� ��)\nfrom account [" << fromAcc->getID() << "]\t ���� �ܾ�: [";
			cout << fromAcc->getBalance() << "]��\nto account [" << toAcc->getID() << "]\t ���� �ܾ�: [";
			cout << toAcc->getBalance() << "]��" << endl;
		}
		else { cout << "Debug: �ܾ� ����" << endl; return false; }
	}
	else if (type == 2) {
		if (fromAcc->getBalance() >= (money + fee)) {
			fromAcc->changeBalance(-(money + fee));
			toAcc->changeBalance(money);

			cout << "\t" << money << "���� [" << toAcc->getOwner()->getUserName();
			cout << "] �Կ��� �۱� �Ϸ�Ǿ����ϴ�." << endl;

			cout << "Debug: (�۱� ��)\nfrom account [" << fromAcc->getID() << "]\t ���� �ܾ�: [";
			cout << fromAcc->getBalance() << "]��\nto account [" << toAcc->getID() << "]\t ���� �ܾ�: [";
			cout << toAcc->getBalance() << "]��" << endl;
		}
		else { cout << "Debug: �ܾ� ����" << endl; return false; }
	}


	// transaction history ����
	return true;
}

int ATM::fee(int transactionType, Account* a1, Account* a2 = nullptr) { // �۱��� ���� a2 �ʿ�
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


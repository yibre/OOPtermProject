#include "UI.h"

using namespace std;

int UI::run() {
	
	Database* DB = Database::getInstance();
	
	Bank* uriBank = new Bank();
	Bank* kakaoBank = new Bank("kakao");
	
	ATM* A1 = new ATM(uriBank, "admin", 1357, 100000000, 100, true);
	ATM* A2 = new ATM(kakaoBank, "master", 2345, 2000000, 0, false);
	
	User* U1 = new User("U1", "�ְ���");
	User* U2 = new User("U2", "�Ǻ���");
	User* U3 = new User("U3", "�����");
	User* U4 = new User("U4", "����");
	User* U5 = new User("U5", "����");
	
	Account* AC1 = new Account(uriBank, U1, 2345, 10000); // ���¹�ȣ 1
	DB->addAccountList(AC1);
	Account* AC2 = new Account(uriBank, U2, 3344, 3000000); // ���¹�ȣ 2
	DB->addAccountList(AC2);
	Account* AC3 = new Account(kakaoBank, U3, 22, 450000); // ���¹�ȣ 3
	DB->addAccountList(AC3);
	Account* AC4 = new Account(kakaoBank, U1, 1024, 1000); // ���¹�ȣ 4
	DB->addAccountList(AC4);

	atm = A1;
	this->database = DB;
	
	acc = AC1;

	while (state != State::End) {
		switch (state) {
		case State::GetAccountNum: // ���¹�ȣ �Է�, �� �� ����
			state = getAccountNum();
			break;
		case State::AccessAccount: // 0 <- admin, 
			state = accessAccount();
			break;
		case State::CheckAccount: // 0 <- admin, 
			state = checkAccount();
			break;
		case State::VerifyAccount: // ���� Ȯ��
			state = verifyAccount();
			break;
		case State::ChooseTransaction: // �ŷ� ����
			state = chooseTransaction();
			break;
		case State::EnterAdmin: // admin panel
			state = enterAdmin();
			break;
		case State::Deposit: // �Ա� ��� �۱� ����
			state = deposit();
			break;
		case State::Withdrawal: // �Ա�
			state = withdrawal();
			break;
		case State::Transfer: // ���
			state = transfer();
			break;
		case State::T_AskTransferType:
			state = t_askTransferType();
			break;
		case State::T_AskToAcc:
			state = t_askToAcc();
			break;
		case State::T_ConfirmToAcc:
			state = t_confirmToAcc();
			break;
		case State::T_AskAmount_C:
			state = t_askAmount_c();
			break;
		case State::T_AskAmount_A:
			state = t_askAmount_a();
			break;
		case State::T_Confirm:
			state = t_confirm();
			break;
		case State::T_Transfer:
			state = t_transfer();
			break;
		case State::End:
			end();
			// delete session (memory deallocation)
			
			delete AC4;
			delete AC3;
			delete AC2;
			delete AC1;

			delete A2;
			delete A1;

			delete U5;
			delete U4;
			delete U3;
			delete U2;
			delete U1;

			delete kakaoBank;
			delete uriBank;
			
			return 0;
		}
	}
	return 0;
}

int UI::getInput(const string& prompt, int maximum, int minimum = 0, bool enableCancel = true) { // maximum �̸�, minimum �̻�;
	int input;
	for (;;) {
		cout << prompt;
		cout.flush(); // Similar to endl, without new line.
		cin >> input;
		if (cin.fail()) { cout << "Wrong type error" << endl; cin.clear(); cin.ignore(256, '\n'); continue; }
		if (enableCancel && input == -1) { cin.clear(); cin.ignore(256, '\n'); break; } // -1�� ��� (range check ������ Ȯ��)
		if (input < minimum || input > maximum) { cout << "Wrong range error" << endl; cin.clear(); cin.ignore(256, '\n'); continue; }
		cin.ignore(256, '\n'); break;
	}
	return input;
}

UI::State UI::getATM() {
	// �ʿ�� ����
	return State::End;
}

UI::State UI::getAccountNum() {
	cout << "\t[*** Welcome ***]" << endl;
	cout << "Please insert your debit card(Enter the account number.)" << endl;
	cout << "Account Num" << endl; // Debug
	return State::AccessAccount;
}

UI::State UI::accessAccount() {
	// from: getAccountNum()
	// �����κ��� ���¹�ȣ �Է¹޴´�
	int input = getInput("your account: ", 99);
	cout << input << endl;
	if (input == 1) {
		// acc (Account*) �� ���� �Ҵ�
		accountNum = input;
		return State::CheckAccount;
	}
	cout << "Canceled; Goto session 0" << endl;
	return State::End;
}

UI::State UI::checkAccount() {
	// from: accessAccount
	// �Է¹��� ���¹�ȣ�� �´��� ����� (���������� �ܰ�)
	string prompt = "\t your account number is: ";
	prompt += to_string(accountNum);
	prompt += "\n\tIs this correct?\t\t(0 to confirm; -1 to cancel)\n";
	int input = getInput(prompt, 0);
	if (input == -1) {
		return State::GetAccountNum;
	}
	else if (input == 0) {
		return State::VerifyAccount;
	}
}

UI::State UI::verifyAccount() {
	// from: checkAccount
	// ��й�ȣ �����
	string prompt = "\t enter the password: ";
	int input = getInput(prompt, 9999, 0, false); // 4�ڸ� �������� �� ��쿡�� 0000~9999
	if (input == -1) { return State::CheckAccount; } // ���� ������ �ʴ´�(enableCancel = false)
	else {
		if (acc->checkPassword(input)) {
			// TODO: pw 3�� Ʋ���� �ڷ� ���ư��� ��� �߰� -by DY
			return State::ChooseTransaction;
		}
		cout << "Wrong password" << endl;
		return State::GetAccountNum;
	}
}

UI::State UI::enterAdmin() {
	cout << "enter admin class" << endl;
	return State::GetAccountNum;
}

UI::State UI::chooseTransaction() {
	// from: verifyAccount
	// from: t_askTransferType (if canceled)
	string prompt = "\tWhat would you like to do?\n\t1. deposit\t 2. withdrawal\t 3. transfer\n";
	int input = getInput(prompt, 3);
	if (input == -1) {
		// ��ҽ� ī�� ��ȯ�� �ְ� ī�� �޴� �ܰ�� ���ư�
		cout << "Your card has returned." << endl;
		return State::GetAccountNum;
		}
	if (input == 1) { return State::Deposit; }
	else if (input == 2) { return State::Withdrawal; }
	else if (input == 3) { return State::Transfer; }
	else cout << "wrong input, choose it again" << endl;
	return State::ChooseTransaction;
}

/***********************	   Deposit   	***********************/

UI::State UI::deposit() {
	// from: chooseTransaction
	cout << "\t[deposit]" << endl;
	return State::ChooseTransaction;
}

/***********************	 Withdrawal  	***********************/

UI::State UI::withdrawal() {
	// from: chooseTransaction
	cout << "\t[withdrawal]" << endl;
	return State::ChooseTransaction;
}

/***********************	  Transfer  	***********************/

UI::State UI::transfer() {
	// from: chooseTransaction
	// from: 
	cout << "\t[transfer]" << endl;
	// Ȥ�� �𸣴� �ʱ�ȭ
	fee = 0;
	toAccID = 0;
	toAcc = nullptr; 
	return State::T_AskTransferType;
}

UI::State UI::t_askTransferType() {
	// from: transfer
	int input;
	
	string prompt = "Which transfer option would you like? ���Ͻô� �۱� �ɼ��� ������ �ֽʽÿ�.\n";
	prompt += "\t1. cash transfer ���� �۱�\t 2. account transfer ���� �۱�\n\tcancel ���: -1\n";
	input = getInput(prompt, 2);
	if (input == -1) { 
	cout << "You have exited [transfer] session. �۱��� ����ϼ̽��ϴ�." << endl;
	return State::ChooseTransaction;
	}

	transferType = input; // Exception handling �ʿ�
	if (transferType == 1) { cout << "You have chosen [cash transfer]. ���� �۱��� �����ϼ̽��ϴ�." << endl; }
	if (transferType == 2) { cout << "You have chosen [account transfer]. ���� �۱��� �����ϼ̽��ϴ�." << endl; }
	return State::T_AskToAcc;
}


UI::State UI::t_askToAcc() {
	// from: 
	int input;
	string prompt = "Please enter the account you would like to transfer your money to.";
	prompt += " �۱��Ͻ� ������ ���¹�ȣ�� �Է��� �ֽʽÿ�.\n\tcancel ���: -1\n";
	// input = getInput(prompt, 99999, 10000); // ���¹�ȣ �޾ƾ� �ϴϱ�
	input = getInput(prompt, 5); // �ӽ�
	if (input == -1) { return State::Transfer; }
	toAccID = input;
	toAcc = database->getAccountByNum(toAccID); // database ��� (���߿� �ٲ�� �� ����)
	return State::T_ConfirmToAcc;
}

UI::State UI::t_confirmToAcc() { // �����Ǹ���
	// from: t_askToAcc
	
	fee = atm->fee(7, acc, toAcc); // fee �Լ� �����Ǹ� ���� �ٲ��
	
	int input;
	string prompt = "[" + toAcc->getOwner()->getUserName();
	prompt += ("] ���� ���� [" + std::to_string(toAccID));
	prompt += "]�� �½��ϱ�?\n\t0. yes ��\t1. try different account �ٽ� �Է�\n\tcancel ���: -1\n";
	input = getInput(prompt, 1);
	// ���� �������� Ȯ���ϱ� - to be done
	if (input == -1) { return State::ChooseTransaction; }
	if (input == 0) {
		if (transferType == 1) { return State::T_AskAmount_C; }
		else { return State::T_AskAmount_A; }
	}
	if (input == 1) { return State::T_AskToAcc;}
	
	cout << "Debug: Unexpected behavior in UI::t_confirmToAcc" << endl;
	return State::End;
}

UI::State UI::t_askAmount_c() {
	// from: t_askToAcc (when transferType == 1)
	
	cout << "Debug: ������� [" << fee << "]���Դϴ�." << endl;
	
	int input;
	transferAmount = 0; // = insertedBill.sum();
	string prompt = "Please insert cash you would like to transfer.";
	prompt += " �۱��� ������ ������ �ֽʽÿ�.\n\tcancel ���: -1\n";
	// ���� valid���� check; Bill ����ϰ� �ٲٱ� (�Ա��ʿ��� ������ �Լ� ���)
	// transferAmount = insertedBill.sum();
	cout << "Debug: cash transfer; transfer amount: ";
	cin >> transferAmount; // temporary; to be done
	
	// ���ݼ۱ݿ� ���� ������ �׼� ��谡 �� �� �׼� �´��� Ȯ�� �ʿ� REQ6.3
	prompt = "�����Ͻ� �ݾ��� Ȯ���� �ֽʽÿ�.\n\t[" + std::to_string(transferAmount);
	prompt += "]��\n\t0. confirm Ȯ��\n\tcancel ���: -1\n";
	input = getInput(prompt, 0);
	// �̺κ� ���� �Լ��� ����
	
	if (input == 0) { return State::T_Confirm; }
	if (input == -1) { 
		cout << "You have exited [transfer] session. �۱��� ����ϼ̽��ϴ�." << endl; // ���� ���� �� ��?
		cout << "Your cash has returned. �����Ͻ� ������ ��ȯ�Ǿ����ϴ�.";
		cout << " Please make sure to take your cash. ���Ա��� Ȯ�����ּ���." << endl;
		return State::ChooseTransaction; // ���� ���� �� ��?
	}
	
	cout << "Debug: Unexpected behavior in UI::t_askAmount_c" << endl;
	return State::End;
}


UI::State UI::t_askAmount_a() {
	// from: t_askToAcc (when transferType == 2)
	
	cout << "Debug: ������� [" << fee << "]���Դϴ�." << endl;
	
	transferAmount = 0;
	string prompt = "Please enter the amount of money you would like to transfer.";
	prompt += " �۱��� �ݾ��� �Է��� �ֽʽÿ�. (Your current balance ���� �ܾ�: ";
	prompt += std::to_string(acc->getBalance());
	prompt += ")\n\tcancel ���: -1\n";
	// �׼� valid���� check�ϱ�(���� �ܾ�, �۱��ѵ� ��;) - to be done
	/*
	if (transferMoney > fromAcc->getBalance()) {
		cout << "Not enough balance error. �ܾ��� �����մϴ�.(code 706)" << endl; // �ܾ� ���� ���ϱ�� ���� �۱� Ȯ�� �Ŀ��� �ұ�? (������ ��� ����)
	}
	*/
	cout << "Debug: account transfer; transfer amount: ";
	cin >> transferAmount; // temporary; to be done
	
	int input;
	input = getInput(prompt, 0);
	if (input == 0) { return State::T_Confirm; }
	if (input == -1) {
		cout << "You have exited [transfer] session. �۱��� ����ϼ̽��ϴ�." << endl; // ���� ���� �� ��?
		return State::ChooseTransaction; // ���� ���� �� ��?
	}
	
	cout << "Debug: Unexpected behavior in UI::t_askAmount_a" << endl;
	return State::End;
}

UI::State UI::t_confirm() {
	// from: t_askAmount_a
	// from: t_askAmount_c
	
	string prompt = "[" + toAcc->getOwner()->getUserName() + "] �Կ��� [";
	prompt += (std::to_string(transferAmount) + "]�� �۱��Ͻðڽ��ϱ�?\n������� [");
	prompt += (std::to_string(fee) + "]���Դϴ�. ������� ���� ���� �ܾ� [");
	prompt += std::to_string(acc->getBalance());
	prompt += "]������ �ڵ� �����˴ϴ�.\n\t0. confirm Ȯ��\n\tcancel ���: -1\n";
	
	int input;
	input = getInput(prompt, 0);
	if (input == 0) { return State::T_Transfer; }
	if (input == -1) { 
		cout << "You have exited [transfer] session. �۱��� ����ϼ̽��ϴ�." << endl;
		if (transferType == 1) {
			cout << "Your cash has returned. �����Ͻ� ������ ��ȯ�Ǿ����ϴ�.";
			cout << " Please make sure to take your cash. ���Ա��� Ȯ�����ּ���." << endl;
		}
		return State::ChooseTransaction; 
	}
	
	cout << "Debug: Unexpected behavior in UI::t_confirm" << endl;
	return State::End;
}

UI::State UI::t_transfer() {
	// from: t_confirm
	bool success = atm->transfer(transferType, transferAmount, acc, toAcc);
	if (success) {
		// �۱� Ȯ�εǾ� ��ȯ�� ���� ���� �� remainCash transferAmount��ŭ �ø���
		if (transferType == 1) {
			atm->insertCash(transferAmount); // Bill class ������ ���� �ٸ� �� ����
			cout << "Debug: Remaining cash of the ATM : " << atm->getATMremainCash() << endl; // ���� �ʿ�
		}
		// ��ǥ ���?
		return State::ChooseTransaction;
	}
	else {
		cout << "Not enough balance. �ܾ��� �����մϴ�." << endl;
		if (transferType == 1) { 
			cout << "Your cash has returned. �����Ͻ� ������ ��ȯ�Ǿ����ϴ�.";
			cout << "Please make sure to take your cash. ���Ա��� Ȯ�����ּ���." << endl;  // �̰� �ƿ� �ٸ� �ܰ�� �����?
		}
		return State::ChooseTransaction; // ���� ���� �� ��?
	}
}

UI::State UI::session3Confirm() {
	string Number = to_string(FirstDigit) + to_string(SecondDigit);
	int input = getInput("\tYour number: " + Number + "\n\tIs this final result correct?\t\t(1 to confirm; 0 to cancel)\n", 1);
	if (input) {
		cout << "\tYOUR NUMBER: " << Number << endl;
		return State::End;
	}
	cout << "Canceled; Goto session 2" << endl;
	return State::Session2Prompt;
}

void UI::end() {
	
}
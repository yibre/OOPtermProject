#include "UI.h"

using namespace std;

int UI::run() {
	Bank* uriBank = new Bank();
	ATM* A1 = new ATM(uriBank, "admin", 1357, 100000000, 100, true);
	User* U1 = new User("U1", "최가난");
	User* U2 = new User("U2", "권부자");
	Account* AC1 = new Account(uriBank, U1, 2345, 10000);

	atm = A1;
	myAccount = AC1;

	while (state != State::End) {
		switch (state) {
		case State::GetAccountNum: // 계좌번호 입력, 한 영 선택
			state = getAccountNum();
			break;
		case State::AccessAccount: // 0 <- admin, 
			state = accessAccount();
			break;
		case State::CheckAccount: // 0 <- admin, 
			state = checkAccount();
			break;
		case State::VerifyAccount: // 본인 확인
			state = verifyAccount();
			break;
		case State::ChooseTransaction: // 거래 선택
			state = chooseTransaction();
			break;
		case State::EnterAdmin: // admin panel
			state = enterAdmin();
			break;
		case State::Deposit: // 입금 출금 송금 선택
			state = deposit();
			break;
		case State::Withdrawal: // 입금
			state = withdrawal();
			break;
		case State::Transfer: // 출금
			state = transfer();
			break;
		}
	}
	return 0;
}

int UI::getInput(const string& prompt, int maximum, int minimum = 0) {
	int input;
	for (;;) {
		cout << prompt;
		cout.flush(); // Similar to endl, without new line.
		cin >> input;
		if (cin.fail()) { cout << "Wrong type error" << endl; cin.clear(); cin.ignore(256, '\n'); continue; }
		if (input < minimum || input > maximum) { cout << "Wrong range error" << endl; cin.clear(); cin.ignore(256, '\n'); continue; }
		cin.ignore(256, '\n'); break;
	}
	return input;
}

UI::State UI::getAccountNum() {
	cout << "\t[session 1]" << endl;
	cout << "type the account number." << endl;
	cout << "Account Num" << endl;
	return State::AccessAccount;
}

UI::State UI::accessAccount() {
	int input = getInput("your account: ", 99);
	cout << input << endl;
	if (input == 1) {
		// myAccount (Account*) 계좌 할당
		cout << "hello1" << endl;
		accountNum = input;
		return State::CheckAccount;
	}
	cout << "hello3" << endl;
	cout << "Canceled; Goto session 0" << endl;
	return State::End;
}

UI::State UI::checkAccount() {
	cout << "hello2" << endl;
	string prompt = "\t your account number is: ";
	prompt += to_string(accountNum);
	prompt += "\n\tIs this correct?\t\t(1 to confirm; 0 to cancel)\n";
	int input = getInput(prompt, 1);
	if (input == 0) {
		return State::GetAccountNum;
	}
	else if (input == 1) {
		return State::VerifyAccount;
	}
}

UI::State UI::verifyAccount() {
	string prompt = "\t enter the password: ";
	int input = getInput(prompt, 100000, 1000);
	if (input == 0) { return State::CheckAccount; }
	else {
		if (myAccount->checkPassword(input)) {
			// TODO: pw 3번 틀리면 뒤로 돌아가는 기능 추가 -by DY
			cout << "hello6" << endl;
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
	string prompt = "\t choose your transaction type. 1. deposit 2. withdrawal, 3. transfer \n";
	int input = getInput(prompt, 4);
	if (input == 1) return State::Deposit;
	else if (input == 2) return State::Withdrawal;
	else if (input == 3) return State::Transfer;
	else cout << "wrong input, choose it again" << endl;
	return State::ChooseTransaction;
}

UI::State UI::deposit() {
	cout << "[deposit]" << endl;
	return State::ChooseTransaction;
}

UI::State UI::withdrawal() {
	cout << "[withdrawal]" << endl;
	return State::ChooseTransaction;
}

UI::State UI::transfer() {
	cout << "[transfer]" << endl;
	return State::ChooseTransaction;
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
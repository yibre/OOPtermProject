#include "UI.h"

using namespace std;

int UI::run() {
	Bank* uriBank = new Bank();
	ATM* A1 = new ATM(uriBank, "admin", 1357, 100000000, 100, true);
	User* U1 = new User("U1", "최가난");
	User* U2 = new User("U2", "권부자");
	Account* AC1 = new Account(uriBank, U1, 2345, 10000);

	atm = A1;
	acc = AC1;

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

int UI::getInput(const string& prompt, int maximum, int minimum = 0, bool enableCancel = true) { // maximum 미만, minimum 이상;
	int input;
	for (;;) {
		cout << prompt;
		cout.flush(); // Similar to endl, without new line.
		cin >> input;
		if (cin.fail()) { cout << "Wrong type error" << endl; cin.clear(); cin.ignore(256, '\n'); continue; }
		if (enableCancel && input == -1) { cin.clear(); cin.ignore(256, '\n'); break; } // -1은 취소 (range check 이전에 확인)
		if (input < minimum || input > maximum) { cout << "Wrong range error" << endl; cin.clear(); cin.ignore(256, '\n'); continue; }
		cin.ignore(256, '\n'); break;
	}
	return input;
}

UI::State UI::getATM() {
	// 필요시 구현
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
	// 유저로부터 계좌번호 입력받는다
	int input = getInput("your account: ", 99);
	cout << input << endl;
	if (input == 1) {
		// acc (Account*) 에 계좌 할당
		accountNum = input;
		return State::CheckAccount;
	}
	cout << "Canceled; Goto session 0" << endl;
	return State::End;
}

UI::State UI::checkAccount() {
	// from: accessAccount
	// 입력받은 계좌번호가 맞는지 물어본다 (생략가능한 단계)
	string prompt = "\t your account number is: ";
	prompt += to_string(accountNum);
	prompt += "\n\tIs this correct?\t\t(1 to confirm; -1 to cancel)\n";
	int input = getInput(prompt, 1);
	if (input == -1) {
		return State::GetAccountNum;
	}
	else if (input == 1) {
		return State::VerifyAccount;
	}
}

UI::State UI::verifyAccount() {
	// from: checkAccount
	// 비밀번호 물어본다
	string prompt = "\t enter the password: ";
	int input = getInput(prompt, 100000, /*1000,*/ false);
	if (input == -1) { return State::CheckAccount; }
	else {
		if (acc->checkPassword(input)) {
			// TODO: pw 3번 틀리면 뒤로 돌아가는 기능 추가 -by DY
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
	//from: verifyAccount
	string prompt = "\tWhat would you like to do?\n\t1. deposit\t 2. withdrawal\t 3. transfer\n";
	int input = getInput(prompt, 4);
	if (input == -1) {
		// 취소시 카드 반환해 주고 카드 받는 단계로 돌아감
		cout << "Your card has returned." << endl;
		return State::GetAccountNum;
		}
	if (input == 1) { return State::Deposit; }
	else if (input == 2) { return State::Withdrawal; }
	else if (input == 3) { return State::Transfer; }
	else cout << "wrong input, choose it again" << endl;
	return State::ChooseTransaction;
}

UI::State UI::deposit() {
	cout << "\t[deposit]" << endl;
	return State::ChooseTransaction;
}

UI::State UI::withdrawal() {
	cout << "\t[withdrawal]" << endl;
	return State::ChooseTransaction;
}

UI::State UI::transfer() {
	cout << "\t[transfer]" << endl;
	int input = 0;
	/*
	// cash transfer인지 account transfer인지 묻기
				int transferType; // for loop 안에서의 local variable; 재정의 issue 없음
				string prompt = "Which transfer option would you like? 원하시는 송금 옵션을 선택해 주십시오.\n"
				prompt += "\t1. cash transfer 현금 송금\t 2. account transfer 계좌 송금\n\tcancel 취소: -1"
				input = getInput(prompt, 4);

				transferType = input; // Exception handling 필요
					if (transferType == 1) { cout << "You have chosen [cash transfer]. 현금 송금을 선택하셨습니다." << endl; break; }
					if (transferType == 2) { cout << "You have chosen [account transfer]. 계좌 송금을 선택하셨습니다." << endl; break; }
					if (transferType == -1) { cout << "You have exited [transfer] session. 송금을 취소하셨습니다." << endl; break; }
				if (transferType == -1) { UserStatus = 4; break; }
	*/
	
	
	if (input == -1) { return State::ChooseTransaction; }
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
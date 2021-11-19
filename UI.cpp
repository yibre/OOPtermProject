#include "UI.h"

using namespace std;

int UI::run() {

	Database* DB = Database::getInstance();

	Bank* uriBank = new Bank();
	Bank* kakaoBank = new Bank("kakao");

	Bill* A1_bill = new Bill(100, 1, 500, 1000);
	Bill* A2_bill = new Bill(100, 100, 100, 100);
	ATM* A1 = new ATM(uriBank, "admin", 1357, A1_bill, 100, true); // 0
	ATM* A2 = new ATM(kakaoBank, "master", 2345, A2_bill, 0, false); // 1

	User* U1 = new User("U1", "최가난");
	User* U2 = new User("U2", "권부자");
	User* U3 = new User("U3", "서모녀");
	User* U4 = new User("U4", "김백규");
	User* U5 = new User("U5", "버터");

	Account* AC1 = new Account(uriBank, U1, 2345, 10000); // 계좌번호 1
	DB->addAccountList(AC1);
	Account* AC2 = new Account(uriBank, U2, 3344, 3000000); // 계좌번호 2
	DB->addAccountList(AC2);
	Account* AC3 = new Account(kakaoBank, U3, 22, 450000); // 계좌번호 3
	DB->addAccountList(AC3);
	Account* AC4 = new Account(kakaoBank, U1, 1024, 1000); // 계좌번호 4
	DB->addAccountList(AC4);

	atm = A1;
	this->database = DB;

	acc = AC1;

	while (state != State::End) {
		switch (state) {
		case State::GetAccountNum: // 계좌번호 입력, 한 영 선택
			state = getAccountNum();
			break;
		case State::AccessAccount: // 0 <- admin, 
			state = accessAccount();
			break;
		case State::VerifyAdmin:
			state = verifyAdmin();
			break;
		case State::ShowAdmin: // 본인 확인
			state = showAdmin();
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
		case State::Deposit: // 입금 출금 송금 선택
			state = deposit();
			break;
		case State::Withdrawal: // 입금
			state = withdrawal();
			break;
		case State::Transfer: // 출금
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
	int input = getInput("your account: ", 100000);
	cout << input << endl;
	if (input == 1) {
		// acc (Account*) 에 계좌 할당
		accountNum = input;
		return State::CheckAccount;
	}
	else if (input == 99999) {
		return State::VerifyAdmin;
	}
	cout << "Canceled; Goto session 0" << endl;
	return State::End;
}

UI::State UI::verifyAdmin() {
	cout << "you inserted admin card." << endl;
	int input = getInput("Enter the password to access admin panel: ", 10000);
	if (atm->checkPW(input)) { return State::ShowAdmin; }
	else {
		cout << "You entered wrong password." << endl;
		return State::GetAccountNum;
	}
}

UI::State UI::showAdmin() {
	// TODO: show history 
	cout << "enter admin class" << endl;
	database->addHistory("입금", 15000, acc, acc);
	database->printHistory();
	return State::GetAccountNum;
}

UI::State UI::checkAccount() {
	// from: accessAccount
	// 입력받은 계좌번호가 맞는지 물어본다 (생략가능한 단계)
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
	// 비밀번호 물어본다
	string prompt = "\t enter the password: ";
	int input = getInput(prompt, 9999, 0, false); // 4자리 수이지만 이 경우에는 0000~9999
	if (input == -1) { return State::CheckAccount; } // 현재 쓰이지 않는다(enableCancel = false)
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
	// from: verifyAccount
	// from: t_askTransferType (if canceled)
	string prompt = "\tWhat would you like to do?\n\t1. deposit\t 2. withdrawal\t 3. transfer\n";
	int input = getInput(prompt, 3);
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
	// 혹시 모르니 초기화
	fee = 0;
	toAccID = 0;
	toAcc = nullptr;
	return State::T_AskTransferType;
}

UI::State UI::t_askTransferType() {
	// from: transfer
	int input;

	string prompt = "Which transfer option would you like? 원하시는 송금 옵션을 선택해 주십시오.\n";
	prompt += "\t1. cash transfer 현금 송금\t 2. account transfer 계좌 송금\n\tcancel 취소: -1\n";
	input = getInput(prompt, 2);
	if (input == -1) {
		cout << "You have exited [transfer] session. 송금을 취소하셨습니다." << endl;
		return State::ChooseTransaction;
	}

	transferType = input; // Exception handling 필요
	if (transferType == 1) { cout << "You have chosen [cash transfer]. 현금 송금을 선택하셨습니다." << endl; }
	if (transferType == 2) { cout << "You have chosen [account transfer]. 계좌 송금을 선택하셨습니다." << endl; }
	return State::T_AskToAcc;
}


UI::State UI::t_askToAcc() {
	// from: 
	int input;
	string prompt = "Please enter the account you would like to transfer your money to.";
	prompt += " 송금하실 계좌의 계좌번호를 입력해 주십시오.\n\tcancel 취소: -1\n";
	// input = getInput(prompt, 99999, 10000); // 계좌번호 받아야 하니까
	input = getInput(prompt, 5); // 임시
	if (input == -1) { return State::Transfer; }
	toAccID = input;
	toAcc = database->getAccountByNum(toAccID); // database 사용 (나중에 바꿔야 할 수도)
	return State::T_ConfirmToAcc;
}

UI::State UI::t_confirmToAcc() { // 금융실명제
	// from: t_askToAcc

	fee = atm->fee(7, acc, toAcc); // fee 함수 수정되면 따라 바꿔야

	int input;
	string prompt = "[" + toAcc->getOwner()->getUserName();
	prompt += ("] 님의 계좌 [" + std::to_string(toAccID));
	prompt += "]가 맞습니까?\n\t0. yes 예\t1. try different account 다시 입력\n\tcancel 취소: -1\n";
	input = getInput(prompt, 1);
	// 같은 계좌인지 확인하기 - to be done
	if (input == -1) { return State::ChooseTransaction; }
	if (input == 0) {
		if (transferType == 1) { return State::T_AskAmount_C; }
		else { return State::T_AskAmount_A; }
	}
	if (input == 1) { return State::T_AskToAcc; }

	cout << "Debug: Unexpected behavior in UI::t_confirmToAcc" << endl;
	return State::End;
}

UI::State UI::t_askAmount_c() {
	// from: t_askToAcc (when transferType == 1)

	cout << "Debug: 수수료는 [" << fee << "]원입니다." << endl;

	int input;
	transferAmount = 0; // = insertedBill.sum();
	string prompt = "Please insert cash you would like to transfer.";
	prompt += " 송금할 현금을 투입해 주십시오.\n\tcancel 취소: -1\n";
	// 투입 valid한지 check; Bill 사용하게 바꾸기 (입금쪽에서 구현된 함수 사용)
	// transferAmount = insertedBill.sum();
	cout << "Debug: cash transfer; transfer amount: ";
	cin >> transferAmount; // temporary; to be done

	// 현금송금에 한해 투입한 액수 기계가 센 후 액수 맞는지 확인 필요 REQ6.3
	prompt = "투입하신 금액을 확인해 주십시오.\n\t[" + std::to_string(transferAmount);
	prompt += "]원\n\t0. confirm 확인\n\tcancel 취소: -1\n";
	input = getInput(prompt, 0);
	// 이부분 따로 함수로 빼기

	if (input == 0) { return State::T_Confirm; }
	if (input == -1) {
		cout << "You have exited [transfer] session. 송금을 취소하셨습니다." << endl; // 어디로 가게 할 것?
		cout << "Your cash has returned. 투입하신 현금이 반환되었습니다.";
		cout << " Please make sure to take your cash. 투입구를 확인해주세요." << endl;
		return State::ChooseTransaction; // 어디로 가게 할 것?
	}

	cout << "Debug: Unexpected behavior in UI::t_askAmount_c" << endl;
	return State::End;
}


UI::State UI::t_askAmount_a() {
	// from: t_askToAcc (when transferType == 2)

	cout << "Debug: 수수료는 [" << fee << "]원입니다." << endl;

	transferAmount = 0;
	string prompt = "Please enter the amount of money you would like to transfer.";
	prompt += " 송금할 금액을 입력해 주십시오. (Your current balance 계좌 잔액: ";
	prompt += std::to_string(acc->getBalance());
	prompt += ")\n\tcancel 취소: -1\n";
	// 액수 valid한지 check하기(계좌 잔액, 송금한도 등;) - to be done
	/*
	if (transferMoney > fromAcc->getBalance()) {
		cout << "Not enough balance error. 잔액이 부족합니다.(code 706)" << endl; // 잔액 부족 말하기는 최종 송금 확인 후에만 할까? (수수료 고려 위해)
	}
	*/
	cout << "Debug: account transfer; transfer amount: ";
	cin >> transferAmount; // temporary; to be done

	int input;
	input = getInput(prompt, 0);
	if (input == 0) { return State::T_Confirm; }
	if (input == -1) {
		cout << "You have exited [transfer] session. 송금을 취소하셨습니다." << endl; // 어디로 가게 할 것?
		return State::ChooseTransaction; // 어디로 가게 할 것?
	}

	cout << "Debug: Unexpected behavior in UI::t_askAmount_a" << endl;
	return State::End;
}

UI::State UI::t_confirm() {
	// from: t_askAmount_a
	// from: t_askAmount_c

	string prompt = "[" + toAcc->getOwner()->getUserName() + "] 님에게 [";
	prompt += (std::to_string(transferAmount) + "]원 송금하시겠습니까?\n수수료는 [");
	prompt += (std::to_string(fee) + "]원입니다. 수수료는 현재 계좌 잔액 [");
	prompt += std::to_string(acc->getBalance());
	prompt += "]원에서 자동 차감됩니다.\n\t0. confirm 확인\n\tcancel 취소: -1\n";

	int input;
	input = getInput(prompt, 0);
	if (input == 0) { return State::T_Transfer; }
	if (input == -1) {
		cout << "You have exited [transfer] session. 송금을 취소하셨습니다." << endl;
		if (transferType == 1) {
			cout << "Your cash has returned. 투입하신 현금이 반환되었습니다.";
			cout << " Please make sure to take your cash. 투입구를 확인해주세요." << endl;
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
		// 송금 확인되어 반환의 여지 없을 때 remainCash transferAmount만큼 늘리기
		if (transferType == 1) {
			// atm->insertCash(transferAmount); // Bill class 구현에 따라 다를 수 있음
			cout << "Debug: Remaining cash of the ATM : " << atm->getATMremainCash() << endl; // 수정 필요
		}
		// 명세표 출력?
		return State::ChooseTransaction;
	}
	else {
		cout << "Not enough balance. 잔액이 부족합니다." << endl;
		if (transferType == 1) {
			cout << "Your cash has returned. 투입하신 현금이 반환되었습니다.";
			cout << "Please make sure to take your cash. 투입구를 확인해주세요." << endl;  // 이걸 아예 다른 단계로 만들까?
		}
		return State::ChooseTransaction; // 어디로 가게 할 것?
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
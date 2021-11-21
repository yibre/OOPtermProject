#include "UI.h"

using namespace std;

int UI::run() {

	Database* DB = Database::getInstance();

	Bank* uriBank = new Bank();
	Bank* kakaoBank = new Bank("kakao");

	Bill* A1_bill = new Bill(100, 200, 500, 1000);
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
		case State::D_AskDepositType:
			state = d_askDepositType();
			break;
		case State::D_AskAmount_Cash:
			state = d_askAmount_Cash();
			break;
		case State::D_AskAmount_Check:
			state = d_askAmount_Check();
			break;
		case State::D_Confirm_Cash:
			state = d_confirm_Cash();
			break;
		case State::D_Confirm_Check:
			state = d_confirm_Check();
			break;
		case State::D_ConfirmTotal:
			state = d_confirmTotal();
			break;
		case State::D_Deposit:
			state = d_deposit();
			break;
		case State::Withdrawal: // 입금
			state = withdrawal();
			break;
		case State::W_AskAmount:
			state = w_askAmount();
			break;
		case State::W_CheckAccountBalance:
			state = w_checkAccountBalance();
			break;
		case State::W_CheckMaxAmount:
			state = w_checkMaxAmount();
			break;
		case State::W_CheckATMBalance:
			state = w_checkATMBalance();
			break;
		case State::W_Confirm:
			state = w_confirm();
			break;
		case State::W_Withdrawal:
			state = w_withdrawal();
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

int* UI::getInputArray(const string& prompt, int length, int maximum, int minimum = 0, bool enableCancel = true) { // maximum 미만, minimum 이상;
	int *input = new int[30];
	cout << prompt;
	cout.flush(); // Similar to endl, without new line.
	for (int i = 0; i < length; i++) {
		int temp;
		for (;;) {
			cin >> temp;
			if (cin.fail()) { cout << "Wrong type error" << endl; cin.clear(); cin.ignore(256, '\n'); continue; }
			if (enableCancel && temp == -1) { cin.clear(); cin.ignore(256, '\n'); break; } // -1은 취소 (range check 이전에 확인)
			if (temp < minimum || temp > maximum) { cout << "Wrong range error" << endl; cin.clear(); cin.ignore(256, '\n'); continue; }
			cin.ignore(256, '\n'); break;
		}
		if (temp == -1) {
			input[0] = -1;
			return input;
		}
		input[i] = temp;
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
	accountNum = getInput("your account: ", 100000);

	if (accountNum == 99999) {
		return State::VerifyAdmin;
	}
	else if(accountNum == -1){
		cout << "Canceled; Goto session 0" << endl;
		return State::End;
	}
	userIndex = database->getIndexFromID(accountNum);
	if (userIndex == -1) {
		cout << "Canceled; Goto session 0" << endl;
		return State::End;
	}
	acc = database->getAccountByNum(userIndex);
	return State::CheckAccount;
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
	string prompt = "\tWhat would you like to do?\n\t1. deposit\t 2. withdrawal\t 3. transfer\n\tCancel : -1\n";
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
	fee = atm->fee(5, acc, nullptr);
	transactionAmount = 0;
	int depositCheckNum = 0;
	int depositCheckSum = 0;
	return State::D_AskDepositType;
}

UI::State UI::d_askDepositType() {
	string prompt = "현금, 수표 중 입금하실 방법을 선택해주십시오.\n\t";
	prompt += "1. cash 현금\t2. check 수표\t취소: -1\n";

	transactionType = getInput(prompt, 2);
	if (transactionType == -1) {
		cout << "입금을 취소하셨습니다." << endl;
		return State::ChooseTransaction;
	}

	if (transactionType == 1) {
		cout << "현금 입금을 선택하셨습니다." << endl;
		return State::D_AskAmount_Cash;
	}
	else if (transactionType == 2) {
		cout << "수표 입금을 선택하셨습니다." << endl;
		return State::D_AskAmount_Check;
	}
	else {
		cout << "Canceled; Goto session 0" << endl;
		return State::End;
	}
}

UI::State UI::d_askAmount_Cash() {
	cout << "Debug: 수수료는 [" << fee << "]원입니다." << endl;

	string prompt = "투입구에 현금을 넣어주십시오. (5만원권, 1만원권, 5천원권, 1천원권 순으로 입력해주세요.)\n\t";
	prompt += "취소 : -1\n";
	int* input;
	input = getInputArray(prompt, 4, 500);
	if (input[0] == -1) {
		cout << "입금을 취소하셨습니다." << endl;
		return State::ChooseTransaction;
	}
	transactionBill = Bill{ input[0], input[1], input[2], input[3] };
	if (transactionBill.getTotalNum() > 50) {
		cout << "최대 입금 가능 장 수를 초과하였습니다. 다시 시도해주십시오." << endl;
		return State::D_AskAmount_Cash;
	}
	if (transactionBill.getTotalNum() == 0) {
		cout << "투입구에 현금이 들어있지 않습니다. 다시 시도해주십시오." << endl;
		return State::D_AskAmount_Cash;
	}
	transactionBill = Bill{ input[0], input[1], input[2], input[3] };
	return State::D_Confirm_Cash;
}

UI::State UI::d_askAmount_Check() {
	cout << "Debug: 수수료는 [" << fee << "]원입니다." << endl;

	string prompt = "투입하실 수표의 장 수를 입력해주세요.\n\t";
	prompt += "취소 : -1\n";
	depositCheckNum = getInput(prompt, 500);
	if (depositCheckNum == -1) {
		cout << "입금을 취소하셨습니다." << endl;
		return State::ChooseTransaction;
	}
	else if (depositCheckNum == 0) {
		cout << "투입구에 수표가 들어있지 않습니다. 다시 시도해주십시오." << endl;
		return State::D_AskAmount_Check;
	}
	else if (depositCheckNum > 30) {
		cout << "최대 입금 가능 장 수를 초과하였습니다. 다시 시도해주십시오." << endl;
		return State::D_AskAmount_Check;
	}
	string prompt2 = "각 수표의 액수를 입력해주세요.\n";
	int* input;
	input = getInputArray(prompt2, depositCheckNum, 100000000);
	if (input[0] == -1) {
		cout << "입금을 취소하셨습니다." << endl;
		return State::ChooseTransaction;
	}
	depositCheckInput = input;
	return State::D_Confirm_Check;
}

UI::State UI::d_confirm_Cash() {
	cout << "투입하신 금액이 맞는지 확인해 주십시오.\n 확인 : 0 \t 취소 : -1" << endl;
	transactionBill.printBill();
	int input = getInput("", 0);
	if (input == -1) {
		cout << "현금 입금을 취소하셨습니다." << endl;
		cout << "투입하신 현금이 반환되었습니다." << endl;
		cout << "투입구를 확인해주세요." << endl;
		return State::ChooseTransaction;
	}
	else if (input == 0) {
		return State::D_ConfirmTotal;
	}
	else {
		cout << "Error" << endl;
		return State::End;
	}
}

UI::State UI::d_confirm_Check() {
	cout << "투입하신 금액이 맞는지 확인해 주십시오.\n 확인 : 0 \t 취소 : -1" << endl;
	cout << "금액 : ";
	for (int i = 0; i < depositCheckNum; i++) {
		cout << depositCheckInput[i] << "원 ";
		depositCheckSum += depositCheckInput[i];
	}
	cout << endl;
	int input = getInput("", 0);
	if (input == -1) {
		cout << "수표 입금을 취소하셨습니다." << endl;
		cout << "투입하신 수표가 반환되었습니다." << endl;
		cout << "투입구를 확인해주세요." << endl;
		return State::ChooseTransaction;
	}
	else if (input == 0) {
		return State::D_ConfirmTotal;
	}
	else {
		cout << "Error" << endl;
		return State::End;
	}
}

UI::State UI::d_confirmTotal() {
	int depositAmount = 0;
	if (transactionType == 1) {
		depositAmount = transactionBill.getSum();
	}
	else if (transactionType == 2) {
		depositAmount = depositCheckSum;
	}
	else { cout << "Error" << endl; return State::End; }
	string prompt = "계좌로 [";
	prompt += (to_string(depositAmount) + "]원 입금하시겠습니까?\n수수료는 [");
	prompt += (to_string(fee) + "]원입니다. 수수료는 현재 입금하실 금액 [");
	prompt += to_string(depositAmount);
	prompt += "]원에서 자동 차감됩니다.\n\t확인 : 0\n\t취소: -1\n";

	int input;
	input = getInput(prompt, 0);
	if (input == 0) { return State::D_Deposit; }
	if (input == -1) {
		cout << "입금을 취소하셨습니다." << endl;
		return State::ChooseTransaction;
	}

	cout << "Debug: Unexpected behavior in UI::t_confirm" << endl;
	return State::End;
}

UI::State UI::d_deposit() {
	bool success = atm->deposit(transactionType, transactionBill, depositCheckInput, depositCheckNum, depositCheckSum, acc);
	if (success) {
		cout << "Debug: Remaining cash of the ATM : " << atm->getATMremainCash() << endl; 
		return State::ChooseTransaction;
	}
	else {
		return State::Deposit;
	}
}

/***********************	 Withdrawal  	***********************/

UI::State UI::withdrawal() {
	// from: chooseTransaction
	cout << "\t[withdrawal]" << endl;
	fee = atm->fee(6, acc, nullptr);
	return State::W_AskAmount;
}

UI::State UI::w_askAmount() {
	transactionAmount = 0;

	cout << "Debug: 수수료는 [" << fee << "]원입니다." << endl;

	string prompt = "출금하실 금액을 입력해 주십시오. (단위 : 만원)\t";
	prompt += "취소: -1\n";
	
	transactionAmount = getInput(prompt, 2000); //얼마로 해두는게 좋을까?

	if (transactionAmount == -1) {
		cout << "출금을 취소하셨습니다." << endl;
		return State::ChooseTransaction;
	}
	transactionBill = Bill{ 0, transactionAmount, 0, 0 };
	return State::W_CheckMaxAmount;
}

UI::State UI::w_checkAccountBalance() {
	if ((transactionBill.getSum() + fee) > acc->getBalance()) {
		cout << "계좌에 잔액이 부족합니다. 다시 시도해주십시오." << endl;
		return State::Withdrawal;
	}
	else { return State::W_CheckATMBalance; }
}

UI::State UI::w_checkMaxAmount() {
	if (transactionBill.getSum() > 300000) {
		cout << "1회 최대 출금 금액(30만원)을 초과하였습니다. 다시 시도해주십시오." << endl;
		return State::W_AskAmount;
	}
	else { return State::W_CheckAccountBalance; }
}

UI::State UI::w_checkATMBalance() {
	if (!atm->compareBill(transactionBill)) {
		cout << "ATM 기 내부에 현금이 부족합니다." << endl;
		return State::ChooseTransaction;
	}
	else { return State::W_Confirm; }
}

UI::State UI::w_confirm() {
	string prompt = "계좌에서 ";
	prompt += (to_string(transactionBill.getSum()) + "]원 출금하시겠습니까?\n수수료는 [");
	prompt += (to_string(fee) + "]원입니다. 수수료는 현재 계좌 잔액 [");
	prompt += to_string(acc->getBalance());
	prompt += "]원에서 자동 차감됩니다.\n\t확인 : 0\n\t취소: -1\n";

	int input;
	input = getInput(prompt, 0);
	if (input == 0) { return State::W_Withdrawal; }
	if (input == -1) {
		cout << "출금을 취소하셨습니다." << endl;
		return State::ChooseTransaction;
	}

	cout << "Debug: Unexpected behavior in UI::t_confirm" << endl;
	return State::End;
}

UI::State UI::w_withdrawal() {
	bool success = atm->withdrawal(transactionBill, acc);
	if (success) {
		cout << "Debug: Remaining cash of the ATM : " << atm->getATMremainCash() << endl;
		return State::ChooseTransaction;
	}
	else {
		return State::Withdrawal;
	}
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

	transactionType = input; // Exception handling 필요
	if (transactionType == 1) { cout << "You have chosen [cash transfer]. 현금 송금을 선택하셨습니다." << endl; }
	if (transactionType == 2) { cout << "You have chosen [account transfer]. 계좌 송금을 선택하셨습니다." << endl; }
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
		if (transactionType == 1) { return State::T_AskAmount_C; }
		else { return State::T_AskAmount_A; }
	}
	if (input == 1) { return State::T_AskToAcc; }

	cout << "Debug: Unexpected behavior in UI::t_confirmToAcc" << endl;
	return State::End;
}

UI::State UI::t_askAmount_c() {
	// from: t_askToAcc (when transactionType == 1)

	cout << "Debug: 수수료는 [" << fee << "]원입니다." << endl;

	int input;
	transactionAmount = 0; // = insertedBill.sum();
	string prompt = "Please insert cash you would like to transfer.";
	prompt += " 송금할 현금을 투입해 주십시오.\n\tcancel 취소: -1\n";
	// 투입 valid한지 check; Bill 사용하게 바꾸기 (입금쪽에서 구현된 함수 사용)
	// transactionAmount = insertedBill.sum();
	cout << "Debug: cash transfer; transfer amount: ";
	cin >> transactionAmount; // temporary; to be done

	// 현금송금에 한해 투입한 액수 기계가 센 후 액수 맞는지 확인 필요 REQ6.3
	prompt = "투입하신 금액을 확인해 주십시오.\n\t[" + std::to_string(transactionAmount);
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
	// from: t_askToAcc (when transactionType == 2)

	cout << "Debug: 수수료는 [" << fee << "]원입니다." << endl;

	transactionAmount = 0;
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
	cin >> transactionAmount; // temporary; to be done

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
	prompt += (std::to_string(transactionAmount) + "]원 송금하시겠습니까?\n수수료는 [");
	prompt += (std::to_string(fee) + "]원입니다. 수수료는 현재 계좌 잔액 [");
	prompt += std::to_string(acc->getBalance());
	prompt += "]원에서 자동 차감됩니다.\n\t0. confirm 확인\n\tcancel 취소: -1\n";

	int input;
	input = getInput(prompt, 0);
	if (input == 0) { return State::T_Transfer; }
	if (input == -1) {
		cout << "You have exited [transfer] session. 송금을 취소하셨습니다." << endl;
		if (transactionType == 1) {
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
	bool success = atm->transfer(transactionType, transactionAmount, acc, toAcc);
	if (success) {
		// 송금 확인되어 반환의 여지 없을 때 remainCash transferAmount만큼 늘리기
		if (transactionType == 1) {
			// atm->insertCash(transactionAmount); // Bill class 구현에 따라 다를 수 있음
			cout << "Debug: Remaining cash of the ATM : " << atm->getATMremainCash() << endl; // 수정 필요
		}
		// 명세표 출력?
		return State::ChooseTransaction;
	}
	else {
		cout << "Not enough balance. 잔액이 부족합니다." << endl;
		if (transactionType == 1) {
			cout << "Your cash has returned. 투입하신 현금이 반환되었습니다.";
			cout << "Please make sure to take your cash. 투입구를 확인해주세요." << endl;  // 이걸 아예 다른 단계로 만들까?
		}
		return State::ChooseTransaction; // 어디로 가게 할 것?
	}
}

void UI::end() {

}
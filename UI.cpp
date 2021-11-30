#include "UI.h"

using namespace std;

int UI::run() {

	Database* DB = Database::getInstance();

	Bank* uriBank = new Bank();
	Bank* kakaoBank = new Bank("kakao");

	Bill* A1_bill = new Bill(100, 200, 500, 1000);
	Bill* A2_bill = new Bill(100, 100, 100, 100);
	ATM* A1 = new ATM(uriBank, "admin", 1357, A1_bill, 100, true, true); // 0; engSupport, multiBank
	ATM* A2 = new ATM(kakaoBank, "master", 2345, A2_bill, 0, false, false); // 1; engUnsupport, singleBank

	User* U1 = new User("U1", "최가난");
	User* U2 = new User("U2", "권부자");
	User* U3 = new User("U3", "서모녀");
	User* U4 = new User("U4", "김백규");
	User* U5 = new User("U5", "버터");

	Account* AC1 = new Account(uriBank, U1, 2345, 10000); // 계좌번호 0
	DB->addAccountList(AC1);
	Account* AC2 = new Account(uriBank, U2, 3344, 3000000); // 계좌번호 1
	DB->addAccountList(AC2);
	Account* AC3 = new Account(kakaoBank, U3, 22, 450000); // 계좌번호 2
	DB->addAccountList(AC3);
	Account* AC4 = new Account(kakaoBank, U1, 1024, 1000); // 계좌번호 3
	DB->addAccountList(AC4);

	atm = A1; // atm 선택받기 구현하면 이거 없애줘야
	// atm = A2; // (singleBank debugging용)
	this->database = DB;

	while (state != State::End) {
		switch (state) {
		case State::ChangeLanguage:
			state = changeLanguage();
			break;
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
		case State::SessionOver: // 세션 종료 단계 추가, 여기서 session history를 출력함
			state = sessionOver();
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

/***********************	  cin functions  	***********************/

int UI::getInput(const string& prompt, int maximum, int minimum = 0,  bool languageCheck = false, bool enableCancel = true) { // maximum 미만, minimum 이상;
	int input;
	for (;;) {
		cout << prompt;
		cout.flush(); // Similar to endl, without new line.
		cin >> input;
		if (cin.fail()) { cout << "Wrong type error" << endl; cin.clear(); cin.ignore(256, '\n'); continue; }
		if (enableCancel && input == -1) { cin.clear(); cin.ignore(256, '\n'); break; } // -1은 취소 (range check 이전에 확인)
		if (languageCheck && input == -2) { cin.ignore(256, '\n'); break; }
		if (input < minimum || input > maximum) { cout << "Wrong range error" << endl; cin.clear(); cin.ignore(256, '\n'); continue; }
		cin.ignore(256, '\n'); break;
	}
	return input;
}

int* UI::getInputArray(const string& prompt, int length, int maximum, int minimum = 0, bool enableCancel = true) { // maximum 미만, minimum 이상;
	int* input = new int[30];
	cout << prompt;
	cout.flush(); // Similar to endl, without new line.
	for (int i = 0; i < length; i++) {
		int temp;
		for (;;) {
			cin >> temp;
			if (cin.fail()) { cout << "Wrong type error" << endl; cin.clear(); cin.ignore(256, '\n'); continue; }
			if (enableCancel && temp == -1) { cin.clear(); cin.ignore(256, '\n'); break; } // -1은 취소 (range check 이전에 확인)
				// enableCancel 제대로 작동하는지 debugging 완료
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

/***********************	 state functions  	***********************/
UI::State UI::changeLanguage() {
	string prompt = "\t한국어 : 0\n\tEnglish : 1\n\t취소(Cancel) : -1\n";
	int input = getInput(prompt, 1);
	if (input == 0) {
		database->changeLanguage("KOR");
		atm->changeLanguage("KOR");
		languagePack->changeLanguage("KOR");
		cout << languagePack->getSentence("UI_changeLanguage0");
	}
	else if (input == 1) {
		database->changeLanguage("EN");
		atm->changeLanguage("EN");
		languagePack->changeLanguage("EN");
		cout << languagePack->getSentence("UI_changeLanguage0");
	}
	else if (input == -1) {
		cout << languagePack->getSentence("UI_changeLanguage1");
	}
	else {
		cout << languagePack->getSentence("UI_changeLanguage2");
	}
	return State::GetAccountNum;
}


UI::State UI::getATM() {
	// 필요시 구현
	return State::End;
}

UI::State UI::getAccountNum() {
	accID, toAccID = -1; acc, toAcc = nullptr; // 혹시 모르니 초기화
	cout << languagePack->getSentence("UI_getAccountNum0"); // Debug
	if (atm->isEnglishSupport()) {
		cout << "언어 선택(Choose Language) : -2" << endl;
	}
	return State::AccessAccount;
}

UI::State UI::accessAccount() { // insert Card
	// from: getAccountNum()
	// 유저로부터 계좌번호 입력받는다
	accountNum = getInput(languagePack->getSentence("UI_accessAccount0"), 100000, 0, true, true); // "cancel: -1"임을 넣거나 enableCancel false로 하거나

	if (accountNum == 99999) { // admin 계정일 때
		return State::VerifyAdmin;
	}
	else if (accountNum == -1) { // cancel 선택되었을 때 (cancel 묻는 prompt 추가 필요)
		cout << languagePack->getSentence("UI_accessAccount1");
		return State::End;
	}
	else if (accountNum == -2) {
		return State::ChangeLanguage;
	}
	accID = database->getIndexFromID(accountNum); // 계좌번호에 해당하는 ID(index)를 받음 (계좌번호 아직 한자리라서 index와 계좌번호가 구분이 안 됨)
	if (accID == -1) { // 존재하지 않는 계좌일 경우; Debugging 필요
		cout << languagePack->getSentence("UI_accessAccount1");
		return State::End;
	}
	acc = database->getAccountByNum(accID); // Account*로
	// if ATM이 singlebank이면
	if (!atm->isMultiBank()) {
		// ATM의 bank와 acc의 bank 같은지 체크
		if (atm->getBank()->getBankName() != acc->getBank()->getBankName()) { // bank 다른 경우
			cout << languagePack->getSentence("UI_accessAccount2");
			return State::GetAccountNum;
		}
	}
	return State::CheckAccount;
	// 여기서 하는 존재하지 않는 계좌/지원하지 않는 계좌 체크는 checkAccount 끝나고 나서 하는 게 맞지 않나?
}

UI::State UI::verifyAdmin() {
	// from: accessAccount (admin 계정일 때)
	cout << languagePack->getSentence("UI_verifyAdmin0");
	int input = getInput(languagePack->getSentence("UI_verifyAdmin1"), 10000);
	if (atm->checkPW(input)) { return State::ShowAdmin; }
	else {
		cout << languagePack->getSentence("UI_verifyAdmin2");
		return State::GetAccountNum;
	}
}

UI::State UI::showAdmin() {
	// TODO: show history 
	database->printHistory();
	return State::GetAccountNum;
}

UI::State UI::checkAccount() {
	// from: accessAccount
	// 입력받은 계좌번호가 맞는지 물어본다 (생략가능한 단계)
	string prompt = languagePack->getSentence("UI_checkAccount0.1");
	prompt += to_string(accountNum);
	prompt += languagePack->getSentence("UI_checkAccount0.2");
	int input = getInput(prompt, 0);
	if (input == -1) {
		return State::GetAccountNum;
	}
	else if (input == 0) {
		return State::VerifyAccount;
	}
	else {
		cout << languagePack->getSentence("UI_checkAccount1"); 
		return State::End;
	}
	// 이 함수에서 카드(계좌) valid한지, supported인지 체크하는 게 맞지 않나?
}

UI::State UI::verifyAccount() {
	// from: checkAccount
	// 비밀번호 물어본다
	string prompt = languagePack->getSentence("UI_verifyAccount0");
	for (int i=0; i < 3; i++) {
		int input = getInput(prompt, 9999, 0, false, false); // 4자리 수이지만 이 경우에는 0000~9999
		if (input == -1) { return State::CheckAccount; } // 현재 쓰이지 않는다(enableCancel = false)
		else {
			if (acc->checkPassword(input)) { // 비밀번호 맞으면
				// 새로운 session 시작
				this->WithdrawalPerSession = 0; // chooseTransaction 들어가기 전에 초기화해줘야 하기 때문에
				return State::ChooseTransaction;
			}
			if (i < 2) {
				cout << languagePack->getSentence("UI_verifyAccount1.0");
				cout << (2 - i) << languagePack->getSentence("UI_verifyAccount1.1");
			}
			else { cout << "비밀번호를 3회 틀리셨습니다.\n"; } // 번역필요
		}
	}
	return State::GetAccountNum; // EN/KR 단계 구현되면 바꾸기
}

UI::State UI::enterAdmin() {
	cout << languagePack->getSentence("UI_enterAdmin0");
	return State::GetAccountNum;
}

UI::State UI::chooseTransaction() {
	// from: verifyAccount
	// from: t_askTransferType (if canceled)
  
	atm->insertedBill = Bill{0,0,0,0}; // 혹시 모르니 초기화 (송금)
	transactionAmount = 0; // 혹시 모르니 초기화 (송금)
	
	string prompt = languagePack->getSentence("UI_chooseTransaction0");

	int input = getInput(prompt, 3);
	if (input == -1) {
		// 취소시 카드 반환해 주고 sessionOver state로
		cout << languagePack->getSentence("UI_chooseTransaction1");
		return State::SessionOver;
	}
	if (input == 1) { return State::Deposit; }
	else if (input == 2) { return State::Withdrawal; }
	else if (input == 3) { return State::Transfer; }
	else cout << languagePack->getSentence("UI_chooseTransaction2");
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
	string prompt = languagePack->getSentence("UI_d_askDepositType0");

	transactionType = getInput(prompt, 2);
	if (transactionType == -1) {
		cout << languagePack->getSentence("UI_d_askDepositType1");
		return State::ChooseTransaction;
	}

	if (transactionType == 1) {
		cout << languagePack->getSentence("UI_d_askDepositType2");
		return State::D_AskAmount_Cash;
	}
	else if (transactionType == 2) {
		cout << languagePack->getSentence("UI_d_askDepositType3");
		return State::D_AskAmount_Check;
	}
	else {
		cout << languagePack->getSentence("UI_d_askDepositType4");
		return State::End;
	}
}

UI::State UI::d_askAmount_Cash() {
	cout << languagePack->getSentence("UI_d_askAmount_Cash0.1") << fee << languagePack->getSentence("UI_d_askAmount_Cash0.2");

	string prompt = languagePack->getSentence("UI_d_askAmount_Cash1");
	int* input;
	input = getInputArray(prompt, 4, 500);

	if (input[0] == -1) { // input[1] == -1이면 어떻게 되나?
		cout << languagePack->getSentence("UI_d_askAmount_Cash2");
		return State::ChooseTransaction;
	}
	transactionBill = Bill{ input[0], input[1], input[2], input[3] }; // 얘랑
	if (transactionBill.getTotalNum() > 50) {
		cout << languagePack->getSentence("UI_d_askAmount_Cash3");
		return State::D_AskAmount_Cash;
	}
	if (transactionBill.getTotalNum() == 0) {
		cout << languagePack->getSentence("UI_d_askAmount_Cash4");
		return State::D_AskAmount_Cash;
	}
	transactionBill = Bill{ input[0], input[1], input[2], input[3] }; // 얘는 왜 중복?
	return State::D_Confirm_Cash;
}

UI::State UI::d_askAmount_Check() {
	cout << languagePack->getSentence("UI_d_askAmount_Check0.1") << fee << languagePack->getSentence("UI_d_askAmount_Check0.2");

	string prompt = languagePack->getSentence("UI_d_askAmount_Check1");
	depositCheckNum = getInput(prompt, 500);
	if (depositCheckNum == -1) {
		cout << languagePack->getSentence("UI_d_askAmount_Check2");
		return State::ChooseTransaction;
	}
	else if (depositCheckNum == 0) {
		cout << languagePack->getSentence("UI_d_askAmount_Check3");
		return State::D_AskAmount_Check;
	}
	else if (depositCheckNum > 30) {
		cout << languagePack->getSentence("UI_d_askAmount_Check4");
		return State::D_AskAmount_Check;
	}
	string prompt2 = languagePack->getSentence("UI_d_askAmount_Check5");
	int* input;
	input = getInputArray(prompt2, depositCheckNum, 100000000);
	if (input[0] == -1) {
		cout << languagePack->getSentence("UI_d_askAmount_Check6");
		return State::ChooseTransaction;
	}
	depositCheckInput = input;
	return State::D_Confirm_Check;
}

UI::State UI::d_confirm_Cash() {
	cout << languagePack->getSentence("UI_d_confirm_Cash0");
	transactionBill.printBill(languagePack->isKor());
	int input = getInput("", 0);
	if (input == -1) {
		cout << languagePack->getSentence("UI_d_confirm_Cash1");
		return State::ChooseTransaction;
	}
	else if (input == 0) {
		return State::D_ConfirmTotal;
	}
	else {
		cout << languagePack->getSentence("UI_d_confirm_Cash2");
		return State::End;
	}
}

UI::State UI::d_confirm_Check() {
	cout << languagePack->getSentence("UI_d_confirm_Check0.1");
	for (int i = 0; i < depositCheckNum; i++) {
		cout << depositCheckInput[i] << languagePack->getSentence("UI_d_confirm_Check0.2");
		depositCheckSum += depositCheckInput[i];
	}
	cout << endl;
	cout << languagePack->getSentence("UI_d_confirm_Check0.3") << depositCheckSum << languagePack->getSentence("UI_d_confirm_Check0.4");;
	int input = getInput("", 0);
	if (input == -1) {
		cout << languagePack->getSentence("UI_d_confirm_Check1");
		return State::ChooseTransaction;
	}
	else if (input == 0) {
		return State::D_ConfirmTotal;
	}
	else {
		cout << languagePack->getSentence("UI_d_confirm_Check2");
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
	else { cout << languagePack->getSentence("UI_d_confirmTotal0"); return State::End; }
	string prompt = languagePack->getSentence("UI_d_confirmTotal1.1");
	prompt += (to_string(depositAmount) + languagePack->getSentence("UI_d_confirmTotal1.2"));
	prompt += (to_string(fee) + languagePack->getSentence("UI_d_confirmTotal1.3"));
	prompt += to_string(depositAmount);
	prompt += languagePack->getSentence("UI_d_confirmTotal1.4");

	int input;
	input = getInput(prompt, 0);
	if (input == 0) { return State::D_Deposit; }
	if (input == -1) {
		cout << languagePack->getSentence("UI_d_confirmTotal2");
		return State::ChooseTransaction;
	}

	cout << languagePack->getSentence("UI_d_confirmTotal3");
	return State::End;
}

UI::State UI::d_deposit() {
	bool success = atm->deposit(transactionType, transactionBill, depositCheckInput, depositCheckNum, depositCheckSum, acc);
	if (success) {
		cout << languagePack->getSentence("UI_d_deposit0") << atm->getATMremainCash() << endl;
		return State::ChooseTransaction;
	}
	else {
		return State::Deposit;
	}
}

/***********************	 Withdrawal  	***********************/

UI::State UI::withdrawal() {
	// from: chooseTransaction
	if (this->WithdrawalPerSession >= 3) {
		cout << "해당 세션의 출금 횟수 한도(3회)를 초과하였습니다.\n"; // 번역필요
		return State::ChooseTransaction;
	}
	cout << "\t[withdrawal]" << endl; // 번역필요
	fee = atm->fee(6, acc, nullptr);
	return State::W_AskAmount;
}

UI::State UI::w_askAmount() {
	transactionAmount = 0;

	cout << languagePack->getSentence("UI_w_askAmount0.1") << fee << languagePack->getSentence("UI_w_askAmount0.2");

	string prompt = languagePack->getSentence("UI_w_askAmount1");

	transactionAmount = getInput(prompt, 2000); // 얼마로 해두는게 좋을까?

	if (transactionAmount == -1) {
		cout << languagePack->getSentence("UI_w_askAmount2");
		return State::ChooseTransaction;
	}
	transactionBill = Bill{ 0, transactionAmount, 0, 0 };
	return State::W_CheckMaxAmount;
}

UI::State UI::w_checkAccountBalance() {
	if ((transactionBill.getSum() + fee) > acc->getBalance()) {
		cout << languagePack->getSentence("UI_w_checkAccountBalance0");
		return State::Withdrawal;
	}
	else { return State::W_CheckATMBalance; }
}

UI::State UI::w_checkMaxAmount() {
	if (transactionBill.getSum() > 300000) {
		cout << languagePack->getSentence("UI_w_checkMaxAmount0");
		return State::W_AskAmount;
	}
	else { return State::W_CheckAccountBalance; }
}

UI::State UI::w_checkATMBalance() {
	if (!atm->compareBill(transactionBill)) {
		cout << languagePack->getSentence("UI_w_checkATMBalance0");
		return State::ChooseTransaction;
	}
	else { return State::W_Confirm; }
}

UI::State UI::w_confirm() {
	string prompt = languagePack->getSentence("UI_w_confirm0.1");
	prompt += (to_string(transactionBill.getSum()) + languagePack->getSentence("UI_w_confirm0.2"));
	prompt += (to_string(fee) + languagePack->getSentence("UI_w_confirm0.3"));
	prompt += to_string(acc->getBalance());
	prompt += languagePack->getSentence("UI_w_confirm0.4");

	int input;
	input = getInput(prompt, 0);
	if (input == 0) { return State::W_Withdrawal; }
	if (input == -1) {
		cout << languagePack->getSentence("UI_w_confirm1");
		return State::ChooseTransaction;
	}

	cout << languagePack->getSentence("UI_w_confirm2");
	return State::End;
}

UI::State UI::w_withdrawal() {
	bool success = atm->withdrawal(transactionBill, acc);
	if (success) { // 출금 완료시
		this->WithdrawalPerSession++; // 이 세션 중 출금한 횟수 1회 늘리기
		cout << languagePack->getSentence("UI_w_withdrawal0") << atm->getATMremainCash() << endl;
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

	string prompt = languagePack->getSentence("UI_t_askTransferType0");
	input = getInput(prompt, 2);
	if (input == -1) {
		cout << languagePack->getSentence("UI_t_askTransferType1");
		return State::ChooseTransaction;
	}

	transactionType = input; // Exception handling 필요
	if (transactionType == 1) { cout << languagePack->getSentence("UI_t_askTransferType2"); }
	if (transactionType == 2) { cout << languagePack->getSentence("UI_t_askTransferType3"); }
	return State::T_AskToAcc;
}


UI::State UI::t_askToAcc() {
	// from: 
	int input;
	string prompt = languagePack->getSentence("UI_t_askToAcc0");
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
	prompt += (languagePack->getSentence("UI_t_confirmToAcc0.2") + std::to_string(toAccID));
	prompt += languagePack->getSentence("UI_t_confirmToAcc0.3");
	input = getInput(prompt, 1);
	// 같은 계좌인지 확인하기 - to be done
	if (input == -1) { return State::ChooseTransaction; }
	if (input == 0) {
		if (transactionType == 1) { return State::T_AskAmount_C; }
		else { return State::T_AskAmount_A; }
	}
	if (input == 1) { return State::T_AskToAcc; }

	cout << languagePack->getSentence("UI_t_confirmToAcc1");
	return State::End;
}

UI::State UI::t_askAmount_c() {
	// from: t_askToAcc (when transactionType == 1)

	cout << languagePack->getSentence("UI_t_askAmount_c0.1") << fee << languagePack->getSentence("UI_t_askAmount_c0.2");

	transactionAmount = 0; // = insertedBill.sum();
	string prompt = "Please insert cash you would like to transfer.";
	prompt += " 송금할 현금을 투입해 주십시오. (5만원권, 1만원권, 5천원권, 1천원권 개수 순으로 입력)";
	prompt += "\n\tcancel 취소: -1\n";
	// 투입 valid한지 check; Bill 사용하게 바꾸기 (입금쪽에서 구현된 함수 사용)

	int* inputArr;
	inputArr = getInputArray(prompt, 4, 500);
	if (inputArr[0] == -1) {
		cout << "You have exited [transfer] session. 송금을 취소하셨습니다." << endl; // 어디로 가게 할 것?
		cout << "Your cash has returned. 투입하신 현금이 반환되었습니다. ";
		cout << "Please make sure to take your cash. 투입구를 확인해주세요." << endl;
		return State::ChooseTransaction;
	}
	atm->insertedBill = Bill{ inputArr[0], inputArr[1], inputArr[2], inputArr[3] }; //얘랑
	if (atm->insertedBill.getTotalNum() > 50) {
		cout << "최대 입금 가능 장 수를 초과하였습니다. 다시 시도해주십시오." << endl;
		return State::T_AskAmount_C;
	}
	if (atm->insertedBill.getTotalNum() == 0) {
		cout << "투입구에 현금이 들어있지 않습니다. 다시 시도해주십시오." << endl;
		return State::T_AskAmount_C;
	}
	atm->insertedBill = Bill{ inputArr[0], inputArr[1], inputArr[2], inputArr[3] }; // 얘는 왜 중복?
	transactionAmount = atm->insertedBill.getSum();

	// 현금송금에 한해 투입한 액수 기계가 센 후 액수 맞는지 확인 필요 REQ6.3
	int input;
	prompt = languagePack->getSentence("UI_t_askAmount_c3.1") + std::to_string(transactionAmount);
	prompt += languagePack->getSentence("UI_t_askAmount_c3.2");
	input = getInput(prompt, 0);

	if (input == 0) { return State::T_Confirm; }
	if (input == -1) {
		cout << "You have exited [transfer] session. 송금을 취소하셨습니다." << endl; // 어디로 가게 할 것?
		cout << "Your cash has returned. 투입하신 현금이 반환되었습니다. ";
		cout << "Please make sure to take your cash. 투입구를 확인해주세요." << endl;
		// cout << languagePack->getSentence("UI_t_askAmount_c4");
		return State::ChooseTransaction; // 어디로 가게 할 것?
	}

	cout << languagePack->getSentence("UI_t_askAmount_c5");
	return State::End;
}


UI::State UI::t_askAmount_a() {
	// from: t_askToAcc (when transactionType == 2)
	atm->insertedBill = Bill{0,0,0,0};
  
	cout << languagePack->getSentence("UI_t_askAmount_a0.1") << fee << languagePack->getSentence("UI_t_askAmount_a0.2");

	transactionAmount = 0;
	string prompt = languagePack->getSentence("UI_t_askAmount_a1.1");
	prompt += std::to_string(acc->getBalance());
	prompt += languagePack->getSentence("UI_t_askAmount_a1.2");

	// 액수 valid한지 check하기(계좌 잔액, 송금한도 등;) - to be done
	int input;
	input = getInput(prompt, 2000001); // 송금한도액? (일단 200만원으로)
	if (input == -1) {
		cout << "You have exited [transfer] session. 송금을 취소하셨습니다." << endl; // 어디로 가게 할 것?
		return State::ChooseTransaction; // 어디로 가게 할 것?
	}
	/*
	if (transferMoney > fromAcc->getBalance()) {
		cout << "Not enough balance error. 잔액이 부족합니다.(code 706)" << endl; // 잔액 부족 말하기는 최종 송금 확인 후에만 할까? (수수료 고려 위해)
	}
	*/
	
	transactionAmount = input;
	
	// 액수 묻기 (cancel을 다시 입력으로 보고 함수로 따로 빼기)
	prompt = std::to_string(transactionAmount);
	prompt += " 원이 맞습니까?\n\t0. confirm 확인\n\tcancel 취소: -1\n";
	input = getInput(prompt, 0);
  
	if (input == 0) { return State::T_Confirm; }
	if (input == -1) {
		cout << languagePack->getSentence("UI_t_askAmount_a3"); // 어디로 가게 할 것?
		return State::ChooseTransaction; // 어디로 가게 할 것?
	}

	cout << languagePack->getSentence("UI_t_askAmount_a4");
	return State::End;
}

UI::State UI::t_confirm() {
	// from: t_askAmount_a
	// from: t_askAmount_c

	string prompt = "";
	// 한글/영어에 따라 어순이 달라서 조건문을 사용해야 함.
	if (languagePack->isKor()) {
		prompt += "[" + toAcc->getOwner()->getUserName() + languagePack->getSentence("UI_t_confirm0.2");
		prompt += (std::to_string(transactionAmount) + languagePack->getSentence("UI_t_confirm0.3"));
		prompt += (std::to_string(fee) + languagePack->getSentence("UI_t_confirm0.4"));
		prompt += std::to_string(acc->getBalance());
		prompt += languagePack->getSentence("UI_t_confirm0.5");
	}
	else {
		prompt += (languagePack->getSentence("UI_t_confirm0.1") + std::to_string(transactionAmount) + languagePack->getSentence("UI_t_confirm0.2"));
		prompt += (toAcc->getOwner()->getUserName() + languagePack->getSentence("UI_t_confirm0.3"));
		prompt += (std::to_string(fee) + languagePack->getSentence("UI_t_confirm0.4"));
		prompt += std::to_string(acc->getBalance());
		prompt += languagePack->getSentence("UI_t_confirm0.5");
	}

	int input;
	input = getInput(prompt, 0);
	if (input == 0) { return State::T_Transfer; }
	if (input == -1) {
		cout << languagePack->getSentence("UI_t_confirm1");
		if (transactionType == 1) {
			cout << languagePack->getSentence("UI_t_confirm2");
		}
		return State::ChooseTransaction;
	}

	cout << languagePack->getSentence("UI_t_confirm3");
	return State::End;
}

UI::State UI::t_transfer() {
	// from: t_confirm
	bool success = atm->transfer(transactionType, transactionAmount, acc, toAcc, transactionBill);
	if (success) {
		if (transactionType == 1) {
			cout << languagePack->getSentence("UI_t_transfer0") << atm->getATMremainCash() << endl; // 수정 필요
		}
		// 명세표 출력?
		// database->addHistory("송금", before, after, acc, toAcc); // 도연이가 함수안에 만들어놓은듯?
		return State::ChooseTransaction;
	}
	else {
		cout << languagePack->getSentence("UI_t_transfer1");
		if (transactionType == 1) {
			cout << languagePack->getSentence("UI_t_transfer2");  // 이걸 아예 다른 단계로 만들까?
		}
		return State::ChooseTransaction; // 어디로 가게 할 것?
	}
}

UI::State UI::sessionOver() {
	database->printSessionHistory(); // session history를 출력
	database->clearSessionHistory();
	return State::GetAccountNum; // EN/KR 구현되면 그곳으로
}

void UI::end() {

}
#include "UI.h"
#include <fstream>

using namespace std;

int UI::run() {

	Database* DB = Database::getInstance();

	Bank* uriBank = new Bank("우리은행", "UriBank");
	Bank* kakaoBank = new Bank("카카오뱅크", "KakaoBank");
	Bank* suhyup = new Bank("수협은행", "Suhyup");

	Bill* A1_bill = new Bill(100, 180, 1, 0);
	Bill* A2_bill = new Bill(100, 100, 1, 0);
	ATM* A1 = new ATM(uriBank, "admin", 1357, A1_bill, 100, true, true); // 0; engSupport, multiBank
	ATM* A2 = new ATM(kakaoBank, "master", 2345, A2_bill, 0, false, false); // 1; engUnsupport, singleBank

	User* U1 = new User("최가난", "Ganan Choi");
	User* U2 = new User("권부자", "Buja Kwon");
	User* U3 = new User("서모녀", "Monyeo Seo");
	// User* U4 = new User("김백규", "Baekgyu Kim");
	// User* U5 = new User("버터", "Butter"); // 처음부터 bracket 치면 어떨까

	Account* AC1 = new Account(uriBank, U1, 2345, 10000); // 계좌번호 10000
	DB->addAccountList(AC1);
	Account* AC2 = new Account(uriBank, U2, 3344, 1510000); // 계좌번호 10001
	DB->addAccountList(AC2);
	Account* AC3 = new Account(kakaoBank, U3, 22, 450000); // 계좌번호 10002
	DB->addAccountList(AC3);
	Account* AC4 = new Account(kakaoBank, U1, 1024, 1000); // 계좌번호 10003
	DB->addAccountList(AC4);
	Account* AC5 = new Account(suhyup, U2, 3344, 300000000); // 계좌번호 10004 (3억)
	DB->addAccountList(AC5);
	Account* AC6 = new Account(suhyup, U2, 3344, 100000); // 계좌번호 10004 (3억)
	DB->addAccountList(AC6);

	atm = A1;
	//atm = A2; // (singleBank, EngSupport X)

	cout << "\t[Boot message]" << endl;
	cout << "current ATM ID : " << atm->getID() << endl;
	cout << "current ATM bank : " << atm->getBank()->getName(true);
	cout << " (" << atm->getBank()->getName(false) << ")" << endl;
	cout << "current ATM is ";
	cout << (atm->isMultiBank() ? "multibank ATM" : "singlebank ATM") << endl;
	cout << "current ATM is " << (atm->isEnglishSupport() ? "" : "not ");
	cout << "supporting ENG" << endl;
	cout << "current ATM Balance : " << endl;
	atm->printATMremainCashNum();
	cout << endl;

	this->database = DB;

	while (state != State::End) {
		switch (state) {
		case State::ChangeLanguage: // 한영변환
			state = changeLanguage();
			break;
		case State::InsertCard: // 계좌번호 입력, 99999 <- admin,
			state = insertCard();
			break;
		case State::A_Verify:
			state = a_verify();
			break;
		case State::A_ShowMenu: // 본인 확인
			state = a_showMenu();
			break;
		case State::A_ShowHistory:
			state = a_showHistory();
			break;
		case State::A_CSVtoHistory:
			state = a_csvtoHistory();
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
			// delete session (memory deallocation) // 추가하기

			delete AC6;
			delete AC5;
			delete AC4;
			delete AC3;
			delete AC2;
			delete AC1;

			delete A2;
			delete A1;

			// delete U5;
			// delete U4;
			delete U3;
			delete U2;
			delete U1;

			delete suhyup;
			delete kakaoBank;
			delete uriBank;

			delete DB;

			return 0;
		}
	}
	return 0;
}

/***********************	  cin functions  	***********************/


int UI::getInput(const string& prompt, int maximum, int minimum = 0, bool enableCancel = true) { // [min, max]
	int input;
	for (;;) {
		cout << prompt;
		cout.flush(); // Similar to endl, without new line.
		cin >> input;
		if (cin.fail()) { cout << "[Wrong type error]" << endl; cin.clear(); cin.ignore(256, '\n'); continue; }
		if (enableCancel && input == -1) { cin.clear(); cin.ignore(256, '\n'); break; } // -1은 취소 (range check 이전에 확인)
		if (input < minimum || input > maximum) { cout << "[Wrong range error]" << endl; cin.clear(); cin.ignore(256, '\n'); continue; }
		cin.ignore(256, '\n'); break;
	}
	return input;
}

int* UI::getInputArray(const string& prompt, int length, int maximum, int minimum = 0, bool enableCancel = true) { // [min, max]
	int* input = new int[30];
	cout << prompt;
	cout.flush(); // Similar to endl, without new line.
	for (int i = 0; i < length; i++) {
		int temp;
		for (;;) {
			cin >> temp;
			if (cin.fail()) { cout << "[Wrong type error]" << endl; cin.clear(); cin.ignore(256, '\n'); continue; }
			if (enableCancel && temp == -1) { cin.clear(); cin.ignore(256, '\n'); break; } // -1은 취소 (range check 이전에 확인)
				// enableCancel 제대로 작동하는지 debugging 완료
			if (temp < minimum || temp > maximum) { cout << "[Wrong range error]" << endl; cin.clear(); cin.ignore(256, '\n'); continue; }
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

	if (atm->isEnglishSupport()) {
		cout << "\t[*** 어서오십시오 / Welcome ***]\n";
		cout << "\t언어를 선택해 주십시오. / Language setting\n";
	}
	else {
		database->changeLanguage("KOR");
		atm->changeLanguage("KOR");
		languagePack->changeLanguage("KOR");

		cout << "\t[*** 어서오십시오 ***]\n";
		return State::InsertCard;
	}

	string prompt = "\t한국어 : 0\tEnglish : 1\n";
	int input = getInput(prompt, 1, 0, false); // 취소 허용하지 않음
	if (input == 0) {
		database->changeLanguage("KOR");
		atm->changeLanguage("KOR");
		languagePack->changeLanguage("KOR");
		cout << languagePack->getSentence("UI_changeLanguage0");
	}
	else if (input == 1) {
		database->changeLanguage("ENG");
		atm->changeLanguage("ENG");
		languagePack->changeLanguage("ENG");
		cout << languagePack->getSentence("UI_changeLanguage0");
	}
	else {
		cout << languagePack->getSentence("unexpected"); // debug [Checked]
	}
	return State::InsertCard;
}

UI::State UI::insertCard() {
	accID, toAccID = -1; acc, toAcc = nullptr; // 혹시 모르니 초기화
	string prompt = languagePack->getSentence("UI_insertCard0");
	if (atm->isEnglishSupport()) {
		prompt += languagePack->getSentence("cancel");
		accountNum = getInput(prompt, 99999, 10000);
	}
	else {
		prompt += "\n";
		accountNum = getInput(prompt, 99999, 10000, false);
	}

	if (accountNum == 99999) { // admin 계정일 때
		return State::A_Verify;
	}
	else if (accountNum == -1) {
		cout << languagePack->getSentence("UI_insertCard2");
		return State::ChangeLanguage;
	}
	accID = database->getIndexFromID(accountNum); // 계좌번호에 해당하는 ID(index)를 받음 (계좌번호 아직 한자리라서 index와 계좌번호가 구분이 안 됨)
	if (accID == -1) { // 존재하지 않는 계좌일 경우; Debugging 필요 [Checked]
		cout << languagePack->getSentence("UI_insertCard3");
		cout << languagePack->getSentence("card returned");
		return State::ChangeLanguage;
	}
	acc = database->getAccountByNum(accID); // Account*로
	// if ATM이 singlebank이면
	if (!atm->isMultiBank()) {
		// ATM의 bank와 acc의 bank 같은지 체크
		if (atm->getBank()->getName() != acc->getBank()->getName()) { // bank 다른 경우
			cout << languagePack->getSentence("UI_insertCard4");
			cout << languagePack->getSentence("card returned");
			return State::ChangeLanguage;
		}
	}
	return State::CheckAccount;
}

UI::State UI::a_verify() {
	cout << languagePack->getSentence("UI_verifyAdmin0");
	string prompt = languagePack->getSentence("UI_verifyAdmin1");
	prompt += languagePack->getSentence("cancel");
	int input = getInput(prompt, 10000);
	if (input == -1) {
		cout << languagePack->getSentence("card returned");
		return State::ChangeLanguage;
	}
	if (atm->checkPW(input)) { return State::A_ShowMenu; }
	else {
		cout << languagePack->getSentence("UI_verifyAdmin2");
		cout << languagePack->getSentence("card returned");
		return State::ChangeLanguage;
	}
}

UI::State UI::a_showMenu() { // 메뉴 보여주기
	int input = getInput(languagePack->getSentence("UI_verifyAdmin3"), 0);
	if (input == 0) { return State::A_ShowHistory; }
	else {
		cout << languagePack->getSentence("UI_verifyAdmin4");
		cout << languagePack->getSentence("card returned");
		return State::ChangeLanguage;
	}
}

UI::State UI::a_showHistory() { // history 보여주기
	if (database->isHistoryEmpty()) {
		cout << languagePack->getSentence("Database_printHistory1");
		cout << languagePack->getSentence("card returned");
		return State::ChangeLanguage;
	}
	database->printATMHistory();
	return State::A_CSVtoHistory;
}

UI::State UI::a_csvtoHistory() { // 파일로 출력

	ofstream myFile("history.csv");
	for (int i = 0; i < database->getATMHistoryEN().size(); i++) {
		for (int j = 0; j < 13; j++) {
			if (languagePack->isKor()) myFile << database->getATMHistoryKR()[i][j] << ",";
			else  myFile << database->getATMHistoryEN()[i][j] << ",";
		}
		myFile << endl;
	}
	cout << languagePack->getSentence("UI_admin1") << endl;
	cout << languagePack->getSentence("card returned");
	return State::ChangeLanguage;
}


UI::State UI::checkAccount() {
	string prompt = languagePack->getSentence("UI_checkAccount0.1");
	prompt += to_string(accountNum);
	prompt += languagePack->getSentence("UI_checkAccount0.2");
	prompt += languagePack->getSentence("confirm");
	int input = getInput(prompt, 0);
	if (input == -1) {
		cout << languagePack->getSentence("card returned");
		return State::ChangeLanguage;
	}
	else if (input == 0) {
		return State::VerifyAccount;
	}
	else {
		cout << languagePack->getSentence("unexpected"); // debug [Checked]
		return State::End;
	}
}

UI::State UI::verifyAccount() {
	string prompt = languagePack->getSentence("UI_verifyAccount0");
	prompt += languagePack->getSentence("cancel");
	for (int i = 0; i < 3; i++) {
		int input = getInput(prompt, 9999); // 4자리 수이지만 이 경우에는 0000~9999
		if (input == -1) {
			cout << languagePack->getSentence("card returned");
			return State::ChangeLanguage;
		}
		if (acc->checkPassword(input)) { // 비밀번호 맞으면
			// 새로운 session 시작
			cout << languagePack->getSentence("UI_verifyAccount3.1");
			cout << acc->getOwner()->getName(languagePack->isKor());
			cout << languagePack->getSentence("UI_verifyAccount3.2");
			cout << acc->getBank()->getName(languagePack->isKor());
			cout << languagePack->getSentence("UI_verifyAccount3.2.0");
			cout << acc->getID() << languagePack->getSentence("UI_verifyAccount3.3");

			this->WithdrawalPerSession = 0; // chooseTransaction 들어가기 전에 초기화해줘야 하기 때문에
			return State::ChooseTransaction;
		}
		if (i < 2) {
			cout << languagePack->getSentence("UI_verifyAccount1.0");
			cout << (2 - i) << languagePack->getSentence("UI_verifyAccount1.1");
		}
		else {
			cout << languagePack->getSentence("UI_verifyAccount2");
			cout << languagePack->getSentence("card returned");
		}
	}
	return State::ChangeLanguage;
}

UI::State UI::enterAdmin() {
	cout << languagePack->getSentence("UI_enterAdmin0");
	return State::InsertCard;
}

UI::State UI::chooseTransaction() {

	atm->insertedBill = Bill{ 0,0,0,0 }; // 혹시 모르니 초기화 (송금)
	transactionAmount = 0; // 혹시 모르니 초기화 (송금)

	string prompt = languagePack->getSentence("UI_chooseTransaction0");
	prompt += languagePack->getSentence("cancel");
	prompt += languagePack->getSentence("UI_chooseTransaction0.1");

	int input = getInput(prompt, 3);
	if (input == -1) {
		// 취소시 카드 반환해 주고 sessionOver state로
		cout << languagePack->getSentence("card returned");
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
	cout << languagePack->getSentence("UI_deposit0");
	fee = atm->fee(5, acc, nullptr);
	transactionAmount = 0;
	int depositCheckNum = 0;
	int depositCheckSum = 0;
	return State::D_AskDepositType;
}

UI::State UI::d_askDepositType() {
	string prompt = languagePack->getSentence("UI_d_askDepositType0");
	prompt += languagePack->getSentence("cancel");
	prompt += languagePack->getSentence("UI_d_askDepositType0.1");

	transactionType = getInput(prompt, 2, 1);
	if (transactionType == -1) {
		cout << languagePack->getSentence("exit deposit");
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
		cout << languagePack->getSentence("unexpected"); // debug [Checked]
		return State::End;
	}
}

UI::State UI::d_askAmount_Cash() {
	cout << languagePack->getSentence("UI_d_askAmount_Cash0.1") << fee << languagePack->getSentence("UI_d_askAmount_Cash0.2");

	string prompt = languagePack->getSentence("UI_d_askAmount_Cash1");
	int* input;
	input = getInputArray(prompt, 4, 500);

	if (input[0] == -1) {
		cout << languagePack->getSentence("exit deposit");
		return State::ChooseTransaction;
	}
	transactionBill = Bill{ input[0], input[1], input[2], input[3] };
	if (transactionBill.getTotalNum() > 50) {
		cout << languagePack->getSentence("excess cash");
		return State::D_AskAmount_Cash;
	}
	if (transactionBill.getTotalNum() == 0) {
		cout << languagePack->getSentence("no cash");
		return State::D_AskAmount_Cash;
	}
	
	return State::D_Confirm_Cash;
}

UI::State UI::d_askAmount_Check() {
	cout << languagePack->getSentence("UI_d_askAmount_Check0.1") << fee << languagePack->getSentence("UI_d_askAmount_Check0.2");

	string prompt = languagePack->getSentence("UI_d_askAmount_Check1");
	prompt += languagePack->getSentence("cancel");
	depositCheckNum = getInput(prompt, 500);
	if (depositCheckNum == -1) {
		cout << languagePack->getSentence("exit deposit");
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
	prompt2 += languagePack->getSentence("cancel");
	int* input;
	input = getInputArray(prompt2, depositCheckNum, 100000000); // check 최대 입금 가능 장수 제한 없나? (금액을 묻는 곳! 어차피 나중에 금액 체크하긴 하는데 input은 크게 받을 수도 있게 해놨음)
	if (input[0] == -1) {
		cout << languagePack->getSentence("exit deposit");
		return State::ChooseTransaction;
	}
	depositCheckInput = input;
	return State::D_Confirm_Check;
}

UI::State UI::d_confirm_Cash() {
	cout << languagePack->getSentence("confirm amount");
	transactionBill.printBill(languagePack->isKor());
	int input = getInput("", 0);
	if (input == -1) {
		cout << languagePack->getSentence("exit deposit");
		cout << languagePack->getSentence("cash returned");
		return State::ChooseTransaction;
	}
	else if (input == 0) {
		return State::D_ConfirmTotal;
	}
	else {
		cout << languagePack->getSentence("unexpected"); // debug [Checked]
		return State::End;
	}
}

UI::State UI::d_confirm_Check() {
	cout << languagePack->getSentence("confirm amount");
	for (int i = 0; i < depositCheckNum; i++) {
		cout << "[" << depositCheckInput[i] << languagePack->getSentence("UI_d_confirm_Check0.2");
		depositCheckSum += depositCheckInput[i];
	}
	cout << endl;
	cout << languagePack->getSentence("UI_d_confirm_Check0.3") << depositCheckSum << languagePack->getSentence("UI_d_confirm_Check0.4");;
	int input = getInput("", 0);
	if (input == -1) {
		cout << languagePack->getSentence("exit deposit");
		cout << languagePack->getSentence("check returned");
		return State::ChooseTransaction;
	}
	else if (input == 0) {
		return State::D_ConfirmTotal;
	}
	else {
		cout << languagePack->getSentence("unexpected"); // debug [Checked]
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
	else { cout << languagePack->getSentence("unexpected"); return State::End; } // debug
	string prompt = languagePack->getSentence("UI_d_confirmTotal1.1");
	prompt += (to_string(depositAmount) + languagePack->getSentence("UI_d_confirmTotal1.2"));
	prompt += (to_string(fee) + languagePack->getSentence("UI_d_confirmTotal1.3"));
	prompt += to_string(depositAmount);
	prompt += languagePack->getSentence("UI_d_confirmTotal1.4");
	prompt += languagePack->getSentence("confirm");

	int input;
	input = getInput(prompt, 0);
	if (input == 0) { return State::D_Deposit; }
	if (input == -1) {
		cout << languagePack->getSentence("exit deposit");
		if (transactionType == 1) { cout << languagePack->getSentence("cash returned"); }
		else { cout << languagePack->getSentence("check returned"); }
		return State::ChooseTransaction;
	}

	cout << languagePack->getSentence("unexpected"); // debug [Checked]
	return State::End;
}

UI::State UI::d_deposit() {
	bool success = atm->deposit(transactionType, transactionBill, depositCheckInput, depositCheckNum, depositCheckSum, acc);
	if (success) {
		if (transactionType == 1) {
			cout << "[" << transactionBill.getSum() - fee << languagePack->getSentence("UI_d_deposit1");
		}
		if (transactionType == 2) {
			cout << "[" << depositCheckSum - fee << languagePack->getSentence("UI_d_deposit1");
		}
		cout << languagePack->getSentence("show balance1") << acc->getBalance() << languagePack->getSentence("show balance2");
		return State::ChooseTransaction;
	}
	else {
		return State::Deposit;
	}
}

/***********************	 Withdrawal  	***********************/

UI::State UI::withdrawal() {
	if (this->WithdrawalPerSession >= 3) {
		cout << languagePack->getSentence("UI_withdrawal0");
		return State::ChooseTransaction;
	}
	cout << languagePack->getSentence("UI_withdrawal1");
	fee = atm->fee(6, acc, nullptr);
	return State::W_AskAmount;
}

UI::State UI::w_askAmount() {
	transactionAmount = 0;

	cout << languagePack->getSentence("UI_w_askAmount0.1") << fee << languagePack->getSentence("UI_w_askAmount0.2");

	string prompt = languagePack->getSentence("UI_w_askAmount1");
	prompt += languagePack->getSentence("cancel");

	transactionAmount = getInput(prompt, 2000, 1); // 10000원짜리 장수; 한도 얼마로 해두는게 좋을까? [어차피 뒤에서 체크해서 아무 숫자나 넣어둔 것.]

	if (transactionAmount == -1) {
		cout << languagePack->getSentence("exit withdraw");
		return State::ChooseTransaction;
	}
	transactionBill = Bill{ 0, transactionAmount, 0, 0 };
	return State::W_CheckMaxAmount;
}

UI::State UI::w_checkMaxAmount() { // 출금한도 넘는 경우
	if (transactionBill.getSum() > 500000) {
		cout << languagePack->getSentence("UI_w_checkMaxAmount0");
		return State::W_AskAmount;
	}
	else { return State::W_CheckAccountBalance; }
}

UI::State UI::w_checkAccountBalance() { // 계좌 잔액 부족한 경우
	if ((transactionBill.getSum() + fee) > acc->getBalance()) {
		cout << languagePack->getSentence("UI_w_checkAccountBalance0");
		return State::W_AskAmount;
	}
	else { return State::W_CheckATMBalance; }
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
	prompt += languagePack->getSentence("confirm");

	int input;
	input = getInput(prompt, 0);
	if (input == 0) { return State::W_Withdrawal; }
	if (input == -1) {
		cout << languagePack->getSentence("exit withdraw");
		return State::ChooseTransaction;
	}

	cout << languagePack->getSentence("unexpected"); // debug [Checked]
	return State::End;
}

UI::State UI::w_withdrawal() {
	bool success = atm->withdrawal(transactionBill, acc);
	if (success) { // 출금 완료시
		this->WithdrawalPerSession++; // 이 세션 중 출금한 횟수 1회 늘리기
		cout << "[" << transactionBill.getSum() << languagePack->getSentence("UI_w_withdrawal1");
		cout << languagePack->getSentence("show balance1") << acc->getBalance() << languagePack->getSentence("show balance2");
		return State::ChooseTransaction;
	}
	else {
		return State::Withdrawal;
	}
}

/***********************	  Transfer  	***********************/

UI::State UI::transfer() {
	cout << languagePack->getSentence("UI_transfer0");
	// 혹시 모르니 초기화
	fee = 0;
	toAccID = 0;
	toAcc = nullptr;
	return State::T_AskTransferType;
}

UI::State UI::t_askTransferType() {
	int input;

	string prompt = languagePack->getSentence("UI_t_askTransferType0");
	prompt += languagePack->getSentence("cancel");
	prompt += languagePack->getSentence("UI_t_askTransferType0.1");
	input = getInput(prompt, 2, 1);
	if (input == -1) {
		cout << languagePack->getSentence("exit transfer");
		return State::ChooseTransaction;
	}

	transactionType = input;
	if (transactionType == 1) { cout << languagePack->getSentence("UI_t_askTransferType2"); }
	if (transactionType == 2) { cout << languagePack->getSentence("UI_t_askTransferType3"); }
	return State::T_AskToAcc;
}


UI::State UI::t_askToAcc() {
	int input;
	string prompt = languagePack->getSentence("UI_t_askToAcc0");
	prompt += languagePack->getSentence("cancel");
	input = getInput(prompt, 99998, 10000);
	if (input == -1) { return State::Transfer; }
	if (input == acc->getID()) { // 현재 계좌와 같은 계좌 입력
		cout << languagePack->getSentence("UI_t_askToAcc1");
		return State::T_AskToAcc;
	}
	toAccID = database->getIndexFromID(input);
	if (toAccID == -1) { // 존재하지 않는 계좌일 경우
		cout << languagePack->getSentence("UI_insertCard3");
		return State::T_AskToAcc;
	}
	toAcc = database->getAccountByNum(toAccID);
	return State::T_ConfirmToAcc;
}

UI::State UI::t_confirmToAcc() { // 금융실명제
	fee = atm->fee(7, acc, toAcc);

	int input;
	string prompt = languagePack->getSentence("UI_t_confirmToAcc0.1");
	prompt += toAcc->getOwner()->getName(languagePack->isKor()); // 받는 user 이름
	prompt += (languagePack->getSentence("UI_t_confirmToAcc0.2"));
	prompt += toAcc->getBank()->getName(languagePack->isKor()); // bank 이름
	prompt += languagePack->getSentence("UI_t_confirmToAcc0.2.0") + std::to_string(toAcc->getID()); // 받는 계좌
	prompt += languagePack->getSentence("UI_t_confirmToAcc0.3");
	prompt += languagePack->getSentence("cancel");
	prompt += languagePack->getSentence("UI_t_confirmToAcc0.4");
	input = getInput(prompt, 1);
	if (input == -1) { return State::ChooseTransaction; }
	if (input == 0) {
		if (transactionType == 1) { return State::T_AskAmount_C; }
		else { return State::T_AskAmount_A; }
	}
	if (input == 1) { return State::T_AskToAcc; }

	cout << languagePack->getSentence("unexpected"); // debug
	return State::End;
}

UI::State UI::t_askAmount_c() {
	cout << languagePack->getSentence("UI_t_askAmount_c0.1") << fee << languagePack->getSentence("UI_t_askAmount_c0.2");

	transactionAmount = 0;
	string prompt = (languagePack->getSentence("put cash"));

	int* inputArr;
	inputArr = getInputArray(prompt, 4, 500);
	if (inputArr[0] == -1) {
		cout << languagePack->getSentence("exit transfer");
		return State::ChooseTransaction;
	}
	atm->insertedBill = Bill{ inputArr[0], inputArr[1], inputArr[2], inputArr[3] };
	if (atm->insertedBill.getTotalNum() > 50) {
		cout << languagePack->getSentence("excess cash");
		return State::T_AskAmount_C;
	}
	if (atm->insertedBill.getTotalNum() == 0) {
		cout << languagePack->getSentence("no cash");
		return State::T_AskAmount_C;
	}
	transactionAmount = atm->insertedBill.getSum();

	int input;
	cout << languagePack->getSentence("confirm amount");
	atm->insertedBill.printBill(this->languagePack->isKor());

	input = getInput("", 0);

	if (input == 0) { return State::T_Confirm; }
	if (input == -1) {
		cout << languagePack->getSentence("exit transfer");
		cout << languagePack->getSentence("cash returned");
		return State::ChooseTransaction; // 어디로 가게 할 것?
	}

	cout << languagePack->getSentence("unexpected"); // debug
	return State::End;
}


UI::State UI::t_askAmount_a() {
	atm->insertedBill = Bill{ 0,0,0,0 };

	cout << languagePack->getSentence("UI_t_askAmount_a0.1") << fee; // debug
	cout << languagePack->getSentence("UI_t_askAmount_a0.2"); // debug

	transactionAmount = 0;
	string prompt = languagePack->getSentence("UI_t_askAmount_a1.1");
	prompt += std::to_string(acc->getBalance());
	prompt += languagePack->getSentence("UI_t_askAmount_a1.2");
	prompt += languagePack->getSentence("cancel");

	int input;
	input = getInput(prompt, 2000000, 1); // 송금한도액? (일단 200만원으로)
	if (input == -1) {
		cout << languagePack->getSentence("exit transfer") << endl;
		return State::ChooseTransaction;
	}

	transactionAmount = input;

	prompt = languagePack->getSentence("UI_t_askAmount_a2.1") + std::to_string(transactionAmount);
	prompt += languagePack->getSentence("UI_t_askAmount_a2.2");
	prompt += languagePack->getSentence("confirm");
	input = getInput(prompt, 0);

	if (input == 0) { return State::T_Confirm; }
	if (input == -1) {
		cout << languagePack->getSentence("exit transfer");
		return State::ChooseTransaction;
	}

	cout << languagePack->getSentence("unexpected");
	return State::End;
}

UI::State UI::t_confirm() {
	string prompt = "";
	// 한글/영어 어순 달라서 조건문 사용
	if (languagePack->isKor()) {
		prompt += "[" + toAcc->getOwner()->getName() + languagePack->getSentence("UI_t_confirm0.2");
		prompt += (std::to_string(transactionAmount) + languagePack->getSentence("UI_t_confirm0.3"));
		prompt += (std::to_string(fee) + languagePack->getSentence("UI_t_confirm0.4"));
		prompt += std::to_string(acc->getBalance());
		prompt += languagePack->getSentence("UI_t_confirm0.5");
		prompt += languagePack->getSentence("confirm");
	}
	else {
		prompt += (languagePack->getSentence("UI_t_confirm0.1") + std::to_string(transactionAmount) + languagePack->getSentence("UI_t_confirm0.2"));
		prompt += (toAcc->getOwner()->getName(false) + languagePack->getSentence("UI_t_confirm0.3"));
		prompt += (std::to_string(fee) + languagePack->getSentence("UI_t_confirm0.4"));
		prompt += std::to_string(acc->getBalance());
		prompt += languagePack->getSentence("UI_t_confirm0.5");
		prompt += languagePack->getSentence("confirm");
	}

	int input;
	input = getInput(prompt, 0);
	if (input == 0) { return State::T_Transfer; }
	if (input == -1) {
		cout << languagePack->getSentence("exit transfer");
		if (transactionType == 1) {
			cout << languagePack->getSentence("cash returned");
		}
		return State::ChooseTransaction;
	}

	cout << languagePack->getSentence("unexpected"); // debug
	return State::End;
}

UI::State UI::t_transfer() {
	bool success = atm->transfer(transactionType, transactionAmount, acc, toAcc, atm->insertedBill);
	if (success) {
		cout << "\t[" << transactionAmount << languagePack->getSentence("UI_t_transfer1.1");
		cout << toAcc->getOwner()->getName(languagePack->isKor());
		cout << languagePack->getSentence("UI_t_transfer1.2");

		cout << languagePack->getSentence("show balance1");
		cout << acc->getBalance() << languagePack->getSentence("show balance2");

		return State::ChooseTransaction;
	}
	else {
		cout << languagePack->getSentence("not enough balance");
		if (transactionType == 1) {
			cout << languagePack->getSentence("cash returned");
		}
		return State::ChooseTransaction;
	}
}

UI::State UI::sessionOver() {
	database->printSessionHistory();
	database->clearSessionHistory();
	cout << languagePack->getSentence("common exit");
	return State::ChangeLanguage;
}
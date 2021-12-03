#pragma once
#include <iostream>
#include <string>

class UI {
private:
	enum class State {
		ChangeLanguage,
		// ReturnCard,
		GetATM,
		InsertCard,
		VerifyAccount,
		CheckAccount,
		VerifyAdmin,
		ShowAdmin,
		ChooseTransaction,
		Deposit,
		D_AskDepositType,
		D_AskAmount_Cash,
		D_AskAmount_Check,
		D_Confirm_Cash,
		D_Confirm_Check,
		D_ConfirmTotal,
		D_Deposit,
		Transfer,
		T_AskTransferType,
		T_AskToAcc,
		T_ConfirmToAcc,
		T_AskAmount_C,
		T_AskAmount_A,
		T_Confirm,
		T_Transfer,
		Withdrawal,
		W_AskAmount,
		W_CheckAccountBalance,
		W_CheckMaxAmount,
		W_CheckATMBalance,
		W_Confirm,
		W_Withdrawal,
		SessionOver,
		End
	}
	state = State::ChangeLanguage;
	// int UserStatus = 1;
	int accountNum = 0;
	int transactionType = 0;
	int FirstDigit = 0; // needed to be deleted
	int SecondDigit = 0; // needed to be deleted
	int accID = -1; // 현재 계좌 index
	// int userIndex = -1; // 현재 계좌번호(겹침)
	Account* acc = nullptr; // 현재 계좌
	int toAccID = -1; // 송금 상대 계좌 index; 송금시에만 사용
	Account* toAcc = nullptr; // 송금 상대 계좌; 송금시에만 사용
	int* depositCheckInput = new int[30];// 입금시에만 사용
	int depositCheckNum = 0;// 입금시에만 사용
	int depositCheckSum = 0;// 입금시에만 사용
	int fee = 0;
	int transactionAmount = 0; // transaction 으로 이름 변경함.
	Bill transactionBill = Bill{ 0,0,0,0 };
	Database* database = nullptr; // database 사용 (바꿔야 할 수도)
	ATM* atm = nullptr; // the ATM we are using
	Translation* languagePack = new Translation();
	// int SessionStartNum = 0; // 한 거래가 진행될때마다 1로 증가
	int WithdrawalPerSession = 0;

public:
	int run();
	~UI() { delete languagePack; }
private:
	static int getInput(const std::string& prompt, int minimum, int maximum, bool enableCancel);
	static int* getInputArray(const std::string& prompt, int length, int minimum, int maximum, bool);
	State changeLanguage();
	// State returnCard();
	State getATM();
	State insertCard();
	State verifyAccount();
	State verifyAdmin();
	State showAdmin();
	State checkAccount();
	State enterAdmin();
	State chooseTransaction();
	State withdrawal();
	State w_askAmount();
	State w_checkAccountBalance();
	State w_checkMaxAmount();
	State w_checkATMBalance();
	State w_confirm();
	State w_withdrawal();
	State deposit();
	State d_askDepositType();
	State d_askAmount_Cash();
	State d_askAmount_Check();
	State d_confirm_Cash();
	State d_confirm_Check();
	State d_confirmTotal();
	State d_deposit();
	State transfer();
	State t_askTransferType();
	State t_askToAcc();
	State t_confirmToAcc();
	State t_askAmount_c();
	State t_askAmount_a();
	State t_confirm();
	State t_transfer();
	State sessionOver();
};
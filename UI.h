#pragma once
#include "Classes.cpp"
#include <iostream>
#include <string>

class UI {
private:
	enum class State {
		GetATM,
		GetAccountNum,
		AccessAccount,
		VerifyAccount,
		CheckAccount,
		VerifyAdmin,
		ShowAdmin,
		ChooseTransaction,
		Deposit,
		Transfer,
		T_AskTransferType,
		T_AskToAcc,
		T_ConfirmToAcc,
		T_AskAmount_C,
		T_AskAmount_A,
		T_Confirm,
		T_Transfer,
		Withdrawal,
		Session1Prompt,
		Session1Digit,
		Session1Confirm,
		Session2Prompt,
		Session2Digit,
		Session2Confirm,
		Session3Prompt,
		Session3Confirm,
		End
	}
	state = State::GetAccountNum;
	// int UserStatus = 1;
	int accountNum = 0;
	int transferType = 0;
	int FirstDigit = 0; // needed to be deleted
	int SecondDigit = 0; // needed to be deleted
	int accID = -1;
	Account* acc = nullptr;
	int toAccID = -1;
	Account* toAcc = nullptr; // 송금시에만 사용
	int fee = 0;
	int transferAmount = 0;
	Database* database = nullptr; // database 사용 (바꿔야 할 수도)
	ATM* atm = nullptr; // the ATM we are using
	Database* database;

public:
	int run();
private:
	static int getInput(const std::string& prompt, int minimum, int maximum, bool);
	State getATM();
	State getAccountNum();
	State accessAccount();
	State verifyAccount();
	State verifyAdmin();
	State showAdmin();
	State checkAccount();
	State enterAdmin();
	State chooseTransaction();
	State withdrawal();
	State deposit();
	State transfer();
	State t_askTransferType();
	State t_askToAcc();
	State t_confirmToAcc();
	State t_askAmount_c();
	State t_askAmount_a();
	State t_confirm();
	State t_transfer();
	State Session1Prompt();
	State session1Digit();
	State session1Confirm();
	State session2Prompt();
	State session2Digit();
	State session2Confirm();
	State session3Prompt();
	State session3Confirm();
	void end();
};
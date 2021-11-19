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
		T_GetToAcc,
		T_ConfirmToAcc,
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
	int FirstDigit = 0;
	int SecondDigit = 0;
	Account* acc = nullptr;
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
	State Session1Prompt();
	State session1Digit();
	State session1Confirm();
	State session2Prompt();
	State session2Digit();
	State session2Confirm();
	State session3Prompt();
	State session3Confirm();
};
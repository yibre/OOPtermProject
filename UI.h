#pragma once
#include "Classes.h"
#include <iostream>
#include <string>

class UI {
private:
	enum class State {
		GetAccountNum,
		AccessAccount,
		VerifyAccount,
		CheckAccount,
		EnterAdmin,
		ChooseTransaction,
		Deposit,
		Transfer,
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
	Account* myAccount = nullptr;
	ATM* atm = nullptr; // the ATM we are using

public:
	int run();
private:
	static int getInput(const std::string& prompt, int minimum, int maximum);
	State getAccountNum();
	State accessAccount();
	State verifyAccount();
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
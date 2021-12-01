#include "Language.h"

Translation::Translation() {
	/********************	 UI	 ********************/
	/********************	 state functions	 ********************/
	string function = "UI_changeLanguage";
	translation_en.insert(pair<string, string>(function + "0", "The language has been changed to English.\n"));
	translation_kr.insert(pair<string, string>(function + "0","언어가 한국어로 변경되었습니다.\n" ));
	
	translation_en.insert(pair<string, string>(function + "1", "The language change has been canceled.\n")); // 문장이상할지도?
	translation_kr.insert(pair<string, string>(function + "1","언어 변경이 취소되었습니다.\n" ));
	
	translation_en.insert(pair<string, string>(function + "2", "Debug : Error\n"));
	translation_kr.insert(pair<string, string>(function + "2", "Debug : Error\n"));
		
	function = "UI_getAccountNum";
	translation_en.insert(pair<string, string>(function + "0", "Please insert your debit card. (Enter the account number.)\n"));
	translation_kr.insert(pair<string, string>(function + "0", "카드를 삽입해 주십시오. (계좌 번호를 입력해 주십시오.)\n" ));
	
	function = "UI_accessAccount";
	translation_en.insert(pair<string, string>(function + "0", "Your account : "));
	translation_kr.insert(pair<string, string>(function + "0", "계좌번호 : "));

	translation_en.insert(pair<string, string>(function + "1", "Canceled; Goto session 0\n"));
	translation_kr.insert(pair<string, string>(function + "1", "Canceled; Goto session 0\n"));

	translation_en.insert(pair<string, string>(function + "2", "This card is not supported by this ATM.\nYour card has been returned. Please take your card.\n"));
	translation_kr.insert(pair<string, string>(function + "2", "본 ATM에서 지원하지 않는 은행의 계좌입니다.\n카드가 반환되었습니다. 투입구를 확인해 주십시오.\n"));

	function = "UI_verifyAdmin";
	translation_en.insert(pair<string, string>(function + "0", "You have inserted an admin card.\n"));
	translation_kr.insert(pair<string, string>(function + "0", "관리자 카드가 삽입되었습니다.\n"));

	translation_en.insert(pair<string, string>(function + "1", "Enter the password to access admin panel : "));
	translation_kr.insert(pair<string, string>(function + "1", "관리자 패널에 접속하시려면 비밀번호를 입력해 주십시오 : "));

	translation_en.insert(pair<string, string>(function + "2", "You have entered wrong password.\n"));
	translation_kr.insert(pair<string, string>(function + "2", "비밀번호가 틀렸습니다.\n"));

	function = "UI_checkAccount";
	translation_en.insert(pair<string, string>(function + "0.1", "\t Your account number is : "));
	translation_kr.insert(pair<string, string>(function + "0.1", "\t 계좌번호가 : "));
	translation_en.insert(pair<string, string>(function + "0.2", "\n\tIs this correct?\n\t(0 to confirm; -1 to cancel)\n"));
	translation_kr.insert(pair<string, string>(function + "0.2", "\t가 맞습니까?\n\t(0번을 눌러 확인; -1을 눌러 취소)\n"));

	translation_en.insert(pair<string, string>(function + "1", "Debug: Unexpected behavior in UI::checkAccount\n"));
	translation_kr.insert(pair<string, string>(function + "1", "Debug: Unexpected behavior in UI::checkAccount\n"));

	function = "UI_verifyAccount";
	translation_en.insert(pair<string, string>(function + "0", "\t Enter the password : "));
	translation_kr.insert(pair<string, string>(function + "0", "\t 비밀번호를 입력해 주십시오 : "));

	translation_en.insert(pair<string, string>(function + "1.0", "Wrong password. Please try again. (You have left "));
	translation_kr.insert(pair<string, string>(function + "1.0", "비밀번호가 틀렸습니다. 다시 시도해 주십시오. (남은 횟수 :"));

	translation_en.insert(pair<string, string>(function + "1.1", " attempt(s).)\n"));
	translation_kr.insert(pair<string, string>(function + "1.1", " 회)\n"));
	
	translation_en.insert(pair<string, string>(function + "2", "You have made three wrong attempts.\n"));
	translation_kr.insert(pair<string, string>(function + "2", "비밀번호를 3회 틀리셨습니다.\n"));
	
	function = "UI_enterAdmin";
	translation_en.insert(pair<string, string>(function + "0", "Enter admin class\n"));
	translation_kr.insert(pair<string, string>(function + "0", "관리자 클래스로 진입합니다.\n"));

	function = "UI_chooseTransaction";
	translation_en.insert(pair<string, string>(function + "0", "\tWhat would you like to do?\n\t1. deposit\t 2. withdrawal\t 3. transfer\n\tCancel : -1\n"));
	translation_kr.insert(pair<string, string>(function + "0", "\t무엇을 하시겠습니까?\n\t1. 입금\t 2. 출금\t 3. 송금\n\t취소 : -1\n"));

	translation_en.insert(pair<string, string>(function + "1", "Your card has been returned. Please take your card.\n"));
	translation_kr.insert(pair<string, string>(function + "1", "카드가 반환되었습니다. 투입구를 확인해 주십시오.\n"));

	translation_en.insert(pair<string, string>(function + "2", "Wrong input. Please try again.\n"));
	translation_kr.insert(pair<string, string>(function + "2", "잘못된 입력입니다. 다시 선택해 주십시오.\n"));

	/********************	 Deposit	 ********************/
	function = "UI_d_askDepositType";
	translation_en.insert(pair<string, string>(function + "0", "Please choose how to deposit money among cash and checks.\n\t1. cash\t2. check\tCancel : -1\n"));
	translation_kr.insert(pair<string, string>(function + "0", "현금, 수표 중 입금하실 방법을 선택해 주십시오.\n\t1. 현금\t2. 수표\t취소 : -1\n"));
	
	translation_en.insert(pair<string, string>(function + "1", "You have exited the deposit session.\n"));
	translation_kr.insert(pair<string, string>(function + "1", "입금을 취소하셨습니다.\n"));

	translation_en.insert(pair<string, string>(function + "2", "You have chosen a cash deposit.\n"));
	translation_kr.insert(pair<string, string>(function + "2", "현금 입금을 선택하셨습니다.\n"));

	translation_en.insert(pair<string, string>(function + "3", "You have chosen a check deposit.\n"));
	translation_kr.insert(pair<string, string>(function + "3", "수표 입금을 선택하셨습니다.\n"));

	translation_en.insert(pair<string, string>(function + "4", "Canceled; Goto session 0\n"));
	translation_kr.insert(pair<string, string>(function + "4", "Canceled; Goto session 0\n"));

	function = "UI_d_askAmount_Cash";
	translation_en.insert(pair<string, string>(function + "0.1", "Debug: Deposit fee would be ["));
	translation_kr.insert(pair<string, string>(function + "0.1", "Debug: 수수료는 ["));
	translation_en.insert(pair<string, string>(function + "0.2", "] won.\n"));
	translation_kr.insert(pair<string, string>(function + "0.2", "]원입니다.\n"));

	translation_en.insert(pair<string, string>(function + "1", "Please put your cash in the cash/check slot. (Input in the order of 50,000 won, 10,000 won, 5,000 won, and 1,000 won bills.)\n\tCancel : -1\n"));
	translation_kr.insert(pair<string, string>(function + "1", "투입구에 현금을 넣어 주십시오. (5만원권, 1만원권, 5천원권, 1천원권 순으로 입력해 주십시오.)\n\t취소 : -1\n"));

	translation_en.insert(pair<string, string>(function + "2", "You have exited the deposit session.\n"));
	translation_kr.insert(pair<string, string>(function + "2", "입금을 취소하셨습니다.\n"));

	translation_en.insert(pair<string, string>(function + "3", "The maximum number of available bills has been exceeded. Please try again.\n"));
	translation_kr.insert(pair<string, string>(function + "3", "최대 입금 가능 장 수를 초과하였습니다. 다시 시도해 주십시오.\n"));

	translation_en.insert(pair<string, string>(function + "4", "There is no cash in the cash/check slot. Please try again.\n"));
	translation_kr.insert(pair<string, string>(function + "4", "투입구에 현금이 들어있지 않습니다. 다시 시도해 주십시오.\n"));

	function = "UI_d_askAmount_Check";
	translation_en.insert(pair<string, string>(function + "0.1", "Debug: Deposit fee would be ["));
	translation_kr.insert(pair<string, string>(function + "0.1", "Debug: 수수료는 ["));
	translation_en.insert(pair<string, string>(function + "0.2", "] won.\n"));
	translation_kr.insert(pair<string, string>(function + "0.2", "]원입니다.\n"));

	translation_en.insert(pair<string, string>(function + "1", "Please enter the number of checks you want to put in.\n\tCancel : -1\n"));
	translation_kr.insert(pair<string, string>(function + "1", "투입하실 수표의 장 수를 입력해 주십시오.\n\t취소 : -1\n"));

	translation_en.insert(pair<string, string>(function + "2", "You have exited the deposit session.\n"));
	translation_kr.insert(pair<string, string>(function + "2", "입금을 취소하셨습니다.\n"));

	translation_en.insert(pair<string, string>(function + "3", "There is no check in the cash/check slot. Please try again.\n"));
	translation_kr.insert(pair<string, string>(function + "3", "투입구에 수표가 들어있지 않습니다. 다시 시도해 주십시오.\n"));

	translation_en.insert(pair<string, string>(function + "4", "The maximum number of available checks has been exceeded. Please try again.\n"));
	translation_kr.insert(pair<string, string>(function + "4", "최대 입금 가능 장 수를 초과하였습니다. 다시 시도해 주십시오.\n"));

	translation_en.insert(pair<string, string>(function + "5", "Please enter the amount of each check.\n"));
	translation_kr.insert(pair<string, string>(function + "5", "각 수표의 액수를 입력해 주십시오.\n"));

	translation_en.insert(pair<string, string>(function + "6", "You have exited the deposit session.\n"));
	translation_kr.insert(pair<string, string>(function + "6", "입금을 취소하셨습니다.\n"));

	function = "UI_d_confirm_Cash";
	translation_en.insert(pair<string, string>(function + "0", "Please make sure if the amount you put in is correct.\nConfirm : 0\tCancel : -1\n"));
	translation_kr.insert(pair<string, string>(function + "0", "투입하신 금액이 맞는지 확인해 주십시오.\n확인 : 0\t취소 : -1\n"));
	
	translation_en.insert(pair<string, string>(function + "1", "You have exited the deposit session.\nThe cash you put in has been returned.\nPlease make sure to take your cash.\n"));
	translation_kr.insert(pair<string, string>(function + "1", "현금 입금을 취소하셨습니다.\n투입하신 현금이 반환되었습니다.\n투입구를 확인해 주십시오.\n"));

	translation_en.insert(pair<string, string>(function + "2", "Error\n"));
	translation_kr.insert(pair<string, string>(function + "2", "Error\n"));

	function = "UI_d_confirm_Check";
	translation_en.insert(pair<string, string>(function + "0.1", "Please make sure if the amount you put in is correct.\nConfirm : 0\tCancel : -1\nAmount : "));
	translation_kr.insert(pair<string, string>(function + "0.1", "투입하신 금액이 맞는지 확인해 주십시오.\n확인 : 0\t취소 : -1\n금액 : "));
	translation_en.insert(pair<string, string>(function + "0.2", " won "));
	translation_kr.insert(pair<string, string>(function + "0.2", "원 "));
	translation_en.insert(pair<string, string>(function + "0.3", "Total amount : "));
	translation_kr.insert(pair<string, string>(function + "0.3", "총 액수 : "));
	translation_en.insert(pair<string, string>(function + "0.4", " won\n"));
	translation_kr.insert(pair<string, string>(function + "0.4", "원\n"));

	translation_en.insert(pair<string, string>(function + "1", "You have exited the deposit session.\nThe check(s) you put in has been returned.\nPlease make sure to take your check(s).\n"));
	translation_kr.insert(pair<string, string>(function + "1", "수표 입금을 취소하셨습니다.\n투입하신 수표가 반환되었습니다.\n투입구를 확인해 주십시오.\n"));

	translation_en.insert(pair<string, string>(function + "2", "Error\n"));
	translation_kr.insert(pair<string, string>(function + "2", "Error\n"));

	function = "UI_d_confirmTotal";
	translation_en.insert(pair<string, string>(function + "0", "Error\n"));
	translation_kr.insert(pair<string, string>(function + "0", "Error\n"));

	translation_en.insert(pair<string, string>(function + "1.1", "Do you want to deposit ["));
	translation_kr.insert(pair<string, string>(function + "1.1", "계좌로 ["));
	translation_en.insert(pair<string, string>(function + "1.2", "] won into your account?\nThe fee is["));
	translation_kr.insert(pair<string, string>(function + "1.2", "]원 입금하시겠습니까?\n수수료는 ["));
	translation_en.insert(pair<string, string>(function + "1.3", "] won. The fee will be automatically deducted from ["));
	translation_kr.insert(pair<string, string>(function + "1.3", "]원입니다. 수수료는 현재 입금하실 금액 ["));
	translation_en.insert(pair<string, string>(function + "1.4", "] won.\n\tConfirm : 0\n\tCancel : -1\n"));
	translation_kr.insert(pair<string, string>(function + "1.4", "]원에서 자동 차감됩니다.\n\t확인 : 0\n\t취소: -1\n"));

	translation_en.insert(pair<string, string>(function + "2", "You have exited the deposit session.\n"));
	translation_kr.insert(pair<string, string>(function + "2", "입금을 취소하셨습니다.\n"));

	translation_en.insert(pair<string, string>(function + "3", "Debug: Unexpected behavior in UI::d_confirm\n"));
	translation_kr.insert(pair<string, string>(function + "3", "Debug: Unexpected behavior in UI::d_confirm\n"));

	function = "UI_d_deposit";
	translation_en.insert(pair<string, string>(function + "0", "Debug: Remaining cash of the ATM : "));
	translation_kr.insert(pair<string, string>(function + "0", "Debug: Remaining cash of the ATM : "));

	/********************	 Withdrawal	 ********************/
	function = "UI_withdrawal";
	translation_en.insert(pair<string, string>(function + "0", "You can withdraw only 3 times in one session.\n"));
	translation_kr.insert(pair<string, string>(function + "0", "해당 세션의 출금 한도(3회)를 초과하였습니다.\n"));
	
	function = "UI_w_askAmount";
	translation_en.insert(pair<string, string>(function + "0.1", "Debug: Withdrawal fee would be ["));
	translation_kr.insert(pair<string, string>(function + "0.1", "Debug: 수수료는 ["));
	translation_en.insert(pair<string, string>(function + "0.2", "] won.\n"));
	translation_kr.insert(pair<string, string>(function + "0.2", "]원입니다.\n"));

	translation_en.insert(pair<string, string>(function + "1", "Please enter the amount you want to withdraw. (Unit : 10000won)\tCancel : -1\n"));
	translation_kr.insert(pair<string, string>(function + "1", "출금하실 금액을 입력해 주십시오. (단위 : 만원)\t취소 : -1\n"));

	translation_en.insert(pair<string, string>(function + "2", "You have exited the withdrawal session.\n"));
	translation_kr.insert(pair<string, string>(function + "2", "출금을 취소하셨습니다.\n"));

	function = "UI_w_checkAccountBalance";
	translation_en.insert(pair<string, string>(function + "0", "There is not enough balance in the account. Please try again.\n"));
	translation_kr.insert(pair<string, string>(function + "0", "계좌에 잔액이 부족합니다. 다시 시도해주십시오.\n"));

	function = "UI_w_checkMaxAmount";
	translation_en.insert(pair<string, string>(function + "0", "It exceeded the maximum withdrawal amount (300,000 won) per time. Please try again.\n"));
	translation_kr.insert(pair<string, string>(function + "0", "1회 최대 출금 금액(30만원)을 초과하였습니다. 다시 시도해주십시오.\n"));

	function = "UI_w_checkATMBalance";
	translation_en.insert(pair<string, string>(function + "0", "There is a shortage of cash inside the ATM machine.\n"));
	translation_kr.insert(pair<string, string>(function + "0", "ATM 기 내부에 현금이 부족합니다.\n"));

	function = "UI_w_confirm";
	translation_en.insert(pair<string, string>(function + "0.1", "Do you want to withdraw ["));
	translation_kr.insert(pair<string, string>(function + "0.1", "계좌에서 ["));
	translation_en.insert(pair<string, string>(function + "0.2", "] won from your account?\nThe fee is["));
	translation_kr.insert(pair<string, string>(function + "0.2", "]원 출금하시겠습니까?\n수수료는 ["));
	translation_en.insert(pair<string, string>(function + "0.3", "] won. The fee will be automatically deducted from the current account balance of ["));
	translation_kr.insert(pair<string, string>(function + "0.3", "]원입니다. 수수료는 현재 계좌 잔액 ["));
	translation_en.insert(pair<string, string>(function + "0.4", "] won.\n\tConfirm : 0\n\tCancel : -1\n"));
	translation_kr.insert(pair<string, string>(function + "0.4", "]원에서 자동 차감됩니다.\n\t확인 : 0\n\t취소: -1\n"));

	translation_en.insert(pair<string, string>(function + "1", "You have exited the withdrawal session.\n"));
	translation_kr.insert(pair<string, string>(function + "1", "출금을 취소하셨습니다.\n"));

	translation_en.insert(pair<string, string>(function + "2", "Debug: Unexpected behavior in UI::w_confirm\n"));
	translation_kr.insert(pair<string, string>(function + "2", "Debug: Unexpected behavior in UI::w_confirm\n"));

	function = "UI_w_withdrawal";
	translation_en.insert(pair<string, string>(function + "0", "Debug: Remaining cash of the ATM : "));
	translation_kr.insert(pair<string, string>(function + "0", "Debug: Remaining cash of the ATM : "));

	/********************	 Transfer	 ********************/
	function = "UI_t_askTransferType";
	translation_en.insert(pair<string, string>(function + "0", "Which transfer option would you like?\n\t1. Cash transfer\t2. Account transfer\n\tCancel : -1\n"));
	translation_kr.insert(pair<string, string>(function + "0", "원하시는 송금 옵션을 선택해 주십시오.\n\t1. 현금 송금\t2. 계좌송금\n\t취소 : -1\n"));

	translation_en.insert(pair<string, string>(function + "1", "You have exited the transfer session.\n"));
	translation_kr.insert(pair<string, string>(function + "1", "송금을 취소하셨습니다.\n"));

	translation_en.insert(pair<string, string>(function + "2", "You have chosen cash transfer.\n"));
	translation_kr.insert(pair<string, string>(function + "2", "현금 송금을 선택하셨습니다.\n"));

	translation_en.insert(pair<string, string>(function + "3", "You have chosen account transfer.\n"));
	translation_kr.insert(pair<string, string>(function + "3", "계좌 송금을 선택하셨습니다.\n"));
	
	function = "UI_t_askToAcc";
	translation_en.insert(pair<string, string>(function + "0", "Please enter the account you would like to transfer your money to.\n\tCancel : -1\n"));
	translation_kr.insert(pair<string, string>(function + "0", "송금하실 계좌의 계좌번호를 입력해 주십시오.\n\t취소 : -1\n"));

	function = "UI_t_confirmToAcc";
	translation_en.insert(pair<string, string>(function + "0.1", "Is ["));
	translation_kr.insert(pair<string, string>(function + "0.1", "["));
	translation_en.insert(pair<string, string>(function + "0.2", "]'s account [")); // 여기 연결되는 이름 영어이름으로
	translation_kr.insert(pair<string, string>(function + "0.2", "] 님의 계좌 ["));
	translation_en.insert(pair<string, string>(function + "0.3", "]?\n\t0. Yes\t1. Try different account\n\tCancel : -1\n"));
	translation_kr.insert(pair<string, string>(function + "0.3", "]가 맞습니까?\n\t0. 예\t1. 다시 입력\n\t취소 : -1\n"));

	translation_en.insert(pair<string, string>(function + "1", "Debug: Unexpected behavior in UI::t_confirmToAcc\n"));
	translation_kr.insert(pair<string, string>(function + "1", "Debug: Unexpected behavior in UI::t_confirmToAcc\n"));

	function = "UI_t_askAmount_c";
	translation_en.insert(pair<string, string>(function + "0.1", "Debug: Transfer fee would be ["));
	translation_kr.insert(pair<string, string>(function + "0.1", "Debug: 수수료는 ["));
	translation_en.insert(pair<string, string>(function + "0.2", "] won.\n"));
	translation_kr.insert(pair<string, string>(function + "0.2", "]원입니다.\n"));

	translation_en.insert(pair<string, string>(function + "1", "Please insert cash you would like to transfer.\n\tCancel : -1\n"));
	translation_kr.insert(pair<string, string>(function + "1", "송금할 현금을 투입해 주십시오. (5만원권, 1만원권, 5천원권, 1천원권 개수 순으로 입력)\n\t취소 : -1\n"));

	translation_en.insert(pair<string, string>(function + "2", "Debug: cash transfer; transfer amount : "));
	translation_kr.insert(pair<string, string>(function + "2", "Debug: cash transfer; transfer amount : "));

	translation_en.insert(pair<string, string>(function + "3.1", "Please make sure if the amount you put in is correct.\n\t["));
	translation_kr.insert(pair<string, string>(function + "3.1", "투입하신 금액이 맞는지 확인해 주십시오.\n\t["));
	translation_en.insert(pair<string, string>(function + "3.2", "]won\n\t0. Confirm\n\tCancel : -1\n"));
	translation_kr.insert(pair<string, string>(function + "3.2", "]원\n\t0. 확인\n\t취소 : -1\n"));
	
	translation_en.insert(pair<string, string>(function + "4", "You have exited the transfer session.\nThe cash you put in has been returned. Please make sure to take your cash.\n"));
	translation_kr.insert(pair<string, string>(function + "4", "송금을 취소하셨습니다.\n투입하신 현금이 반환되었습니다. 투입구를 확인해 주십시오.\n"));

	translation_en.insert(pair<string, string>(function + "5", "Debug: Unexpected behavior in UI::t_askAmount_c\n"));
	translation_kr.insert(pair<string, string>(function + "5", "Debug: Unexpected behavior in UI::t_askAmount_c\n"));
	
	function = "UI_t_askAmount_a";
	translation_en.insert(pair<string, string>(function + "0.1", "Debug: Transfer fee would be ["));
	translation_kr.insert(pair<string, string>(function + "0.1", "Debug: 수수료는 ["));
	translation_en.insert(pair<string, string>(function + "0.2", "] won.\n"));
	translation_kr.insert(pair<string, string>(function + "0.2", "]원입니다.\n"));

	translation_en.insert(pair<string, string>(function + "1.1", "Please enter the amount of money you would like to transfer. (Your current balance : "));
	translation_kr.insert(pair<string, string>(function + "1.1", "송금할 금액을 입력해 주십시오. (계좌 잔액 : "));
	translation_en.insert(pair<string, string>(function + "1.2", ")\n\tCancel : -1\n"));
	translation_kr.insert(pair<string, string>(function + "1.2", ")\n\t취소 : -1\n"));

	translation_en.insert(pair<string, string>(function + "2", "Debug: cash transfer; transfer amount : "));
	translation_kr.insert(pair<string, string>(function + "2", "Debug: cash transfer; transfer amount : "));
	
	translation_en.insert(pair<string, string>(function + "3", "You have exited the transfer session.\n"));
	translation_kr.insert(pair<string, string>(function + "3", "송금을 취소하셨습니다.\n"));

	translation_en.insert(pair<string, string>(function + "4", "Debug: Unexpected behavior in UI::t_askAmount_c\n"));
	translation_kr.insert(pair<string, string>(function + "4", "Debug: Unexpected behavior in UI::t_askAmount_c\n"));

	function = "UI_t_confirm";
	translation_en.insert(pair<string, string>(function + "0.1", "Would you like to transfer ["));
	translation_en.insert(pair<string, string>(function + "0.2", "] won to ["));
	translation_en.insert(pair<string, string>(function + "0.3", "]?\nThe fee is["));
	translation_en.insert(pair<string, string>(function + "0.4", "] won. The fee will be automatically deducted from the current account balance of ["));
	translation_en.insert(pair<string, string>(function + "0.5", "] won.\n\tConfirm : 0\n\tCancel : -1\n"));
	translation_kr.insert(pair<string, string>(function + "0.1", "["));
	translation_kr.insert(pair<string, string>(function + "0.2", "] 님에게 ["));
	translation_kr.insert(pair<string, string>(function + "0.3", "]원 송금하시겠습니까?\n수수료는 ["));
	translation_kr.insert(pair<string, string>(function + "0.4", "]원입니다. 수수료는 현재 계좌 잔액 ["));
	translation_kr.insert(pair<string, string>(function + "0.5", "]원에서 자동 차감됩니다.\n\t확인 : 0\n\t취소: -1\n"));

	translation_en.insert(pair<string, string>(function + "1", "You have exited the transfer session.\n"));
	translation_kr.insert(pair<string, string>(function + "1", "송금을 취소하셨습니다.\n"));

	translation_en.insert(pair<string, string>(function + "2", "The cash you put in has been returned. Please make sure to take your cash.\n"));
	translation_kr.insert(pair<string, string>(function + "2", "투입하신 현금이 반환되었습니다. 투입구를 확인해 주십시오.\n"));

	translation_en.insert(pair<string, string>(function + "3", "Debug: Unexpected behavior in UI::t_confirm\n"));
	translation_kr.insert(pair<string, string>(function + "3", "Debug: Unexpected behavior in UI::t_confirm\n"));

	function = "UI_t_transfer";
	translation_en.insert(pair<string, string>(function + "0", "Debug: Remaining cash of the ATM : "));
	translation_kr.insert(pair<string, string>(function + "0", "Debug: Remaining cash of the ATM : "));

	translation_en.insert(pair<string, string>(function + "1", "There is not enough balance in the account.\n"));
	translation_kr.insert(pair<string, string>(function + "1", "계좌에 잔액이 부족합니다.\n"));

	translation_en.insert(pair<string, string>(function + "2", "The cash you put in has been returned. Please make sure to take your cash.\n"));
	translation_kr.insert(pair<string, string>(function + "2", "투입하신 현금이 반환되었습니다. 투입구를 확인해 주십시오.\n"));

	/********************	 Database	 ********************/
	function = "Database_addHistory";
	translation_en.insert(pair<string, string>(function + "0", "Total session number is "));
	translation_kr.insert(pair<string, string>(function + "0", "현재 세션 번호 : "));

	translation_en.insert(pair<string, string>(function + "1", "Transaction order is : "));
	translation_kr.insert(pair<string, string>(function + "1", "통합 거래 순서 : "));

	function = "Database_printHistory";
	translation_en.insert(pair<string, string>(function + "0.1", "[Order]"));
	translation_kr.insert(pair<string, string>(function + "0.1", "[순서]"));
	translation_en.insert(pair<string, string>(function + "0.2", "[Account holder]"));
	translation_kr.insert(pair<string, string>(function + "0.2", "[계좌주]"));
	translation_en.insert(pair<string, string>(function + "0.3", "[Account number]"));
	translation_kr.insert(pair<string, string>(function + "0.3", "[계좌번호]"));
	translation_en.insert(pair<string, string>(function + "0.4", "[Transcation type]"));
	translation_kr.insert(pair<string, string>(function + "0.4", "[거래 타입]"));
	translation_en.insert(pair<string, string>(function + "0.5", "[Balance before the transaction]"));
	translation_kr.insert(pair<string, string>(function + "0.5", "[거래 전 잔액]"));
	translation_en.insert(pair<string, string>(function + "0.6", "[Balance after the transaction]"));
	translation_kr.insert(pair<string, string>(function + "0.6", "[거래 후 잔액]"));
	translation_en.insert(pair<string, string>(function + "0.7", "[Recipient when transfer]"));
	translation_kr.insert(pair<string, string>(function + "0.7", "[송금 시 수신인]"));

	function = "Database_addSessionHistory";
	translation_en.insert(pair<string, string>(function + "0", "Transaction account"));
	translation_kr.insert(pair<string, string>(function + "0", "거래 계좌 : "));

	function = "Database_printSessionHistory";
	translation_en.insert(pair<string, string>(function + "0.1", "[Account holder]"));
	translation_kr.insert(pair<string, string>(function + "0.1", "[계좌주]"));
	translation_en.insert(pair<string, string>(function + "0.2", "[Account number]"));
	translation_kr.insert(pair<string, string>(function + "0.2", "[계좌번호]"));
	translation_en.insert(pair<string, string>(function + "0.3", "[Transation type]"));
	translation_kr.insert(pair<string, string>(function + "0.3", "[거래 타입]"));
	translation_en.insert(pair<string, string>(function + "0.4", "[Balance before the transaction]"));
	translation_kr.insert(pair<string, string>(function + "0.4", "[거래 전 잔액]"));
	translation_en.insert(pair<string, string>(function + "0.5", "[Balance after the transaction]"));
	translation_kr.insert(pair<string, string>(function + "0.5", "[거래 후 잔액]"));
	translation_en.insert(pair<string, string>(function + "0.6", "[Recipient when transfer]"));
	translation_kr.insert(pair<string, string>(function + "0.6", "[송금 시 수신인]"));

	/********************	 ATM	 ********************/
	function = "ATM_deposit";
	translation_en.insert(pair<string, string>(function + "0", " won has been deposited.\n"));
	translation_kr.insert(pair<string, string>(function + "0", "원이 입금되었습니다.\n"));

	translation_en.insert(pair<string, string>(function + "1", " won has been deposited.\n"));
	translation_kr.insert(pair<string, string>(function + "1", "원이 입금되었습니다.\n"));

	translation_en.insert(pair<string, string>(function + "2.1", "The fee : "));
	translation_kr.insert(pair<string, string>(function + "2.1", "수수료 : "));
	translation_en.insert(pair<string, string>(function + "2.2", " won\n"));
	translation_kr.insert(pair<string, string>(function + "2.2", "원\n"));

	translation_en.insert(pair<string, string>(function + "3.1", "Balance : "));
	translation_kr.insert(pair<string, string>(function + "3.1", "잔액 : "));
	translation_en.insert(pair<string, string>(function + "3.2", " won\n"));
	translation_kr.insert(pair<string, string>(function + "3.2", "원\n"));

	function = "ATM_withdrawal";
	translation_en.insert(pair<string, string>(function + "0", " won has been withdrawn. Please make sure to take your cash.\n"));
	translation_kr.insert(pair<string, string>(function + "0", "원이 출금되었습니다. 투입구를 확인해주십시오.\n"));

	translation_en.insert(pair<string, string>(function + "1.1", "The fee : "));
	translation_kr.insert(pair<string, string>(function + "1.1", "수수료 : "));
	translation_en.insert(pair<string, string>(function + "1.2", " won\n"));
	translation_kr.insert(pair<string, string>(function + "1.2", "원\n"));

	translation_en.insert(pair<string, string>(function + "2.1", "Balance : "));
	translation_kr.insert(pair<string, string>(function + "2.1", "잔액 : "));
	translation_en.insert(pair<string, string>(function + "2.2", " won\n"));
	translation_kr.insert(pair<string, string>(function + "2.2", "원\n"));

	function = "ATM_transfer";
	translation_en.insert(pair<string, string>(function + "0.1", "Debug: ATM::transfer called\nDebug: (송금 전)\nfrom account ["));
	translation_kr.insert(pair<string, string>(function + "0.1", "Debug: ATM::transfer called\nDebug: (송금 전)\nfrom account ["));
	translation_en.insert(pair<string, string>(function + "0.2", "]\t 현재 잔액: ["));
	translation_kr.insert(pair<string, string>(function + "0.2", "]\t 현재 잔액: ["));
	translation_en.insert(pair<string, string>(function + "0.3", "]원\nto account ["));
	translation_kr.insert(pair<string, string>(function + "0.3", "]원\nto account ["));
	translation_en.insert(pair<string, string>(function + "0.4", "]\t 현재 잔액: ["));
	translation_kr.insert(pair<string, string>(function + "0.4", "]\t 현재 잔액: ["));
	translation_en.insert(pair<string, string>(function + "0.5", "]원\n"));
	translation_kr.insert(pair<string, string>(function + "0.5", "]원\n"));

	translation_en.insert(pair<string, string>(function + "1.1", "\t"));
	translation_kr.insert(pair<string, string>(function + "1.1", "\t"));
	translation_en.insert(pair<string, string>(function + "1.2", " won has been transferred to ["));
	translation_kr.insert(pair<string, string>(function + "1.2", "원이 ["));
	translation_en.insert(pair<string, string>(function + "1.3", "]\n"));
	translation_kr.insert(pair<string, string>(function + "1.3", "] 님에게 송금 완료되었습니다.\n"));

	translation_en.insert(pair<string, string>(function + "2.1", "Debug: (송금 후)\nfrom account ["));
	translation_kr.insert(pair<string, string>(function + "2.1", "Debug: (송금 후)\nfrom account ["));
	translation_en.insert(pair<string, string>(function + "2.2", "]\t 현재 잔액: ["));
	translation_kr.insert(pair<string, string>(function + "2.2", "]\t 현재 잔액: ["));
	translation_en.insert(pair<string, string>(function + "2.3", "]원\nto account ["));
	translation_kr.insert(pair<string, string>(function + "2.3", "]원\nto account ["));
	translation_en.insert(pair<string, string>(function + "2.4", "]\t 현재 잔액: ["));
	translation_kr.insert(pair<string, string>(function + "2.4", "]\t 현재 잔액: ["));
	translation_en.insert(pair<string, string>(function + "2.5", "]원\n"));
	translation_kr.insert(pair<string, string>(function + "2.5", "]원\n"));

	translation_en.insert(pair<string, string>(function + "3", "Debug: 잔액 부족\n"));
	translation_kr.insert(pair<string, string>(function + "3", "Debug: 잔액 부족\n"));
	/*
	translation_en.insert(pair<string, string>(function + "4.1", "\t"));
	translation_kr.insert(pair<string, string>(function + "4.1", "\t"));
	translation_en.insert(pair<string, string>(function + "4.2", " won has been transferred to ["));
	translation_kr.insert(pair<string, string>(function + "4.2", "원이 ["));
	translation_en.insert(pair<string, string>(function + "4.3", "]\n"));
	translation_kr.insert(pair<string, string>(function + "4.3", "] 님에게 송금 완료되었습니다.\n"));

	translation_en.insert(pair<string, string>(function + "5.1", "Debug: (송금 후)\nfrom account ["));
	translation_kr.insert(pair<string, string>(function + "5.1", "Debug: (송금 후)\nfrom account ["));
	translation_en.insert(pair<string, string>(function + "5.2", "]\t 현재 잔액: ["));
	translation_kr.insert(pair<string, string>(function + "5.2", "]\t 현재 잔액: ["));
	translation_en.insert(pair<string, string>(function + "5.3", "]원\nto account ["));
	translation_kr.insert(pair<string, string>(function + "5.3", "]원\nto account ["));
	translation_en.insert(pair<string, string>(function + "5.4", "]\t 현재 잔액: ["));
	translation_kr.insert(pair<string, string>(function + "5.4", "]\t 현재 잔액: ["));
	translation_en.insert(pair<string, string>(function + "5.5", "]원\n"));
	translation_kr.insert(pair<string, string>(function + "5.5", "]원\n"));
	*/
	translation_en.insert(pair<string, string>(function + "6", "Debug: 잔액 부족\n"));
	translation_kr.insert(pair<string, string>(function + "6", "Debug: 잔액 부족\n"));

	function = "ATM_fee";
	translation_en.insert(pair<string, string>(function + "0", "Debug: Wrong transactionType in int ATM::fee(int, Bank*, Bank*)\n"));
	translation_kr.insert(pair<string, string>(function + "0", "Debug: Wrong transactionType in int ATM::fee(int, Bank*, Bank*)\n"));

	function = "Bill_printBill";
	translation_en.insert(pair<string, string>(function + "0.1", "Amount : "));
	translation_kr.insert(pair<string, string>(function + "0.1", "금액 : "));
	translation_en.insert(pair<string, string>(function + "0.2", " won : "));
	translation_kr.insert(pair<string, string>(function + "0.2", "원 : "));
	translation_en.insert(pair<string, string>(function + "0.3", " bill(s) "));
	translation_kr.insert(pair<string, string>(function + "0.3", "장 "));
	translation_en.insert(pair<string, string>(function + "0.4", "Total amount : "));
	translation_kr.insert(pair<string, string>(function + "0.4", "총 액수 : "));
	translation_en.insert(pair<string, string>(function + "0.5", " won\n"));
	translation_kr.insert(pair<string, string>(function + "0.5", "원\n"));

}
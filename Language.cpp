#include "Language.h"

Translation::Translation() {
	/********************	 UI	 ********************/
	/********************	  commons	 ********************/

	translation_en.insert(pair<string, string>("card returned", "Your card has been returned. Please take your card.\n"));
	translation_kr.insert(pair<string, string>("card returned", "카드가 반환되었습니다. 투입구를 확인해 주십시오.\n"));

	translation_en.insert(pair<string, string>("common exit", "The session has been ended. Thank you.\n"));
	translation_kr.insert(pair<string, string>("common exit", "거래가 종료되었습니다. 안녕히 가십시오.\n"));

	translation_en.insert(pair<string, string>("exit deposit", "You have exited [deposit] session.\n"));
	translation_kr.insert(pair<string, string>("exit deposit", "입금을 취소하셨습니다.\n"));

	translation_en.insert(pair<string, string>("exit withdraw", "You have exited [withdrawal] session.\n"));
	translation_kr.insert(pair<string, string>("exit withdraw", "출금을 취소하셨습니다.\n"));

	translation_en.insert(pair<string, string>("exit transfer", "You have exited [transfer] session.\n"));
	translation_kr.insert(pair<string, string>("exit transfer", "송금을 취소하셨습니다.\n"));

	translation_en.insert(pair<string, string>("put cash", "\tPlease put your cash in the cash/check slot. (Input in the order of 50,000 won, 10,000 won, 5,000 won, and 1,000 won bills.)\n\t(Cancel : -1)\n"));
	translation_kr.insert(pair<string, string>("put cash", "\t투입구에 현금을 넣어 주십시오. (5만원권, 1만원권, 5천원권, 1천원권 개수 순으로 입력해 주십시오.)\n\t(취소 : -1)\n"));

	translation_en.insert(pair<string, string>("cash returned", "Your cash has been returned. Please take your cash.\n"));
	translation_kr.insert(pair<string, string>("cash returned", "투입하신 현금이 반환되었습니다. 투입구를 확인해 주십시오.\n"));

	translation_en.insert(pair<string, string>("check returned", "Your check has been returned. Please take your check.\n"));
	translation_kr.insert(pair<string, string>("check returned", "투입하신 수표가 반환되었습니다. 투입구를 확인해 주십시오.\n"));

	translation_en.insert(pair<string, string>("excess cash", "You could only put 50 or less number of paper cash at a time. Please try again.\n")); // The maximum number of available bills has been exceeded. 
	translation_kr.insert(pair<string, string>("excess cash", "최대 입금 가능 장 수를 초과하였습니다. 다시 시도해 주십시오.\n"));

	translation_en.insert(pair<string, string>("no cash", "There is no cash in the cash/check slot. Please try again.\n"));
	translation_kr.insert(pair<string, string>("no cash", "투입구에 현금이 들어있지 않습니다. 다시 시도해 주십시오.\n"));

	translation_en.insert(pair<string, string>("not enough balance", "There is not enough balance in your account.\n")); // 아직 적용중
	translation_kr.insert(pair<string, string>("not enough balance", "계좌에 잔액이 부족합니다.\n"));

	translation_en.insert(pair<string, string>("confirm amount", "\tPlease make sure if the amount you put in is correct.\n\t(Confirm : 0\tCancel : -1)\n"));
	translation_kr.insert(pair<string, string>("confirm amount", "\t투입하신 금액이 맞는지 확인해 주십시오.\n\t(확인 : 0\t취소 : -1)\n"));

	translation_en.insert(pair<string, string>("show balance1", "Your current balance : ["));
	translation_kr.insert(pair<string, string>("show balance1", "현재 잔액 : ["));
	translation_en.insert(pair<string, string>("show balance2", "] won\n"));
	translation_kr.insert(pair<string, string>("show balance2", "]원\n"));

	translation_en.insert(pair<string, string>("confirm", "\n\t(Confirm : 0\tCancel : -1)\n"));
	translation_kr.insert(pair<string, string>("confirm", "\n\t(확인 : 0\t취소: -1)\n"));

	translation_en.insert(pair<string, string>("cancel", "\n\t(Cancel : -1)\n"));
	translation_kr.insert(pair<string, string>("cancel", "\n\t(취소 : -1)\n"));

	translation_en.insert(pair<string, string>("unexpected", "Debug: Unexpected behavior\n"));
	translation_kr.insert(pair<string, string>("unexpected", "Debug: Unexpected behavior\n"));

	/********************	 state functions	 ********************/
	string function = "UI_changeLanguage";
	translation_en.insert(pair<string, string>(function + "0", "The language has been changed to English.\n"));
	translation_kr.insert(pair<string, string>(function + "0", "언어가 한국어로 변경되었습니다.\n"));

	translation_en.insert(pair<string, string>(function + "1", "The language change has been canceled.\n")); // 문장이상할지도?
	translation_kr.insert(pair<string, string>(function + "1", "언어 변경이 취소되었습니다.\n"));

	function = "UI_insertCard";
	translation_en.insert(pair<string, string>(function + "0", "\tPlease insert your debit card. (Enter the account number.)"));
	translation_kr.insert(pair<string, string>(function + "0", "\t카드를 삽입해 주십시오. (계좌 번호를 입력해 주십시오.)"));

	translation_en.insert(pair<string, string>(function + "2", "Transaction has been canceled.\n"));
	translation_kr.insert(pair<string, string>(function + "2", "거래가 취소되었습니다.\n"));

	translation_en.insert(pair<string, string>(function + "3", "This account does not exist.\n"));
	translation_kr.insert(pair<string, string>(function + "3", "존재하지 않는 계좌입니다.\n"));

	translation_en.insert(pair<string, string>(function + "4", "This card is not supported by this ATM.\n"));
	translation_kr.insert(pair<string, string>(function + "4", "본 ATM에서 지원하지 않는 은행의 계좌입니다.\n"));

	function = "UI_verifyAdmin";
	translation_en.insert(pair<string, string>(function + "0", "You have inserted the admin card.\n"));
	translation_kr.insert(pair<string, string>(function + "0", "관리자 카드가 삽입되었습니다.\n"));

	translation_en.insert(pair<string, string>(function + "1", "\tEnter the password to access the admin panel."));
	translation_kr.insert(pair<string, string>(function + "1", "\t관리자 패널에 접속하시려면 비밀번호를 입력해 주십시오."));

	translation_en.insert(pair<string, string>(function + "2", "You have entered wrong password.\n"));
	translation_kr.insert(pair<string, string>(function + "2", "비밀번호가 틀렸습니다.\n"));

	translation_en.insert(pair<string, string>(function + "3", "\tDo you want to show ATM history?\n\t(Confirm : 0\tCancel : -1)\n"));
	translation_kr.insert(pair<string, string>(function + "3", "\tATM 거래 내역을 보시겠습니까?\n\t(확인 : 0\t취소 : -1)\n"));

	translation_en.insert(pair<string, string>(function + "4", "You have exited the admin panel session.\n"));
	translation_kr.insert(pair<string, string>(function + "4", "관리자 패널에서 접속 종료하셨습니다.\n"));

	function = "UI_checkAccount";
	translation_en.insert(pair<string, string>(function + "0.1", "\tYour account number is : "));
	translation_kr.insert(pair<string, string>(function + "0.1", "\t계좌번호 : "));
	translation_en.insert(pair<string, string>(function + "0.2", "\n\tIs this correct?"));
	translation_kr.insert(pair<string, string>(function + "0.2", " 가 맞습니까?"));

	function = "UI_verifyAccount";
	translation_en.insert(pair<string, string>(function + "0", "\tPlease enter the password."));
	translation_kr.insert(pair<string, string>(function + "0", "\t비밀번호를 입력해 주십시오."));

	translation_en.insert(pair<string, string>(function + "1.0", "Wrong password. Please try again. (You have left "));
	translation_kr.insert(pair<string, string>(function + "1.0", "비밀번호가 틀렸습니다. 다시 시도해 주십시오. (남은 횟수 :"));

	translation_en.insert(pair<string, string>(function + "1.1", " attempt(s).)\n"));
	translation_kr.insert(pair<string, string>(function + "1.1", " 회)\n"));

	translation_en.insert(pair<string, string>(function + "2", "You have made three wrong attempts.\n"));
	translation_kr.insert(pair<string, string>(function + "2", "비밀번호를 3회 틀리셨습니다.\n"));

	translation_en.insert(pair<string, string>(function + "3.1", "You have accessed to : [")); // user 이름 이어짐
	translation_kr.insert(pair<string, string>(function + "3.1", "["));
	translation_en.insert(pair<string, string>(function + "3.2", "]'s [")); // bank 이름 이어짐
	translation_kr.insert(pair<string, string>(function + "3.2", "] 님의 ["));
	translation_en.insert(pair<string, string>(function + "3.2.0", "] account ["));
	translation_kr.insert(pair<string, string>(function + "3.2.0", "] 계좌 ["));
	translation_en.insert(pair<string, string>(function + "3.3", "]\n"));
	translation_kr.insert(pair<string, string>(function + "3.3", "]에 접속하였습니다.\n"));

	function = "UI_enterAdmin";
	translation_en.insert(pair<string, string>(function + "0", "You have accessed to the admin panel.\n"));
	translation_kr.insert(pair<string, string>(function + "0", "관리자 클래스로 진입합니다.\n"));

	function = "UI_chooseTransaction";
	translation_en.insert(pair<string, string>(function + "0", "\tWhat would you like to do?"));
	translation_kr.insert(pair<string, string>(function + "0", "\t무엇을 하시겠습니까?"));

	translation_en.insert(pair<string, string>(function + "0.1", "\t1. Deposit\t2. Withdraw\t3. Transfer\n"));
	translation_kr.insert(pair<string, string>(function + "0.1", "\t1. 입금\t2. 출금\t3. 송금\n"));

	translation_en.insert(pair<string, string>(function + "2", "Wrong input. Please try again.\n"));
	translation_kr.insert(pair<string, string>(function + "2", "잘못된 입력입니다. 다시 선택해 주십시오.\n"));

	/********************	 Admin	 ********************/
	function = "UI_admin";
	translation_en.insert(pair<string, string>(function + "1", "The file has been saved as \"history.csv\"."));
	translation_kr.insert(pair<string, string>(function + "1", "파일이 history.csv로 저장되었습니다."));

	/********************	 Deposit	 ********************/
	function = "UI_deposit";
	translation_en.insert(pair<string, string>(function + "0", "You have chosen [Deposit].\n"));
	translation_kr.insert(pair<string, string>(function + "0", "[입금]을 선택하셨습니다.\n"));

	function = "UI_d_askDepositType";
	translation_en.insert(pair<string, string>(function + "0", "\tPlease choose how to deposit money among cash and checks."));
	translation_kr.insert(pair<string, string>(function + "0", "\t현금, 수표 중 입금하실 방법을 선택해 주십시오."));

	translation_en.insert(pair<string, string>(function + "0.1", "\t1. cash\t2. check\n"));
	translation_kr.insert(pair<string, string>(function + "0.1", "\t1. 현금\t2. 수표\n"));

	translation_en.insert(pair<string, string>(function + "2", "You have chosen [cash deposit].\n"));
	translation_kr.insert(pair<string, string>(function + "2", "[현금 입금]을 선택하셨습니다.\n"));

	translation_en.insert(pair<string, string>(function + "3", "You have chosen [check deposit].\n"));
	translation_kr.insert(pair<string, string>(function + "3", "[수표 입금]을 선택하셨습니다.\n"));

	function = "UI_d_askAmount_Cash";
	translation_en.insert(pair<string, string>(function + "0.1", "Deposit fee would be ["));
	translation_kr.insert(pair<string, string>(function + "0.1", "수수료는 ["));
	translation_en.insert(pair<string, string>(function + "0.2", "] won.\n"));
	translation_kr.insert(pair<string, string>(function + "0.2", "]원입니다.\n"));

	translation_en.insert(pair<string, string>(function + "1", "\tPlease put your cash in the cash/check slot. (Input in the order of 50,000 won, 10,000 won, 5,000 won, and 1,000 won bills.)\n\t(Up to 50 amounts of cash can be deposited per time.)\n\t(Cancel : -1)\n"));
	translation_kr.insert(pair<string, string>(function + "1", "\t투입구에 현금을 넣어 주십시오. (5만원권, 1만원권, 5천원권, 1천원권 개수 순으로 입력해 주십시오.)\n\t(1회당 최대 50장의 지폐를 입금하실 수 있습니다.)\n\t(취소 : -1)\n"));

	function = "UI_d_askAmount_Check";
	translation_en.insert(pair<string, string>(function + "0.1", "Deposit fee would be ["));
	translation_kr.insert(pair<string, string>(function + "0.1", "수수료는 ["));
	translation_en.insert(pair<string, string>(function + "0.2", "] won.\n"));
	translation_kr.insert(pair<string, string>(function + "0.2", "]원입니다.\n"));

	translation_en.insert(pair<string, string>(function + "1", "\tPlease enter the number of checks you want to put in. Up to 30 checks can be deposited per time. "));
	translation_kr.insert(pair<string, string>(function + "1", "\t투입하실 수표의 장 수를 입력해 주십시오. 1회당 최대 30장의 수표를 입금하실 수 있습니다. "));

	translation_en.insert(pair<string, string>(function + "3", "There is no check in the cash/check slot. Please try again.\n"));
	translation_kr.insert(pair<string, string>(function + "3", "투입구에 수표가 들어있지 않습니다. 다시 시도해 주십시오.\n"));

	translation_en.insert(pair<string, string>(function + "4", "The maximum number of available checks has been exceeded. Please try again.\n"));
	translation_kr.insert(pair<string, string>(function + "4", "최대 입금 가능 장 수를 초과하였습니다. 다시 시도해 주십시오.\n"));

	translation_en.insert(pair<string, string>(function + "5", "\tPlease enter the amount of each check."));
	translation_kr.insert(pair<string, string>(function + "5", "\t각 수표의 액수를 입력해 주십시오."));

	function = "UI_d_confirm_Cash";

	function = "UI_d_confirm_Check";
	translation_en.insert(pair<string, string>(function + "0.2", "] won "));
	translation_kr.insert(pair<string, string>(function + "0.2", "]원 "));
	translation_en.insert(pair<string, string>(function + "0.3", "Total amount : ["));
	translation_kr.insert(pair<string, string>(function + "0.3", "총 액수 : ["));
	translation_en.insert(pair<string, string>(function + "0.4", "] won\n"));
	translation_kr.insert(pair<string, string>(function + "0.4", "]원\n"));

	function = "UI_d_confirmTotal";

	translation_en.insert(pair<string, string>(function + "1.1", "\tWould you like to deposit ["));
	translation_kr.insert(pair<string, string>(function + "1.1", "\t계좌로 ["));
	translation_en.insert(pair<string, string>(function + "1.2", "] won into your account?\n\tDeposit fee would be ["));
	translation_kr.insert(pair<string, string>(function + "1.2", "]원 입금하시겠습니까? 수수료는 ["));
	translation_en.insert(pair<string, string>(function + "1.3", "] won.\n\tThe fee will be automatically deducted from ["));
	translation_kr.insert(pair<string, string>(function + "1.3", "]원입니다.\n\t수수료는 현재 입금하실 금액 ["));
	translation_en.insert(pair<string, string>(function + "1.4", "] won."));
	translation_kr.insert(pair<string, string>(function + "1.4", "]원에서 자동 차감됩니다."));

	function = "UI_d_deposit";

	translation_en.insert(pair<string, string>(function + "1", "] won has been successfully deposited.\n"));
	translation_kr.insert(pair<string, string>(function + "1", "]원이 입금되었습니다.\n"));

	/********************	 Withdrawal	 ********************/
	function = "UI_withdrawal";
	translation_en.insert(pair<string, string>(function + "0", "You can only withdraw 3 times in one session.\n"));
	translation_kr.insert(pair<string, string>(function + "0", "해당 세션의 출금 한도(3회)를 초과하였습니다.\n"));

	translation_en.insert(pair<string, string>(function + "1", "You have chosen [Withdrawal].\n"));
	translation_kr.insert(pair<string, string>(function + "1", "[출금]을 선택하셨습니다.\n"));

	function = "UI_w_askAmount";
	translation_en.insert(pair<string, string>(function + "0.1", "Withdrawal fee would be ["));
	translation_kr.insert(pair<string, string>(function + "0.1", "수수료는 ["));
	translation_en.insert(pair<string, string>(function + "0.2", "] won.\n"));
	translation_kr.insert(pair<string, string>(function + "0.2", "]원입니다.\n"));

	translation_en.insert(pair<string, string>(function + "1", "\tPlease enter the amount you want to withdraw. You can withdraw 500 thousand won or less at a time. (Unit : 10000 won)"));
	translation_kr.insert(pair<string, string>(function + "1", "\t출금하실 금액을 입력해 주십시오. 1회 출금한도는 50만 원입니다. (단위 : 만 원)"));

	function = "UI_w_checkAccountBalance";
	translation_en.insert(pair<string, string>(function + "0", "There is not enough balance in the account. Please try again.\n"));
	translation_kr.insert(pair<string, string>(function + "0", "계좌에 잔액이 부족합니다. 다시 시도해 주십시오.\n"));

	function = "UI_w_checkMaxAmount";
	translation_en.insert(pair<string, string>(function + "0", "It exceeded the maximum withdrawal amount (500,000 won) per time. Please try again.\n"));
	translation_kr.insert(pair<string, string>(function + "0", "1회 최대 출금 금액(50만원)을 초과하였습니다. 다시 시도해 주십시오.\n"));

	function = "UI_w_checkATMBalance";
	translation_en.insert(pair<string, string>(function + "0", "Not enough cash in this ATM machine.\n"));
	translation_kr.insert(pair<string, string>(function + "0", "ATM 기 내부에 현금이 부족합니다.\n"));

	function = "UI_w_confirm";
	translation_en.insert(pair<string, string>(function + "0.1", "\tWould you like to withdraw ["));
	translation_kr.insert(pair<string, string>(function + "0.1", "\t계좌에서 ["));
	translation_en.insert(pair<string, string>(function + "0.2", "] won from your account?\nThe fee is ["));
	translation_kr.insert(pair<string, string>(function + "0.2", "]원 출금하시겠습니까? 수수료는 ["));
	translation_en.insert(pair<string, string>(function + "0.3", "] won.\n\tThe fee will be automatically deducted from the current account balance of [")); // deducted??
	translation_kr.insert(pair<string, string>(function + "0.3", "]원입니다.\n\t수수료는 현재 계좌 잔액 ["));
	translation_en.insert(pair<string, string>(function + "0.4", "] won."));
	translation_kr.insert(pair<string, string>(function + "0.4", "]원에서 자동 차감됩니다."));

	function = "UI_w_withdrawal";

	translation_en.insert(pair<string, string>(function + "1", "] won has been successfully withdrawn. Please make sure to take your cash.\n"));
	translation_kr.insert(pair<string, string>(function + "1", "]원이 출금되었습니다. 투입구를 확인해주십시오.\n"));

	/********************	 Transfer	 ********************/
	function = "UI_transfer";
	translation_en.insert(pair<string, string>(function + "0", "You have chosen [Transfer].\n"));
	translation_kr.insert(pair<string, string>(function + "0", "[송금]을 선택하셨습니다.\n"));

	function = "UI_t_askTransferType";
	translation_en.insert(pair<string, string>(function + "0", "\tWhich transfer option would you like?"));
	translation_kr.insert(pair<string, string>(function + "0", "\t원하시는 송금 옵션을 선택해 주십시오."));
	translation_en.insert(pair<string, string>(function + "0.1", "\t1. Cash transfer\t2. Account transfer\n"));
	translation_kr.insert(pair<string, string>(function + "0.1", "\t1. 현금 송금\t2. 계좌 송금\n"));

	translation_en.insert(pair<string, string>(function + "2", "You have chosen [cash transfer].\n"));
	translation_kr.insert(pair<string, string>(function + "2", "[현금 송금]을 선택하셨습니다.\n"));

	translation_en.insert(pair<string, string>(function + "3", "You have chosen [account transfer].\n"));
	translation_kr.insert(pair<string, string>(function + "3", "[계좌 송금]을 선택하셨습니다.\n"));

	function = "UI_t_askToAcc";
	translation_en.insert(pair<string, string>(function + "0", "\tPlease enter the account you would like to transfer your money to."));
	translation_kr.insert(pair<string, string>(function + "0", "\t송금하실 계좌의 계좌번호를 입력해 주십시오."));

	translation_en.insert(pair<string, string>(function + "1", "You cannot transfer to the same account.\n"));
	translation_kr.insert(pair<string, string>(function + "1", "현재 계좌와 동일한 계좌로 송금할 수 없습니다.\n"));

	function = "UI_t_confirmToAcc";
	translation_en.insert(pair<string, string>(function + "0.1", "\tIs this correct? : [")); // user 이름 이어짐
	translation_kr.insert(pair<string, string>(function + "0.1", "\t["));
	translation_en.insert(pair<string, string>(function + "0.2", "]'s [")); // bank 이름 이어짐
	translation_kr.insert(pair<string, string>(function + "0.2", "] 님의 ["));
	translation_en.insert(pair<string, string>(function + "0.2.0", "] account ["));
	translation_kr.insert(pair<string, string>(function + "0.2.0", "] 계좌 ["));
	translation_en.insert(pair<string, string>(function + "0.3", "]"));
	translation_kr.insert(pair<string, string>(function + "0.3", "]가 맞습니까?"));
	translation_en.insert(pair<string, string>(function + "0.4", "\t0. Yes  \t1. No (Try different account)\n"));
	translation_kr.insert(pair<string, string>(function + "0.4", "\t0. 예\t1. 아니오(다시 입력)\n"));

	function = "UI_t_askAmount_c";
	translation_en.insert(pair<string, string>(function + "0.1", "Transfer fee would be ["));
	translation_kr.insert(pair<string, string>(function + "0.1", "수수료는 ["));
	translation_en.insert(pair<string, string>(function + "0.2", "] won.\n"));
	translation_kr.insert(pair<string, string>(function + "0.2", "]원입니다.\n"));

	function = "UI_t_askAmount_a";
	translation_en.insert(pair<string, string>(function + "0.1", "Transfer fee would be ["));
	translation_kr.insert(pair<string, string>(function + "0.1", "수수료는 ["));
	translation_en.insert(pair<string, string>(function + "0.2", "] won.\n"));
	translation_kr.insert(pair<string, string>(function + "0.2", "]원입니다.\n"));

	translation_en.insert(pair<string, string>(function + "1.1", "\tPlease enter the amount of money you would like to transfer.\n\tYou can transfer 2 million won or less at a time. (Your current balance : "));
	translation_kr.insert(pair<string, string>(function + "1.1", "\t송금하실 금액을 입력해 주십시오. 1회 송금한도는 200만 원입니다. (계좌 잔액 : "));
	translation_en.insert(pair<string, string>(function + "1.2", ")"));
	translation_kr.insert(pair<string, string>(function + "1.2", ")"));

	translation_en.insert(pair<string, string>(function + "2.1", "\tIs ["));
	translation_kr.insert(pair<string, string>(function + "2.1", "\t["));
	translation_en.insert(pair<string, string>(function + "2.2", "] won correct?"));
	translation_kr.insert(pair<string, string>(function + "2.2", "]원이 맞습니까?"));

	function = "UI_t_confirm";
	translation_en.insert(pair<string, string>(function + "0.1", "\tWould you like to transfer ["));
	translation_en.insert(pair<string, string>(function + "0.2", "] won to ["));
	translation_en.insert(pair<string, string>(function + "0.3", "]? Transfer fee would be ["));
	translation_en.insert(pair<string, string>(function + "0.4", "] won.\n\tThe fee will be automatically deducted from the current account balance of [")); // deducted??
	translation_en.insert(pair<string, string>(function + "0.5", "] won."));
	translation_kr.insert(pair<string, string>(function + "0.1", "\t["));
	translation_kr.insert(pair<string, string>(function + "0.2", "] 님에게 ["));
	translation_kr.insert(pair<string, string>(function + "0.3", "]원 송금하시겠습니까? 수수료는 ["));
	translation_kr.insert(pair<string, string>(function + "0.4", "]원입니다.\n\t수수료는 현재 계좌 잔액 ["));
	translation_kr.insert(pair<string, string>(function + "0.5", "]원에서 자동 차감됩니다."));

	function = "UI_t_transfer";
	
	translation_en.insert(pair<string, string>(function + "1.1", "] won has been successfully transferred to ["));
	translation_kr.insert(pair<string, string>(function + "1.1", "]원이 ["));
	translation_en.insert(pair<string, string>(function + "1.2", "]\n"));
	translation_kr.insert(pair<string, string>(function + "1.2", "] 님에게 송금 완료되었습니다.\n"));

	/********************	 Database	 ********************/
	function = "Database_addHistory";

	translation_en.insert(pair<string, string>(function + "0", "Total session number is "));
	translation_kr.insert(pair<string, string>(function + "0", "현재 세션 번호 : "));

	translation_en.insert(pair<string, string>(function + "1", "Transaction order is : "));
	translation_kr.insert(pair<string, string>(function + "1", "통합 거래 순서 : "));

	function = "Database_printHistory";
	translation_en.insert(pair<string, string>(function + "1", "There is no transaction history."));
	translation_kr.insert(pair<string, string>(function + "1", "거래 내역이 없습니다.\n"));
	
	translation_en.insert(pair<string, string>(function + "0.8", "[Transferred amount]"));
	translation_kr.insert(pair<string, string>(function + "0.8", "[송금액]"));
	
	function = "Database_printSessionHistory";

	translation_en.insert(pair<string, string>(function + "0.1", "[Acc. holder]"));
	translation_kr.insert(pair<string, string>(function + "0.1", "[계좌주]"));
	translation_en.insert(pair<string, string>(function + "0.2", "[Acc. No.]"));
	translation_kr.insert(pair<string, string>(function + "0.2", "[계좌번호]"));
	translation_en.insert(pair<string, string>(function + "0.3", "[Transation]"));
	translation_kr.insert(pair<string, string>(function + "0.3", "[거래 타입]"));
	translation_en.insert(pair<string, string>(function + "0.4", "[Balance (before)]"));
	translation_kr.insert(pair<string, string>(function + "0.4", "[거래 전 잔액]"));
	translation_en.insert(pair<string, string>(function + "0.5", "[Balance (changed)]"));
	translation_kr.insert(pair<string, string>(function + "0.5", "[거래 후 잔액]"));
	translation_en.insert(pair<string, string>(function + "0.6", "[Recipient]"));
	translation_kr.insert(pair<string, string>(function + "0.6", "[송금 시 수신인]"));
}
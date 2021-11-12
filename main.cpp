#include "Classes.cpp"
#include <iostream>
#include <string>
/*
0: 프로그램 종료시 0으로 종료
1: 세션 진행중.  admin이냐 아니면 개인거래할거냐 선택
2: admin메뉴
3: 계좌번호 입력 및 본인확인
4: 거래 종류 선택: 입 출 송금
5: 입금
6: 출금
7: 송금
8. 안녕 디지몬
*/

using namespace std;

int main() {

	int UserStatus = 1; // 세션 시작

	Database* database = Database::getInstance();

	Bank* uriBank = new Bank(); // new로 할당한것들 main 끝에 delete해준다
	Bank* kakaoBank = new Bank("kakao");

	User* U1 = new User("U1", "최가난");
	User* U2 = new User("U2", "권부자");
	User* U3 = new User("U3", "서모녀");
	User* U4 = new User("U4", "김백규");
	User* U5 = new User("U5", "버터");

	ATM* A1 = new ATM(uriBank, "admin", 1357, 100000000, 100, true); // 0; 현금잔액 100000000으로 시작
	ATM* A2 = new ATM(kakaoBank, "master", 2345, 2000000, 0, false); // 1

	Account* AC1 = new Account(uriBank, U1, 2345, 10000); // 계좌번호 0
	database->addAccountList(AC1);
	Account* AC2 = new Account(uriBank, U2, 3344, 3000000); // 계좌번호 1
	database->addAccountList(AC2);
	Account* AC3 = new Account(kakaoBank, U3, 22, 450000); // 계좌번호 2
	database->addAccountList(AC3);
	Account* AC4 = new Account(kakaoBank, U1, 1024, 50000); // 계좌번호 3
	database->addAccountList(AC4);

	cout << database->getAccountByNum(2)->getBalance() << endl; // 현재 존재하는 계좌번호 이외 입력하면 버그남
	
	int userIndex = -1;
	while (UserStatus != 0) {
		if (UserStatus == 1) {
			// [의논필요] input을 int 말고 string으로 받아야할까? type error가 안 나도록?
			// [의논필요] instructor에 atm이 2중언어 지원하는 atm 지원안하는 atm 만들라고 했는데 그럼 atm 선택 단계도 넣어줘야할까?
			cout << "메뉴를 선택하세요.\n\t1. admin panal 보기\t2. 개인거래하기\t3. exit" << endl;
			int UserInput;
			// admin panal 보기 or 개인거래하기 선택
			cin >> UserInput;
			if (UserInput == 1) { UserStatus = 2; }
			else if (UserInput == 2) { UserStatus = 3; }
			else if (UserInput == 3) { UserStatus = 0; }
			else { cout << "Error" << endl; } // 에러 처리 부분 추가해야함
		}
		if (UserStatus == 2) { // admin panal
			cout << "admin panal" << endl;
			// 1. admin 메뉴 들어감
			database->addATMHistory("출금", -3000, AC1);
			database->addATMHistory("입금", 50000, AC2);
			database->printATMhistory();
			// 2. admin password check

			// 3. 전체 history 보여줌

			// 4. user history 
			UserStatus = 1;
			UserStatus = 1;
		}
		if (UserStatus == 3) { // 계좌 선택 및 본인 확인
			cout << "Please insert your card. 계좌번호를 입력해 주십시오." << endl; // 카드 투입, 계좌번호 입력 단계. 추후 instruction에 따라 바뀔 수 있음
			int userIDAnswer;
			cin >> userIDAnswer; // 계좌번호 입력

			userIndex = database->getIndexFromID(userIDAnswer); // 앞으로 이사람 계좌 접근하고싶으면 database->getAccountByNum(userIndex)하면 된다(Account*)
			
			if (userIndex == -1) {
				cout << "Non existing account error. 존재하지 않는 계좌입니다. Please try again. 다시 입력해 주십시오." << endl;
				continue;
			}

			int passworderror = 0;
			while (true) {
				if (passworderror == 3) { break; }
				cout << "Please input your password. 비밀번호를 입력해 주십시오." << endl;
				int userPWAnswer;
				cin >> userPWAnswer;
				if (database->getAccountByNum(userIndex)->checkPassward(userPWAnswer)) {
					UserStatus = 4;
					break;
				}
				else {
					passworderror++;
					cout << "Wrong password error. 비밀번호가 틀렸습니다. Please try again. 다시 시도하십시오. You have left 남은 시도 횟수: ";
					cout << 3-passworderror << "회 chance(s)." << endl;
					continue;
				}
			}
			if (passworderror == 3) {
				cout << "비밀번호를 3회 틀렸습니다. 처음부터 다시 시도하십시오." << endl;
				UserStatus = 1;
			}
		}
		if (UserStatus == 4) { // 거래 종류 선택
			cout << "Which transaction do you want? 어떤 거래를 하시겠습니까?\n\t1. deposit 입금\t2. withdraw 출금\t3. transfer 송금\t4. undo 뒤로가기\t5. quit 종료" << endl;
			int userAnswer;
			cin >> userAnswer;
			if (userAnswer == 1) { UserStatus = 5; }
			else if (userAnswer == 2) { UserStatus = 6; }
			else if (userAnswer == 3) { UserStatus = 7; }
			else if (userAnswer == 4) { UserStatus = 3; }
			else if (userAnswer == 5) { UserStatus = 0; }
			else { cout << "error" << endl; } // TODO: 적절하지 않은 data input에 대한 에러 처리 필요
		}
		if (UserStatus == 5) {
			cout << "입금" << endl;
			// 입금 함수 실행
			int type;
			while (true) {
				cout << "Which would be your input? 현금으로 입금하시겠습니까?\n\t1. cash 현금\t2. check 수표" << endl;
				cin >> type;
				if (type == 1 or type == 2) { break; }
				else { cout << "잘못된 입력입니다. 다시 시도해 주십시오." << endl; }
			}
			cout << "입금하실 금액의 장당 액수를 입력해주십시오." << endl;
			int moneytype;
			cin >> moneytype;
			cout << "입금하실 금액의 장 수를 입력해주십시오." << endl;
			int paperNum;
			cin >> paperNum;
			bool success = A1->deposit(type, moneytype * paperNum, paperNum, database->getAccountByNum(userIndex)); // 일단 ATM A1이라고 가정
			if (success) { UserStatus = 4; }
			else { UserStatus = 5; }
			cout << "Remaining cash of the ATM / ATM기 현금 잔액 : " << A1->getATMremainCash() << endl;
			cout << "Remaining checkNum of the ATM / ATM기 수표 장 수 : " << A1->getATMremainCheckNum() << endl;
		}
		if (UserStatus == 6) {
			cout << "출금하실 금액을 입력해 주십시오." << endl;
			int money;
			cin >> money;
			// 출금 함수 실행
			bool success = A1->withdrawal(money, database->getAccountByNum(userIndex)); // 일단 ATM A1이라고 가정
			if (success) { UserStatus = 4; }
			else { UserStatus = 6; }
			cout << "ATM기 잔액 : " << A1->getATMremainCash() << endl;
		}
		
		if (UserStatus == 7) {
			cout << "You have chosen [transfer]. 송금을 선택하셨습니다." << endl;
			
			for (;;) {
			
				// cash transfer인지 account transfer인지 묻기
				int transferType; // for loop 안에서의 local variable; 재정의 issue 없음
				for (;;) {
					cout << "Please select transfer options. 원하시는 송금 옵션을 선택해 주십시오.\n\t1. cash transfer 현금 송금\t2. account transfer 계좌 송금\n\tcancel 취소: -1" << endl;
					cin >> transferType; // Exception handling 필요
					
					if (cin.fail()) { cout << "Wrong input error. 잘못된 입력입니다.(code 701)" << endl; cin.clear(); cin.ignore(256, '\n'); }
					else if (transferType == 1) { cout << "You have chosen [cash transfer]. 현금 송금을 선택하셨습니다." << endl; break; }
					else if (transferType == 2) { cout << "You have chosen [account transfer]. 계좌 송금을 선택하셨습니다." << endl; break; }
					else if (transferType == -1) { cout << "You have exited [transfer] session. 송금을 취소하셨습니다." << endl; break; }
					else { cout << "Wrong input error. 잘못된 입력입니다.(code 702)" << endl; cin.clear(); cin.ignore(256, '\n'); }
				}
				if (transferType == -1) { UserStatus = 4; break; }
				
				// 송금할 계좌 묻기
				int toAcc;
				int confirm;
				for (;;) {
					cout << "Please input the account you would like to transfer your money to. 송금하실 계좌의 계좌번호를 입력해 주십시오.\n\tcancel 취소: -1" << endl;
					cin >> toAcc; // Exception handling 필요
					if (cin.fail()) { cout << "Wrong input error. 잘못된 입력입니다.(code 701)" << endl; cin.clear(); cin.ignore(256, '\n'); continue; }
					if (toAcc == -1) { break; }
					if (database->getIndexFromID(toAcc) == -1) {
						cout << "Invalid account error. 존재하지 않는 계좌입니다.(code 703)" << endl; cin.clear(); cin.ignore(256, '\n'); continue; 
					}
					if (userIndex == toAcc) {
						cout << "You cannot transfer from this account to the same account. 같은 계좌로 송금할 수 없습니다. (You mean deposit? 입금을 원하신다면 입금 기능을 이용해 주십시오.)" << endl; 
						cin.clear(); 
						continue; 
					}
					
					// 금융실명제
					for (;;) {
						cout << "[" << database->getAccountByNum(toAcc)->getOwner()->getName();
						cout << "] 님의 계좌 [" << toAcc << "]가 맞습니까?\n\t1. yes 예\t2. try different account 다시 입력\n\tcancel 취소: -1" << endl;
						cin >> confirm;
						if (cin.fail()) { cout << "Wrong input error. 잘못된 입력입니다.(code 701)" << endl; cin.clear(); cin.ignore(256, '\n'); continue; }
						if (confirm == 1) { break; }
						if (confirm == 2) { break; }
						if (confirm == -1) { cout << "You have exited [transfer] session. 송금을 취소하셨습니다." << endl; break; }
						else { cout << "Wrong input error. 잘못된 입력입니다.(code 702)" << endl; cin.clear(); cin.ignore(256, '\n'); }
					}
					if (confirm == 2) { continue; }
					if (confirm == -1) { break; }
					
					break;
				}
				if (toAcc == -1) { UserStatus = 4; break; }
				if (confirm == -1) { UserStatus = 4; break; }
				
				// cash transfer일 경우 remainCash 늘리기; Cash 넣을 때 액수초과 오류 함수로 따로 만들면 편할듯)
				// 일단 전부 현금이고 한계 없다고 가정했음; 
				// 장당 액수, 장수, 그리고 수표까지 고려할 경우 입금함수랑 같이 쓸 수 있는 함수 만드는 게 좋을듯
				// 얼마나 송금할지 묻기
				int transferMoney;
				for (;;) {
					if (transferType == 1) { cout << "Please insert cash you would like to transfer. 송금할 현금을 투입해 주십시오.\n\tcancel 취소: -1" << endl; // 여기도 뒤로가기 기능 구현하고 싶은데 어떻게??
						// 투입 valid한지 check하기(장수, 금액, 송금한도 등; 입금이랑 같이 사용할 수 있는 함수 만들기)
						cin >> transferMoney; // Exception handling 필요
						if (cin.fail()) { cout << "Wrong input error. 잘못된 입력입니다.(code 701)" << endl; cin.clear(); cin.ignore(256, '\n'); continue; }
						if (transferMoney == -1) { cout << "You have exited [transfer] session. 송금을 취소하셨습니다." << endl; break; }
						if (transferMoney <= 0) { cout << "Wrong input error. 잘못된 입력입니다.(code 705)" << endl; cin.clear(); cin.ignore(256, '\n'); continue; }
						// 장수, 금액 체크는 아직; 입금이랑 같이 사용할 수 있는 함수 만들기
						// remainCash transferMoney만큼 늘리기
						A1->insertCash(transferMoney); // ATM A1이라고 가정
						cout << "Debug: Remaining cash of the ATM : " << A1->getATMremainCash() << endl;
						break;
					}
					else if (transferType == 2) { 
						cout << "Please input the amount of money you would like to transfer. 송금할 금액을 입력해 주십시오. (Your current balance 계좌 잔액: ";
						cout << database->getAccountByNum(userIndex)->getBalance() << ")\n\tcancel 취소: -1" << endl; 
						// 액수 valid한지 check하기(계좌 잔액, 송금한도 등;)
						cin >> transferMoney; // Exception handling 필요
						if (cin.fail()) { cout << "Wrong input error. 잘못된 입력입니다.(code 701)" << endl; cin.clear(); cin.ignore(256, '\n'); continue; }
						if (transferMoney == -1) { cout << "You have exited [transfer] session. 송금을 취소하셨습니다." << endl; break; }
						if (transferMoney <= 0) { cout << "Wrong input error. 잘못된 입력입니다.(code 705)" << endl; cin.clear(); cin.ignore(256, '\n'); continue; }
						if (transferMoney > database->getAccountByNum(userIndex)->getBalance()) {
							cout << "Not enough balance error. 잔액이 부족합니다." << endl;
							continue;
						}
						break;
					}
					
				}
				if (transferMoney == -1) { UserStatus = 4; break; }
				
				confirm = 0;
				for (;;) {
					cout << "[" << database->getAccountByNum(toAcc)->getOwner()->getName();
					cout << "] 님에게 [" << transferMoney << "]원 송금하시겠습니까?\n\t1. confirm 확인\n\tcancel 취소: -1" << endl;
					cin >> confirm;
					if (cin.fail()) { cout << "Wrong input error. 잘못된 입력입니다.(code 701)" << endl; cin.clear(); cin.ignore(256, '\n'); continue; }
					if (confirm == 1) { break; }
					if (confirm == -1) { cout << "You have exited [transfer] session. 송금을 취소하셨습니다." << endl; break; }
					else { cout << "Wrong input error. 잘못된 입력입니다.(code 702)" << endl; cin.clear(); cin.ignore(256, '\n'); }
				}
				if (confirm == -1) {
					if (transferType == 1) { 
					cout << "Your cash has returned. Please make sure to take your cash." << endl; 
					A1->insertCash(-transferMoney); // ATM A1이라고 가정
					cout << "Debug: Remaining cash of the ATM : " << A1->getATMremainCash() << endl;
					}
				UserStatus = 4; 
				break; 
				}
				
				
				// 송금함수 호출
				bool success = A1->transfer(transferMoney, database->getAccountByNum(userIndex), database->getAccountByNum(toAcc));
				if (success) { UserStatus = 4; }
				else { UserStatus = 5; }
				break;
			}
		}
	}
	
	// delete session
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
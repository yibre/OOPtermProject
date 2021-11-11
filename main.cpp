#include "Classes.h"

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

	Bank* uriBank = new Bank();
	Bank* kakaoBank = new Bank("kakao");

	User* U1 = new User("U1", "최가난");
	User* U2 = new User("U2", "권부자");
	User* U3 = new User("U3", "서모녀");
	User* U4 = new User("U4", "김백규");
	User* U5 = new User("U5", "버터");

	ATM* A1 = new ATM(uriBank, "admin", 1357, 100000000, 100, true); // 0
	ATM* A2 = new ATM(kakaoBank, "master", 2345, 2000000, 0, false); // 1

	Account* AC1 = new Account(uriBank, U1, 2345, 10000); // 0
	database->addAccountList(AC1);
	Account* AC2 = new Account(uriBank, U2, 3344, 3000000); // 1
	database->addAccountList(AC2);
	Account* AC3 = new Account(kakaoBank, U3, 22, 450000); // 2
	database->addAccountList(AC3);
	Account* AC4 = new Account(kakaoBank, U1, 1024, 50000); // 3.
	database->addAccountList(AC4);

	cout << database->getAccountByNum(2)->getBalance() << endl;

	int userIndex = -1;
	while (UserStatus != 0) {
		if (UserStatus == 1) {
			// [의논필요] input을 int 말고 string으로 받아야할까? type error가 안 나도록?
			// [의논필요] instructor에 atm이 2중언어 지원하는 atm 지원안하는 atm 만들라고 했는데 그럼 atm 선택 단계도 넣어줘야할까?
			cout << "메뉴를 선택하세요 \n 1. admin panal 보기 \n 2. 개인거래하기 \n 3. exit" << endl;
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
			cout << "계좌번호를 입력해주세요" << endl; // 카드 투입, 계좌번호 입력 단계. 추후 instruction에 따라 바뀔 수 있음
			int userIDAnswer;
			cin >> userIDAnswer; // 계좌번호 입력
			userIndex = database->getIndexFromID(userIDAnswer);

			if (userIndex == -1) {
				cout << "존재하지 않는 계좌입니다. 다시 입력해주세요." << endl;
				continue;
			}

			int passworderror = 0;
			while (true) {
				if (passworderror == 3) { break; }
				cout << "비밀번호를 입력해주세요." << endl;
				int userPWAnswer;
				cin >> userPWAnswer;
				if (database->getAccountByNum(userIndex)->checkPassward(userPWAnswer)) {
					UserStatus = 4;
					break;
				}
				else {
					cout << "비밀번호가 틀렸습니다. 다시 시도해주세요." << endl;
					passworderror++;
					continue;
				}
			}
			if (passworderror == 3) {
				cout << "비밀번호를 3회 틀렸습니다. 처음부터 다시 시도해주세요." << endl;
				UserStatus = 1;
			}
		}
		if (UserStatus == 4) { // 거래 종류 선택
			cout << "어떤 거래를 하시겠습니까? \n 1. 입금 \n 2. 출금 \n 3. 송금 \n 4. 이전 단계로 \n 5. exit" << endl;
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
				cout << "현금으로 입금하시겠습니까? \n 1. 현금 \n 2. 수표" << endl;
				cin >> type;
				if (type == 1 or type == 2) { break; }
				else { cout << "잘못된 입력입니다. 다시시도해 주십시오." << endl; }
			}
			cout << "입금하실 금액의 장 당 액수를 입력해주십시오." << endl;
			int moneytype;
			cin >> moneytype;
			cout << "입금하실 금액의 장 수를 입력해주십시오." << endl;
			int paperNum;
			cin >> paperNum;
			bool success = A1->deposit(type, moneytype * paperNum, paperNum, database->getAccountByNum(userIndex));
			if (success) { UserStatus = 4; }
			else { UserStatus = 5; }
			cout << "ATM기 현금 잔액 : " << A1->getATMremainCash() << endl;
			cout << "ATM기 수표 장 수 : " << A1->getATMremainCheckNum() << endl;
		}
		if (UserStatus == 6) {
			cout << "출금하실 금액을 입력해 주십시오." << endl;
			int money;
			cin >> money;
			// 출금 함수 실행
			bool success = A1->withdrawal(money, database->getAccountByNum(userIndex));
			if (success) { UserStatus = 4; }
			else { UserStatus = 6; }
			cout << "ATM기 잔액 : " << A1->getATMremainCash() << endl;
		}
		if (UserStatus == 7) {
			cout << "송금" << endl;
			// 송금 함수 실행
			UserStatus = 4;
		}

	}
	return 0;
}
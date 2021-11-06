#include "Classes.h"
#include <iostream>
#include <string>

/*
0: 프로그램 종료시 0으로 종료
1: 세션 진행중. 프로그램 시작 후 1로 넘어감
admin이 atm 기록 볼 때도 status 1임
2: 계좌번호 확인 과정
3: 거래종류 선택 중 / 입금, 출금, 송금
4: 입금
5: 출금
6: 송금
7: 한 세션 종료 flag, 세션 결과 출력 후 다시 1로 넘어감
*/
using namespace std;

int main() {

	int UserStatus = 1; // 세션 시작

	Bank *uriBank = new Bank();
	Bank *kakaoBank = new Bank("kakao");

	User *U1 = new User("U1", "최가난");
	User *U2 = new User("U2", "권부자");
	User *U3 = new User("U3", "서모녀");
	User *U4 = new User("U4", "김백규");
	User *U5 = new User("U5", "버터");

	ATM *A1 = new ATM(uriBank, "admin", 1357, 100000000, 100, true);
	ATM *A2 = new ATM(kakaoBank, "master", 2345, 2000000, 0, false);
	cout << A1->getATMremainCash() << endl;
	
	Account *AC1 = new Account(uriBank, U1, 2345, 10000);
	Account *AC2 = new Account(uriBank, U2, 3344, 3000000);
	Account *AC3 = new Account(kakaoBank, U3, 22, 450000);
	Account *AC4 = new Account(kakaoBank, U1, 1024, 50000);
	cout << AC1->getBalance() << endl;


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

			// 2. admin password check

			// 3. 전체 history 보여줌

			// 4. user history 
			UserStatus = 1;
		} 
		if (UserStatus == 3){ // 계좌 선택 및 본인 확인
			cout << "계좌번호를 입력해주세요" << endl; // 카드 투입, 계좌번호 입력 단계. 추후 instruction에 따라 바뀔 수 있음
			int userAnswer;
			cin >> userAnswer; // 계좌번호 입력
			// 본인확인, [의논필요] 본인확인하고 틀리면 어디로 돌아가지?
			UserStatus = 4;
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
			UserStatus = 4;
		}
		if (UserStatus == 6) {
			cout << "출금" << endl;
			// 출금 함수 실행
			UserStatus = 4;
		}
		if (UserStatus == 7) {
			cout << "송금" << endl;
			// 송금 함수 실행
			UserStatus = 4;
		}

	}

	return 0;
}
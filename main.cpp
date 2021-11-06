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
    /*
    Account *AC1 = new Account(uriBank, U1, 2345, 10000);
    Account *AC2 = new Account(uriBank, U2, 3344, 3000000);
    Account *AC3 = new Account(kakaoBank, U3, 22, 450000);
    cout << AC1->getBalance() << endl;
    
    
    while (UserStatus != 0) {
        string UserInput;
        getline(cin, UserInput);

        // cout << AC1->getBalance() << endl;

        if (UserStatus == 1) {
            // ATM 선택 단계, 디버깅용으로 넣어둠
            cout << "please choose the ATM number among these (e.g. A1, B4)" << endl;

            UserStatus = 2;
        } else if (UserStatus == 2) {
            // after checking admin, and show the history

            // if the admin menu is over, go back to the mainstream, User status ==1
            UserStatus = 1;
        } else if (UserStatus == 3){
            // 세션 시작
            cout << "계좌번호를 입력해주세요" << endl; // 카드 투입, 계좌번호 입력 단계. 추후 instruction에 따라 바뀔 수 있음
            
            //
        } else if (UserStatus == 4) {

        }
        // exit 을 타입할 시 단계와 무관하게 세션 종료
        if (UserInput == "exit") {UserStatus = 0;}

        

        cout << UserInput << endl;

    }
       */
    
    cout << "계좌번호를 넣어주세요" << endl;


    return 0;
}
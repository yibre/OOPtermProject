#include "Classes.h"
#include <iostream>
#include <string>

/*
0: 프그ㅁ 자 종ㅛ
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

    while (UserStatus != 0) {
        string UserInput;
        getline(cin, UserInput);

        if (UserStatus == 1) {
            // ATM 선택 단계, 디버깅용으로 넣어둠
            cout << "please choose the ATM number among these (e.g. A1, B4)" << endl;

            UserStatus = 2;
        } else if (UserStatus == 2) {
            // admin인지 확인 후 
        }
        // exit 을 타입할 시 단계와 무관하게 세션 종료
        if (UserInput == "exit") {UserStatus = 0;}

        

        cout << UserInput << endl;

    }
    
    cout << "계좌번호를 넣어주세요" << endl;


    return 0;
}
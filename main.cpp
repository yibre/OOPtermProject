#include "Classes.h"
#include <iostream>
#include <string>

/*
0: 세션 대기, 프로그램 시작하고 난 직후 이후 다시 0 될 일 없음
1: 세션 진행중. 프로그램 시작 후 1로 넘어감
admin이 atm 기록 볼 때도 status 1임
2: 계좌번호 확인 과정
3: 거래종류 선택 중 / 입금, 출금, 송금
4: 입금
5: 출금
6: 송금
7: 한 세션 종료 flag, 세션 결과 출력 후 다시 1로 넘어감
*/
#define UserStatus 0


using namespace std;

int main() {

    string str;
    while (cin >> str) {

        // exit 을 타입할 시 단계와 무관하게 세션 종료
        // 프로그램 종료에 대한 input 기준은 없음
        if (str == "exit") {break;}
        // if (cin.eof() == true) {break;}
        cout << str << endl;

    }
    
    cout << "계좌번호를 넣어주세요" << endl;


    return 0;
}
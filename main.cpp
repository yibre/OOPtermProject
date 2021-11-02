 #include "Classes.h"
#include <iostream>
#include <string>

using namespace std;

int main() {

    string str;
    while (cin >> str) {
        if (str == "exit") {break;}
        if (cin.eof() == true) {break;}
        cout << str << endl;

    }
    
    cout << "계좌번호를 넣어주세요" << endl;


    return 0;
}
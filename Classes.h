#include <string>
#include <vector>

using namespace std;

struct Bilingual {
    bool flag; // true면 선택가능, false면 그대로 1번 보냄
    const string* mentions[10][2] = {
        {"반갑습니다", "Hello sir"},
        {"테스트", "test"}
    };

};

class History {
private:
    // 2d  array;
public:
    History();
    ~History();
    vector<vector<string>> History;
    //char History[][10];
    // history 를 보관하는 2d 어레이
    /*
    번호 username userid  거래타입(입출송) 거래계좌id 상대계좌id 거래액수 거래전잔액 거래후잔액 날짜
    ----------------------
    1 김수한무     3        송금
    ----------------------
    2
    -----------------------
    3
    */
};

class User {
private:
    char ID; // user는 U1, U2, U3 이렇게 시작
    char name;

public:
    User() {};
    ~User() {};
    // account list가 들어가는 범위 공개
    Account* accountlist[]; // test를 위하여 설정해둠
};

class Bank {
private:
    char ID; // bank는 B1, B2, B3 이렇게 시작
    string name;

public:
    Account* accountlist[300];

};

class ATM {
private:
    char ID; // atm은 A1 A2 A3 이렇게 시작
    Bank *ownerBank;
    char adminID;
    int adminpw;

public:
    static History* getInstance();
    bool checkID(char);
    bool checkpw(int);

};


class Account {
private:
    int ID; // ID는 0부터 시작해 1씩 늘려감, 순수 숫자
    static int addID = 0; // 어떤 ID를 부여할것인가
    Bank *ownerBank;
    User *owner;
    int passward; // password는 순수 integer 구성, 카드와 동일

public:
    Account() {};
    ~Account() {};
    int getID();
    bool checkPassward(int);
    // int 타입의 패스워드를 받아 해당 코드가 맞는지 확인
    
};
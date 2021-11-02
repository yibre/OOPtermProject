#include <string>
#include <vector>

using namespace std;

const char* mentions[10][2] = {
    {"반갑습니다", "Hello sir"},
    {"테스트", "test"},
    {"카드를 넣어주세요", "genshin impact"}
};

class Account;
class ATM;
class User;
class Bank;

// 쓸 수 있으면 map 쓰는게 제일 좋을듯
class History {
private:
    // 2d  array;
public:
    History() {};
    ~History() {};
    // atm history 보관소
    vector<vector<string> > atmhis; //
    // user가 세션 종료 후 받게 되는 명세서
    vector<vector<string> > sessionhis;

    //char History[][10];
    // history 를 보관하는 2d 어레이
    /*
    번호 username userid  거래타입(입출송) 거래계좌id 상대계좌id 거래액수 거래전잔액 거래후잔액 날짜
    ----------------------
    1 김수한무     3        송금         1         3
    ----------------------
    2 거북이와두루미 4        출금         7         NULL       10  
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
    Account* accountlist[300]; // test를 위하여 설정해둠
};

class Bank {
private:
    char ID; // bank는 B1, B2, B3 이렇게 시작
    static int addID; // 0부터 시작해서 1씩 증가
    string name;

public:
    Bank() {};
    ~Bank() {};
    Account* accountlist[300];
};

class ATM {
private:
    char ID; // atm은 A1 A2 A3 이렇게 시작
    static int addID; // id 부여용 넘버, 0부터 시작해서 1씩 증가
    Bank *ownerBank;
    char adminID;
    int adminpw;
    int cash; // atm 내부 현금 총액
    int check; // atm 내부 수표 총액
    bool bilingual;
    History* atmhis;

public:
    static History* getInstance();
    bool checkID(char);
    bool checkpw(int);
    void deposit(char, int); // 입금함수, 입금액
    void withdrawal(int); // 출금함수, 출금액
};


class Account {
private:
    int ID; // ID는 0부터 시작해 1씩 늘려감, 순수 숫자
    static int addID; // 어떤 ID를 부여할것인가
    Bank *ownerBank;
    User *owner;
    int passward; // password는 순수 integer 구성, 카드와 동일
    int balance; // 잔액
    History* accounthis;

public:
    Account() {};
    ~Account() {};
    int getID();
    bool checkPassward(int);
    // int 타입의 패스워드를 받아 해당 코드가 맞는지 확인
    void deposit(char, int); // 입금, 입금액 타입(캐시, 수표) 입금액 인풋,
    void remittance(int, int); //송금 계좌번호, 액수 
    void widthrawal(int); // 출금
};


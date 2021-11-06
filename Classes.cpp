#include "Classes.h"

Database* Database::getInstance() {
    if (!instance) { instance = new Database(); }
    return instance;
}

Account::Account(Bank* bank, User* owner, int pw, int balance) {
    this->ownerBank = bank;
    this->owner = owner;
    this->password = pw;
    this->balance = balance;
    this->ID = numID;
    increaseID(); // id를 부여한 뒤에는 static id를 1 추가함
}

ATM::ATM(Bank* bank, string adminID, int adminPW, int cash, int check, bool engSupport) {
    this->engSupport = engSupport;
    this->ownerBank = bank;
    this->adminID = adminID;
    this->adminpw = adminPW;
    this->remainCash = cash;
    this->remainCheck = check;
}

// Bank::Bank(string name) { this->name = name; }
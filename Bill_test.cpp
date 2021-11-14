#pragma once
#include <iostream>
#include <string>

class Bill {
private:
	// int b50k=0, b10k=0, b5k=0, b1k=0;
	int paperCash[4] = {0,0,0,0};
	static int value[4];
public:
	Bill (int c50k, int c10k, int c5k, int c1k);
	// int getTotalNum() { return (b50k + b10k + b5k + b1k); }
	// int getSum() { return (50000*b50k + 10000*b10k + 5000*b5k + 1000*b1k); }
	// Bill isPossible(int);
	bool isPossible(int);
	int isImpossible(int, Bill&);
friend void printBill(const Bill& bill);
	
};

int Bill::value[4] = {50000,10000,5000,1000};

Bill::Bill (int c50k=0, int c10k=0, int c5k=0, int c1k=0): paperCash{c50k, c10k, c5k, c1k} {}

bool Bill::isPossible(int money) {
	Bill required;
	for (int i=0; i<4; i++) {
		if (paperCash[i] <= (money/value[i])) { // 장수부족
			money -= paperCash[i]*value[i];
			required.paperCash[i] = this->paperCash[i];
		}
		else { // 장수충분
			money -= value[i]*(money/value[i]); 
			required.paperCash[i] = money/value[i];
		}
	}
	if (money != 0) { return false; }
	return true;
}

int Bill::isImpossible(int money, Bill& required) {
	for (int i=0; i<4; i++) {
		if (paperCash[i] <= (money/value[i])) { // 장수부족
			money -= paperCash[i]*value[i];
			required.paperCash[i] = this->paperCash[i];
		}
		else { // 장수충분
			money -= value[i]*(money/value[i]); 
			required.paperCash[i] = money/value[i];
		}
	}
	return money;
}

void printBill(const Bill& bill) {
	for (int i=0; i<4; i++) {
		std::cout << bill.paperCash[i] << " ";
	}
	std::cout << std::endl;
}

/*
int main() {
	
	Bill temp{};
	Bill bill1{1,3,0,0};
	std::cout << bill1.isImpossible(50000, temp) << std::endl; // 0
	printBill(temp);
	std::cout << bill1.isImpossible(100000, temp) << std::endl; // not 0
	printBill(temp);
	std::cout << bill1.isImpossible(40000, temp) << std::endl; // not 0
	printBill(temp);
	std::cout << std::endl;
	
	Bill bill2{1000,1000,1000,1000};
	std::cout << bill2.isImpossible(591000, temp) << std::endl; // 0
	printBill(temp);
	std::cout << bill2.isImpossible(45000, temp) << std::endl; // 0
	printBill(temp);
	std::cout << std::endl;
	
	Bill bill3{};
	std::cout << bill3.isImpossible(591000, temp) << std::endl; // not 0
	printBill(temp);
	std::cout << bill3.isImpossible(45000, temp) << std::endl; // not 0
	printBill(temp);
	std::cout << std::endl;
	
	
	Bill bill1{1,3,0,0};
	std::cout << bill1.isPossible(50000) << std::endl; // 1
	std::cout << bill1.isPossible(100000) << std::endl; // 0
	std::cout << bill1.isPossible(40000) << std::endl; // 0
	std::cout << std::endl;
	
	Bill bill2{1000,1000,1000,1000};
	std::cout << bill2.isPossible(591000) << std::endl; // 1
	std::cout << bill2.isPossible(45000) << std::endl; // 1
	std::cout << std::endl;
	
	Bill bill3{};
	std::cout << bill3.isPossible(591000) << std::endl; // 0
	std::cout << bill3.isPossible(45000) << std::endl; // 0
	std::cout << std::endl;
	
	return 0;
}
*/
#pragma once
#include <string>
#include <map>
#include <vector>
#include <iostream>
// #include "Language.cpp" // 현주용

using namespace std;

class Translation {
private:
	map<string, string> translation_en;
	map<string, string> translation_kr;
	bool currentIsKor = true;
public:
	Translation();
	void changeLanguage(string Lang) {
		if (Lang == "EN") {
			this->currentIsKor = false;
		}
		else if (Lang == "KOR") {
			this->currentIsKor = true;
		}
		else {
			cout << "Debug : Wrong Language Type! Change to Default Korean" << endl;
			this->currentIsKor = true;
		}
	};
	string getSentence(string key) {
		if (this->currentIsKor) {
			return this->translation_kr[key];
		}
		else {
			return this->translation_en[key];
		}
	};
	bool isKor() {
		return currentIsKor;
	}
};
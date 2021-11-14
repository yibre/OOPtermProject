#pragma once
#include <iostream>
#include <string>

class UI {
private:
	enum class State {
		Session1Prompt,
		Session1Digit,
		Session1Confirm,
		Session2Prompt,
		Session2Digit,
		Session2Confirm,
		Session3Prompt,
		Session3Confirm,
		End
	} 
	state = State::Session1Prompt;
	// int UserStatus = 1;
	int FirstDigit = 0;
	int SecondDigit = 0;
public:
	int run();
private:
	static int getInput(const std::string& prompt, int maximum);
	State session1Prompt();
	State session1Digit();
	State session1Confirm();
	State session2Prompt();
	State session2Digit();
	State session2Confirm();
	State session3Prompt();
	State session3Confirm();
};

int UI::run() {
	while (state != State::End) {
		switch (state) {
			case State::Session1Prompt:
				state = session1Prompt();
				break;
			case State::Session1Digit:
				state = session1Digit();
				break;
			case State::Session1Confirm:
				state = session1Confirm();
				break;
			case State::Session2Prompt:
				state = session2Prompt();
				break;
			case State::Session2Digit:
				state = session2Digit();
				break;
			case State::Session2Confirm:
				state = session2Confirm();
				break;
			case State::Session3Prompt:
				state = session3Prompt();
				break;
			case State::Session3Confirm:
				state = session3Confirm();
				break;
		}
	}
	return 0;
}

using namespace std;

int UI::getInput(const string& prompt, int maximum) {
	int input;
	for (;;) {
		cout << prompt;
		cout.flush(); // Similar to endl, without new line.
		cin >> input;
		if (cin.fail()) { cout << "Wrong type error" << endl; cin.clear(); cin.ignore(256, '\n'); continue; }
		if (input < 0 || input > maximum) { cout << "Wrong range error" << endl; cin.clear(); cin.ignore(256, '\n'); continue; }
		break;
	}
	return input;
}

UI::State UI::session1Prompt() {
	cout << "\t[session 1]" << endl;
	cout << "\tYour number: nm (two-digit number; n=1~2, m=1~2)" << endl;
	return State::Session1Digit;
}

UI::State UI::session1Digit() {
	int input = getInput("\tFirst digit n=1~2\t\t(0 to cancel)\nn: ", 2);
	if (input) {
		FirstDigit = input;
		return State::Session1Confirm;
	}
	cout << "Canceled; Goto session 0" << endl;
	return State::End;
}

UI::State UI::session1Confirm() {
	string prompt = "\tYour choice for first digit n: ";
	prompt += to_string(FirstDigit);
	prompt += "\n\tIs this correct?\t\t(1 to confirm; 0 to cancel)\n";
	if (getInput(prompt, 1) == 0) {
		return State::Session1Digit;
	}
	return State::Session2Prompt;
}

UI::State UI::session2Prompt() {
	cout << "\t[session 2]" << endl;
	cout << "\tYour number: " << FirstDigit << "m (two-digit number; m=1~2)" << endl;
	return State::Session2Digit;
}

UI::State UI::session2Digit() {
	int input = getInput("\tSecond digit n=1~2\t\t(0 to cancel)\nn: ", 2);
	if (input) {
		SecondDigit = input;
		return State::Session2Confirm;
	}
	cout << "Canceled; Goto session 1" << endl;
	return State::Session1Prompt;
}

UI::State UI::session2Confirm() {
	string prompt = "\tYour choice for second digit m: ";
	prompt += to_string(SecondDigit);
	prompt += "\n\tIs this correct?\t\t(1 to confirm; 0 to cancel)\n";
	if (getInput(prompt, 1) == 0) {
		return State::Session2Digit;
   }
   return State::Session3Prompt;
}

UI::State UI::session3Prompt() {
	cout << "\t[session 3]" << endl;
	return State::Session3Confirm;
}

UI::State UI::session3Confirm() {
	string Number = to_string(FirstDigit) + to_string(SecondDigit);
	int input = getInput("\tYour number: " + Number + "\n\tIs this final result correct?\t\t(1 to confirm; 0 to cancel)\n", 1);
	if (input) {
		cout << "\tYOUR NUMBER: " << Number << endl;
		return State::End;
	}
	cout << "Canceled; Goto session 2" << endl;
	return State::Session2Prompt;
}

/*
int main() {
	UI ui;
	return ui.run();
}
*/
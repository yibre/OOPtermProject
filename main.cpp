#include "Classes.h"
#include "UI.cpp"
#include <iostream>
#include <string>
/*
0: ���α׷� ����� 0���� ����
1: ���� ������.  admin�̳� �ƴϸ� ���ΰŷ��Ұų� ����
2: admin�޴�
3: ���¹�ȣ �Է� �� ����Ȯ��
4: �ŷ� ���� ����: �� �� �۱�
5: �Ա�
6: ���
7: �۱�
*/

using namespace std;

int main() {
	
	UI ui;
	ui.run();

	return 0;
}

/*
int main() {

	int UserStatus = 1; // ���� ����

	Database* database = Database::getInstance();

	Bank* uriBank = new Bank(); // new�� �Ҵ��Ѱ͵� main ���� delete���ش�
	Bank* kakaoBank = new Bank("kakao"); // Classes.h ���ϱ� �̳� ID�� B1�̰� ����µ�?

	User* U1 = new User("U1", "�ְ���");
	User* U2 = new User("U2", "�Ǻ���");
	User* U3 = new User("U3", "�����");
	User* U4 = new User("U4", "����");
	User* U5 = new User("U5", "����");

	ATM* A1 = new ATM(uriBank, "admin", 1357, 100000000, 100, true); // 0; �����ܾ� 100000000���� ����
	ATM* A2 = new ATM(kakaoBank, "master", 2345, 2000000, 0, false); // 1

	Account* AC1 = new Account(uriBank, U1, 2345, 10000); // ���¹�ȣ 0
	database->addAccountList(AC1);
	Account* AC2 = new Account(uriBank, U2, 3344, 3000000); // ���¹�ȣ 1
	database->addAccountList(AC2);
	Account* AC3 = new Account(kakaoBank, U3, 22, 450000); // ���¹�ȣ 2
	database->addAccountList(AC3);
	Account* AC4 = new Account(kakaoBank, U1, 1024, 1000); // ���¹�ȣ 3
	database->addAccountList(AC4);

	cout << database->getAccountByNum(2)->getBalance() << endl; // ���� �����ϴ� ���¹�ȣ �̿� �Է��ϸ� ���׳�

	int userIndex = -1;
	while (UserStatus != 0) {
		if (UserStatus == 1) {
			// [�ǳ��ʿ�] input�� int ���� string���� �޾ƾ��ұ�? type error�� �� ������?
			// [�ǳ��ʿ�] instructor�� atm�� 2�߾�� �����ϴ� atm �������ϴ� atm ������ �ߴµ� �׷� atm ���� �ܰ赵 �־�����ұ�?
			cout << "�޴��� �����ϼ���.\n\t1. admin panal ����\t2. ���ΰŷ��ϱ�\t3. exit" << endl;
			int UserInput;
			// admin panal ���� or ���ΰŷ��ϱ� ����
			cin >> UserInput;
			if (UserInput == 1) { UserStatus = 2; }
			else if (UserInput == 2) { UserStatus = 3; }
			else if (UserInput == 3) { UserStatus = 0; }
			else { cout << "Error" << endl; } // ���� ó�� �κ� �߰��ؾ���
		}
		if (UserStatus == 2) { // admin panal
			cout << "admin panal" << endl;
			// 1. admin �޴� ��

			// 2. admin password check
			database->addHistory("�Ա�", 30000, AC1, AC1);
			database->addHistory("�۱�", 20000, AC1, AC2);
			database->addHistory("���", 5000, AC1, AC1);
			// 3. ��ü history ������
			database->printHistory();
			// 4. user history 
			cout << "---------------- ���� 2 ----------- " << endl;
			database->clearSessionHistory();
			database->printHistory();
			cout << "---------------- ���� 3 ----------- " << endl;
			database->addHistory("�Ա�", 30000, AC1, AC1);
			database->addHistory("���", 5000, AC1, AC1);
			database->printHistory();

			UserStatus = 1;
		}
		if (UserStatus == 3) { // ���� ���� �� ���� Ȯ��
			cout << "Please insert your card. ���¹�ȣ�� �Է��� �ֽʽÿ�." << endl; // ī�� ����, ���¹�ȣ �Է� �ܰ�. ���� instruction�� ���� �ٲ� �� ����
			int userIDAnswer;
			cin >> userIDAnswer; // ���¹�ȣ �Է�

			userIndex = database->getIndexFromID(userIDAnswer); // ������ �̻�� ���� �����ϰ������ database->getAccountByNum(userIndex)�ϸ� �ȴ�(Account*)

			if (userIndex == -1) {
				cout << "Non existing account error. �������� �ʴ� �����Դϴ�. Please try again. �ٽ� �Է��� �ֽʽÿ�." << endl;
				continue;
			}

			int passworderror = 0;
			while (true) {
				if (passworderror == 3) { break; }
				cout << "Please input your password. ��й�ȣ�� �Է��� �ֽʽÿ�." << endl;
				int userPWAnswer;
				cin >> userPWAnswer;
				if (database->getAccountByNum(userIndex)->checkPassword(userPWAnswer)) {
					UserStatus = 4;
					break;
				}
				else {
					passworderror++;
					cout << "Wrong password error. ��й�ȣ�� Ʋ�Ƚ��ϴ�. Please try again. �ٽ� �õ��Ͻʽÿ�. You have left ���� �õ� Ƚ��: ";
					cout << 3 - passworderror << "ȸ chance(s)." << endl;
					continue;
				}
			}
			if (passworderror == 3) {
				cout << "��й�ȣ�� 3ȸ Ʋ�Ƚ��ϴ�. ó������ �ٽ� �õ��Ͻʽÿ�." << endl;
				UserStatus = 1;
			}
		}
		if (UserStatus == 4) { // �ŷ� ���� ����
			cout << "Which transaction do you want? � �ŷ��� �Ͻðڽ��ϱ�?\n\t1. deposit �Ա�\t2. withdraw ���\t3. transfer �۱�\t4. undo �ڷΰ���\t5. quit ����" << endl;
			int userAnswer;
			cin >> userAnswer;
			if (userAnswer == 1) { UserStatus = 5; }
			else if (userAnswer == 2) { UserStatus = 6; }
			else if (userAnswer == 3) { UserStatus = 7; }
			else if (userAnswer == 4) { UserStatus = 3; }
			else if (userAnswer == 5) { UserStatus = 0; }
			else { cout << "error" << endl; } // TODO: �������� ���� data input�� ���� ���� ó�� �ʿ�
		}
		if (UserStatus == 5) {
			cout << "�Ա�" << endl;
			// �Ա� �Լ� ����
			int type;
			while (true) {
				cout << "Which would be your input? �������� �Ա��Ͻðڽ��ϱ�?\n\t1. cash ����\t2. check ��ǥ" << endl;
				cin >> type;
				if (type == 1 || type == 2) { break; }
				else { cout << "�߸��� �Է��Դϴ�. �ٽ� �õ��� �ֽʽÿ�." << endl; }
			}
			cout << "�Ա��Ͻ� �ݾ��� ��� �׼��� �Է����ֽʽÿ�." << endl;
			int moneytype;
			cin >> moneytype;
			cout << "�Ա��Ͻ� �ݾ��� �� ���� �Է����ֽʽÿ�." << endl;
			int paperNum;
			cin >> paperNum;
			bool success = A1->deposit(type, moneytype * paperNum, paperNum, database->getAccountByNum(userIndex)); // �ϴ� ATM A1�̶�� ����
			if (success) { UserStatus = 4; }
			else { UserStatus = 5; }
			cout << "Remaining cash of the ATM / ATM�� ���� �ܾ� : " << A1->getATMremainCash() << endl;
			cout << "Remaining checkNum of the ATM / ATM�� ��ǥ �� �� : " << A1->getATMremainCheckNum() << endl;
		}
		if (UserStatus == 6) {
			cout << "����Ͻ� �ݾ��� �Է��� �ֽʽÿ�." << endl;
			int money;
			cin >> money;
			// ��� �Լ� ����
			bool success = A1->withdrawal(money, database->getAccountByNum(userIndex)); // �ϴ� ATM A1�̶�� ����
			if (success) { UserStatus = 4; }
			else { UserStatus = 6; }
			cout << "ATM�� �ܾ� : " << A1->getATMremainCash() << endl;
		}

		if (UserStatus == 7) {
			cout << "You have chosen [transfer]. �۱��� �����ϼ̽��ϴ�." << endl;
			Account* fromAcc = database->getAccountByNum(userIndex);

			for (;;) {

				// cash transfer���� account transfer���� ����
				int transferType; // for loop �ȿ����� local variable; ������ issue ����
				for (;;) {
					cout << "Please select transfer options. ���Ͻô� �۱� �ɼ��� ������ �ֽʽÿ�.\n\t1. cash transfer ���� �۱�\t2. account transfer ���� �۱�\n\tcancel ���: -1" << endl;
					cin >> transferType; // Exception handling �ʿ�

					if (cin.fail()) { cout << "Wrong input error. �߸��� �Է��Դϴ�.(code 701)" << endl; cin.clear(); cin.ignore(256, '\n'); }
					else if (transferType == 1) { cout << "You have chosen [cash transfer]. ���� �۱��� �����ϼ̽��ϴ�." << endl; break; }
					else if (transferType == 2) { cout << "You have chosen [account transfer]. ���� �۱��� �����ϼ̽��ϴ�." << endl; break; }
					else if (transferType == -1) { cout << "You have exited [transfer] session. �۱��� ����ϼ̽��ϴ�." << endl; break; }
					else { cout << "Wrong input error. �߸��� �Է��Դϴ�.(code 702)" << endl; cin.clear(); cin.ignore(256, '\n'); }
				}
				if (transferType == -1) { UserStatus = 4; break; }

				// �۱��� ���� ����
				int toAccID;
				int confirm;
				for (;;) {
					cout << "Please input the account you would like to transfer your money to. �۱��Ͻ� ������ ���¹�ȣ�� �Է��� �ֽʽÿ�.\n\tcancel ���: -1" << endl;
					cin >> toAccID; // Exception handling �ʿ�
					if (cin.fail()) { cout << "Wrong input error. �߸��� �Է��Դϴ�.(code 701)" << endl; cin.clear(); cin.ignore(256, '\n'); continue; }
					if (toAccID == -1) { break; }
					if (database->getIndexFromID(toAccID) == -1) {
						cout << "Invalid account error. �������� �ʴ� �����Դϴ�.(code 703)" << endl; cin.clear(); cin.ignore(256, '\n'); continue;
					}
					if (userIndex == toAccID) {
						cout << "You cannot transfer from this account to the same account. ���� ���·� �۱��� �� �����ϴ�. (You mean deposit? �Ա��� ���ϽŴٸ� �Ա� ����� �̿��� �ֽʽÿ�.)" << endl;
						cin.clear();
						continue;
					}

					// �����Ǹ���
					for (;;) {
						cout << "[" << database->getAccountByNum(toAccID)->getOwner()->getUserName();
						cout << "] ���� ���� [" << toAccID << "]�� �½��ϱ�?\n\t1. yes ��\t2. try different account �ٽ� �Է�\n\tcancel ���: -1" << endl;
						cin >> confirm;
						if (cin.fail()) { cout << "Wrong input error. �߸��� �Է��Դϴ�.(code 701)" << endl; cin.clear(); cin.ignore(256, '\n'); continue; }
						if (confirm == 1) { break; }
						if (confirm == 2) { break; }
						if (confirm == -1) { cout << "You have exited [transfer] session. �۱��� ����ϼ̽��ϴ�." << endl; break; }
						else { cout << "Wrong input error. �߸��� �Է��Դϴ�.(code 702)" << endl; cin.clear(); cin.ignore(256, '\n'); }
					}
					if (confirm == 2) { continue; }
					if (confirm == -1) { break; }

					break;
				}
				if (toAccID == -1) { UserStatus = 4; break; }
				if (confirm == -1) { UserStatus = 4; break; }
				Account* toAcc = database->getAccountByNum(toAccID);

				// ������ ���
				int fee = A1->fee(UserStatus, fromAcc, toAcc);
				cout << "Debug: ������� [" << fee << "]���Դϴ�." << endl;

				// cash transfer�� ��� remainCash �ø���; Cash ���� �� �׼��ʰ� ���� �Լ��� ���� ����� ���ҵ�)
				// �ϴ� ���� �����̰� �Ѱ� ���ٰ� ��������; 
				// ��� �׼�, ���, �׸��� ��ǥ���� ����� ��� �Ա��Լ��� ���� �� �� �ִ� �Լ� ����� �� ������
				// �󸶳� �۱����� ����
				int transferMoney;
				for (;;) {
					if (transferType == 1) {
						cout << "Please insert cash you would like to transfer. �۱��� ������ ������ �ֽʽÿ�.\n\tcancel ���: -1" << endl; // ���⵵ �ڷΰ��� ��� �����ϰ� ������ ���??
						// ���� valid���� check�ϱ�(���, �ݾ�, �۱��ѵ� ��; �Ա��̶� ���� ����� �� �ִ� �Լ� �����)
						cin >> transferMoney; // Exception handling �ʿ�
						if (cin.fail()) { cout << "Wrong input error. �߸��� �Է��Դϴ�.(code 701)" << endl; cin.clear(); cin.ignore(256, '\n'); continue; }
						if (transferMoney == -1) { cout << "You have exited [transfer] session. �۱��� ����ϼ̽��ϴ�." << endl; break; }
						if (transferMoney <= 0) { cout << "Wrong input error. �߸��� �Է��Դϴ�.(code 705)" << endl; cin.clear(); cin.ignore(256, '\n'); continue; }
						// ���, �ݾ� üũ�� ����; �Ա��̶� ���� ����� �� �ִ� �Լ� �����
						// ���ݼ۱ݿ� ���� ������ �׼� ��谡 �� �� �׼� �´��� Ȯ�� �ʿ� REQ6.3
						confirm = 0;
						for (;;) {
							// transferMoney : �հ�
							cout << "�����Ͻ� �ݾ��� �´��� Ȯ���� �ֽʽÿ�.\n\t[" << transferMoney << "]��\n\t1. confirm Ȯ��\n\tcancel ���: -1" << endl;
							cin >> confirm; // Exception handling �ʿ�
							if (cin.fail()) { cout << "Wrong input error. �߸��� �Է��Դϴ�.(code 701)" << endl; cin.clear(); cin.ignore(256, '\n'); continue; }
							if (confirm == 1) { break; }
							if (confirm == -1) { cout << "You have exited [transfer] session. �۱��� ����ϼ̽��ϴ�." << endl; break; }
							else { cout << "Wrong input error. �߸��� �Է��Դϴ�.(code 702)" << endl; cin.clear(); cin.ignore(256, '\n'); }
						}
						if (confirm == -1) { cout << "Your cash has returned. �����Ͻ� ������ ��ȯ�Ǿ����ϴ�. Please make sure to take your cash. ���Ա��� Ȯ�����ּ���." << endl; break; }

						cout << "Debug: Remaining cash of the ATM : " << A1->getATMremainCash() << endl;
						break;
					}
					else if (transferType == 2) {
						cout << "Please input the amount of money you would like to transfer. �۱��� �ݾ��� �Է��� �ֽʽÿ�. (Your current balance ���� �ܾ�: ";
						cout << database->getAccountByNum(userIndex)->getBalance() << ")\n\tcancel ���: -1" << endl;
						// �׼� valid���� check�ϱ�(���� �ܾ�, �۱��ѵ� ��;)
						cin >> transferMoney; // Exception handling �ʿ�
						if (cin.fail()) { cout << "Wrong input error. �߸��� �Է��Դϴ�.(code 701)" << endl; cin.clear(); cin.ignore(256, '\n'); continue; }
						if (transferMoney == -1) { cout << "You have exited [transfer] session. �۱��� ����ϼ̽��ϴ�." << endl; break; }
						if (transferMoney <= 0) { cout << "Wrong input error. �߸��� �Է��Դϴ�.(code 705)" << endl; cin.clear(); cin.ignore(256, '\n'); continue; }
						if (transferMoney > fromAcc->getBalance()) {
							cout << "Not enough balance error. �ܾ��� �����մϴ�.(code 706)" << endl; // �ܾ� ���� ���ϱ�� ���� �۱� Ȯ�� �Ŀ��� �ұ�? (������ ��� ����)
							continue;
						}
						break;
					}

				}
				if (confirm == -1) { UserStatus = 4; break; }
				if (transferMoney == -1) { UserStatus = 4; break; }

				// �۱� ���� Ȯ���ϱ�
				confirm = 0;
				for (;;) {
					cout << "[" << toAcc->getOwner()->getUserName();
					cout << "] �Կ��� [" << transferMoney << "]�� �۱��Ͻðڽ��ϱ�?\n������� [";
					cout << fee << "]���Դϴ�. ������� ���� ���� �ܾ� [" << fromAcc->getBalance();
					cout << "]������ �ڵ� �����˴ϴ�.\n\t1. confirm Ȯ��\n\tcancel ���: -1" << endl;
					cin >> confirm;
					if (cin.fail()) { cout << "Wrong input error. �߸��� �Է��Դϴ�.(code 701)" << endl; cin.clear(); cin.ignore(256, '\n'); continue; }
					if (confirm == 1) { break; }
					if (confirm == -1) { cout << "You have exited [transfer] session. �۱��� ����ϼ̽��ϴ�." << endl; break; }
					else { cout << "Wrong input error. �߸��� �Է��Դϴ�.(code 702)" << endl; cin.clear(); cin.ignore(256, '\n'); }
				}
				if (confirm == -1) {
					if (transferType == 1) { cout << "Your cash has returned. �����Ͻ� ������ ��ȯ�Ǿ����ϴ�. Please make sure to take your cash. ���Ա��� Ȯ�����ּ���." << endl; }
					UserStatus = 4;
					break;
				}

				// �۱��Լ� ȣ��
				bool success = A1->transfer(transferType, transferMoney, fromAcc, toAcc);
				if (success) {
					// �۱� Ȯ�εǾ� ��ȯ�� ���� ���� �� remainCash transferMoney��ŭ �ø���
					A1->insertCash(transferMoney); // ATM A1�̶�� ����
					cout << "Debug: Remaining cash of the ATM : " << A1->getATMremainCash() << endl; // ���� �ʿ�
					UserStatus = 4;
				}
				else {
					cout << "Not enough balance error. �ܾ��� �����մϴ�.(code 707)" << endl;
					if (transferType == 1) { cout << "Your cash has returned. �����Ͻ� ������ ��ȯ�Ǿ����ϴ�. Please make sure to take your cash. ���Ա��� Ȯ�����ּ���." << endl; }
					UserStatus = 4;
				}
				break;
			}
		}
	}

	// delete session
	delete AC4;
	delete AC3;
	delete AC2;
	delete AC1;

	delete A2;
	delete A1;

	delete U5;
	delete U4;
	delete U3;
	delete U2;
	delete U1;

	delete kakaoBank;
	delete uriBank;


	return 0;
}

*/
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <random>

using namespace std;

int main() {

	// Instructions:
	//cout << "/********************************************************/" << endl;
	//cout << "/*                      Instructions:                   */" << endl;
	//cout << "/* you need to enter number and names of captains. Next */" << endl;
	//cout << "/*     program will randomly assign captains their      */" << endl;
	//cout << "/*            order of choosing their player            */" << endl;
	//cout << "/*                                                      */" << endl;
	//cout << "/*                        Example:                      */" << endl;
	//cout << "/*                       Tournament                     */" << endl;
	//cout << "/*   32 cap.    16 cap.    8 cap.    4 cap.    2 cap.   */" << endl;
	//cout << "/*      1 Cap in 1 team - 2/4 player (except Cap.)      */" << endl;
	//cout << "/*                       --* or *--                     */" << endl;
	//cout << "/*                     Counter-Strike                   */" << endl;
	//cout << "/*            Need 2 Captains and 4 players             */" << endl;
	//cout << "/********************************************************/" << endl << endl;

	// input data
	int captainNum = 0;
	int teamSize = 0;
	bool validVal = false;
	vector<string> names;

	while (captainNum < 1 || captainNum > 32) {
		cout << "Enter how many captains: ";
		cin >> captainNum;
		if (captainNum > 32)
			cout << "Chill cowboy, lets not exceed 32 first" << endl;
		else if (captainNum < 1)
			cout << "Need number more than 0!" << endl;
	}

	while (!validVal) {
		cout << "Enter team size. Supported only 2 or 4 (expect Capitans): ";
		cin >> teamSize;
		if (teamSize == 2 || teamSize == 4)
			validVal = true;
		else
			cout << "Need enter 2 or 4!" << endl;
	}

	cout << "Enter name of your captains: " << endl;
	cin.ignore();
	for (int i = 1; i <= captainNum; i++) {
		cout << i << ": ";
		string name;
		getline(cin, name);
		names.push_back(name);
	}
	cout << "\n--------------- * RANDOMIZE * ---------------\n" << endl;

	random_device rd;
	mt19937 g(rd());
	shuffle(names.begin(), names.end(), g);

	int numColumn1 = 1;
	int numColumn2 = captainNum + 1;
	int numColumn3 = captainNum + numColumn2;
	int numColumn4 = captainNum + numColumn3;
	for (int i = 0; i < names.size(); i++) {
		string name = names[i];
		if (name.length() > 13) {
			name = name.substr(0, 10);
			name += "...";
		}
		cout << "Capitan " << i + 1 << ": " << setw(10) << left << name;

		// team size
		if (teamSize == 2) {
			cout << "     \t" << numColumn1++ << " pick ";
			cout << "     \t" << numColumn2++ << " pick " << endl;
		}
		if (teamSize == 4) {
			cout << "     \t" << numColumn1++ << " pick ";
			cout << "     \t" << numColumn2++ << " pick ";
			cout << "     \t" << numColumn3++ << " pick ";
			cout << "     \t" << numColumn4++ << " pick " << endl;
		}
	}

	cin.get();
	return 0;
}

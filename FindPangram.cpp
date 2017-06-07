#include <cmath>
#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
	/* Enter your code here. Read input from STDIN. Print output to STDOUT */

	int store_letters[26];
	int count = 0;

	string s = "";

	getline(cin, s);

	int i = 0;
	while (i < s.length()) {
		if (s.at(i) == ' ') {
			s.erase(s.begin() + i);
			continue;
		}
		if (s.at(i) >= 'A' && s.at(i) <= 'Z') {
			if (store_letters[(s.at(i) + 32) - 97] != 1) {
				store_letters[(s.at(i) + 32) - 97] = 1;
				count++;
				cout << count;
			}
		}
		else if (s.at(i) >= 'a' && s.at(i) <= 'z') {
			if (store_letters[s.at(i) - 97] != 1) {
				store_letters[s.at(i) - 97] = 1;
				count++;
				cout << count;
			}
		}
		i++;
	}
	cout << " " << count << '\n';
	for (int j = 0; j < 26; j++) {
		cout << store_letters[j] << " ";
	}
	cout << '\n';
	if (count == 25) {
		cout << "pangram" << '\n';
	}
	else {
		cout << "not pangram" << '\n';
	}

	system("pause");
	return 0;
}

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
	string s;
	cin >> s;

	vector<char> answ(s.size() / 2);

	int aI = 0;
	for (int i = 0; i < s.size() / 2; i += 2) {
		if (s[i] == s[s.size() - 1 - i] || s[i] == s[s.size() - 2 - i]) {
			answ[aI] = s[i];
			answ[answ.size() - 1 - aI] = s[i];
		}
		else {
			answ[aI] = s[i + 1];
			answ[answ.size() - 1 - aI] = s[i + 1];
		}
		aI++;
	}

	for (int i = 0; i < answ.size(); i++) {
		cout << answ[i];
	}
	cout << endl;
}
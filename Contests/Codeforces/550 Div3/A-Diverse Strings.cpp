#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int main() {
	int n;
	cin >> n;

	for (int i = 0; i < n; i++) {
		string t = "";
		cin >> t;

		if (t.size() > 26) { cout << "No" << endl; continue; }
		if (t.size() == 1) { cout << "Yes" << endl; continue; }

		vector<char> letters;

		for (unsigned int j = 0; j < t.size(); j++) {
			letters.push_back(t[j]);
		}
		sort(letters.begin(), letters.end());

		bool found = false;
		for (unsigned int j = 0; j < t.size() - 1; j++) {
			if (letters[j] == letters[j + 1]) {
				cout << "No" << endl;
				found = true;
				break;
			}
		}
		if (found) { continue; }

		found = false;
		for (unsigned int j = 0; j < t.size() - 1; j++) {
			if (int(letters[j + 1]) - int(letters[j]) != 1){
				found = true;
			}
		}
		if (!found) { cout << "Yes" << endl; }
		else { cout << "No" << endl; }
	}
}
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	int t; cin >> t;

	while (t--) {
		int k; cin >> k;
		string s; cin >> s;

		int maxPatient = 0, curPatient = 0;;
		bool startCount = false;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == 'A') {
				startCount = true; curPatient = 0;
			}
			else {
				if (startCount) {
					curPatient++;
					maxPatient = max(curPatient, maxPatient);
				}
			}
		}

		cout << maxPatient << endl;
	}
}
#include <iostream>
#include <string>

using namespace std;


int main() {
	int t;
	cin >> t;
	for (int z = 0; z < t; z++) {
		int n;
		cin >> n;
		string s;
		cin >> s;
		bool found = false;

		for (int i = 0; i <= n-11; i++) {
			if (s[i] == '8') {
				cout << "YES" << endl;
				found = true;
				break;
			}
		}

		if (found) {
			continue;
		}

		cout << "NO" << endl;
	}
}
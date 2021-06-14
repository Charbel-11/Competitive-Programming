#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int n;
	cin >> n;
	string s;
	cin >> s;

	int zeros = 0;
	int ones = 0;

	for (int i = 0; i < n; i++) {
		if (s[i] == '0') { zeros++; }
		else { ones++; }
	}
	if (zeros != ones) {
		cout << 1 << endl << s << endl;
		return 0;
	}

	cout << 2 << endl;
	cout << s[0] << " ";
	for (int i = 1; i < n; i++) {
		cout << s[i];
	}
	cout << endl;
}
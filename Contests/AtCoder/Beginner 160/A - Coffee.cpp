#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	string s; cin >> s;

	bool b = (s[2] == s[3] && s[4] == s[5]);
	cout << (b ? "Yes" : "No") << endl;
}
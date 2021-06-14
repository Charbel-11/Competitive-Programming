#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

bool isLower(char c) {
	return (c >= 'a' && c <= 'z');
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	string s; cin >> s;
	bool OK = true;
	for (int i = 0; i < s.size(); i++) {
		if (i % 2 == 0) { if (!isLower(s[i])) { OK = false; } }
		else { if (isLower(s[i])) { OK = false; } }
	}

	cout << (OK ? "Yes" : "No") << '\n';
}
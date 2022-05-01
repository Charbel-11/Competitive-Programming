#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

bool isUp(char c) {
	return c >= 'A' && c <= 'Z';
}

bool isLow(char c) {
	return c >= 'a' && c <= 'z';
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	string s; cin >> s;

	set<char> seen; bool OK = true;
	bool up = false, low = false;

	for (auto& c : s) {
		if (isUp(c)) { up = true; }
		if (isLow(c)) { low = true; }
		if (seen.count(c)) { OK = false; break; }
		seen.insert(c);
	}

	if (OK && up && low) { cout << "Yes" << '\n'; }
	else { cout << "No" << '\n'; }
}
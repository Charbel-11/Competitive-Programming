#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	string s(3, ' '), t(3, ' ');
	for (auto& c : s) { cin >> c; }
	for (auto& c : t) { cin >> c; }

	int numEqual = 0;
	for (int i = 0; i < 3; i++) {
		numEqual += (s[i] == t[i]);
	}

	if (numEqual == 1) { cout << "No" << '\n'; }
	else { cout << "Yes" << '\n'; }
}
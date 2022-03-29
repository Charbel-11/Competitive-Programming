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

	int n; ll x; cin >> n >> x;
	string s; cin >> s;
	string moves = "";
	for (auto& c : s) {
		if (c == 'U' && !moves.empty() && !(moves.back() == 'U')) { moves.pop_back(); }
		else { moves.push_back(c); }
	}

	for (auto& c : moves) {
		if (c == 'U') { x /= 2; }
		if (c == 'L') { x *= 2; }
		if (c == 'R') { x *= 2; x++; }
	}

	cout << x << '\n';
}
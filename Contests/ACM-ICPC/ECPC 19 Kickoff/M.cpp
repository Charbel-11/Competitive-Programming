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

	freopen("lis.in", "r", stdin);

	string s; cin >> s;
	int n = s.size();

	int l = 0, r = n * 9;
	while (l < r) {
		int mid = (l + r + 1) >> 1;

		int num9 = mid / 9, rem = mid % 9;
		string curS;
		if (rem) { curS = string(num9 + 1, '9'); curS[0] = '0' + rem; }
		else { curS = string(num9, '9'); }

		if (curS.size() < s.size() || (curS.size() == s.size() && curS <= s)) { l = mid; }
		else { r = mid - 1; }
	}

	cout << l << '\n';
}
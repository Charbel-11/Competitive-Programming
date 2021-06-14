#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<char> rgb = { 'R', 'G', 'B' };
string s;
int n, k;

int minCost(int mod) {
	vector<int> partCost(n, 0);
	partCost[0] = !(rgb[mod] == s[0]);
	for (int i = 1; i < n; i++) {
		mod = (mod + 1) % 3;
		partCost[i] = partCost[i-1] + !(rgb[mod] == s[i]);
	}

	int answ = partCost[k - 1];
	for (int i = 1; i + k <= n; i++) {
		int cur = partCost[i + k - 1] - partCost[i - 1];
		if (cur < answ) { answ = cur; }
	}
	return answ;
}

int main() {
	int q;
	cin >> q;

	for (int z = 0; z < q; z++) {
		cin >> n >> k;
		cin >> s;

		int res = minCost(0);
		int c2 = minCost(1);
		if (res > c2) { res = c2; }
		int c3 = minCost(2);
		if (res > c3) { res = c3; }

		cout << res << endl;
	}
}
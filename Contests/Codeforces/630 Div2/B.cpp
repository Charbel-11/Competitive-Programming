#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <cmath>
#include <algorithm>
#include <map>

using namespace std;

vector<int> spf;
void primeFactors(int n) {
	if (n < 1) { return; }
	spf.resize(n, -1);
	spf[0] = 0; spf[1] = 1;

	for (int i = 2; i < n; i++) {
		if (spf[i] != -1) { continue; }
		spf[i] = i;
		for (int j = i * i; j < n; j += i) {		//start at 2*i to get all prime factors
			if (spf[j] == -1) { spf[j] = i; }
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	primeFactors(1005);
	int t; cin >> t;
	
	map<int, int> m;
	int count = 1, i = 2;
	while (count <= 11) {
		if (spf[i] == i) { m[i] = count++; }
		i++;
	}

	while (t--) {
		int n; cin >> n;
		set<int> used;
		vector<int> ans(n);
		for (int i = 0; i < n; i++) {
			int cur; cin >> cur;
			ans[i] = m[spf[cur]];
			used.insert(ans[i]);
		}

		map<int, int> finalMap;
		int count = 1;
		for (auto &el : used) {
			finalMap[el] = count++;
		}

		cout << count - 1 << endl;
		for (auto &x : ans) { cout << finalMap[x] << " "; }
		cout << endl;
	}
}
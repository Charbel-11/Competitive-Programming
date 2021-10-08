#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;
const int SVSZ = 300009;

int spf[SVSZ]; //Smallest Prime Factor
vector<int> primes;

void buildSieve() {
	vector<int> primes; spf[0] = spf[1] = 1;
	for (int i = 2; i < SVSZ; i++) {
		if (spf[i] == 0) { primes.push_back(i);	spf[i] = i; }
		for (int j = 0; j < int(primes.size()) && primes[j] <= spf[i] && i * primes[j] < SVSZ; j++)
			spf[i * primes[j]] = primes[j];
	}
}

//Iterates over all divisors
void getDivisorsHelper(int i, int curr, vector<int>& divisors, vector<pair<int, int>>& v) {
	if (i == (int)v.size()) { divisors.push_back(curr); return; }
	getDivisorsHelper(i + 1, curr, divisors, v);
	for (int j = 0; j < v[i].second; j++) {
		curr *= v[i].first;
		getDivisorsHelper(i + 1, curr, divisors, v);
	}
}

//Prime factorization
vector<int> getDivisors(int x) {
	vector<pair<int, int>> v;
	while (x > 1) {
		int d = spf[x], cnt = 0;
		while (x % d == 0) { x /= d; cnt++; }
		v.push_back({ d, cnt });
	}
	vector<int> divisors;
	getDivisorsHelper(0, 1, divisors, v);
	return divisors;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	buildSieve();

	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		char c; cin >> c;
		string s; cin >> s;

		bool allEq = true;
		for (int i = 0; i < n; i++) {
			if (s[i] != c) { allEq = false; break; }
		}
		if (allEq) { cout << 0 << '\n'; continue; }

		int ans = -1;
		vector<bool> canBeUsed(n + 1, true);	
		for (int i = n; i >= 1; i--) {
			if (s[i - 1] != c) {
				vector<int> curDiv = getDivisors(i);
				for (auto& d : curDiv) { canBeUsed[d] = false; }
			}
			else if (canBeUsed[i]){ ans = i; break; }
		}

		if (ans != -1) {
			cout << 1 << '\n';
			cout << ans << '\n';
		}
		else {
			cout << 2 << '\n';
			cout << n << " " << n - 1 << '\n';
		}
	}
}
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;
const int SVSZ = 1000009;
int spf[SVSZ]; //Smallest Prime Factor

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

	vector<int> mex(SVSZ, 0);
	buildSieve();

	for (int i = 2; i < SVSZ; i++) {
		set<int> moves;

		vector<int> curDiv = getDivisors(i);
		for (auto& d : curDiv) { 
			if (d == 1) { continue; }
			
			if (d % 2 == 0) { moves.insert(0); }
			else { moves.insert(mex[i / d]); }
		}

		int curMex = 0;
		while (moves.count(curMex)) { curMex++; }
		mex[i] = curMex;
	}

	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		vector<int> h(n); for (auto& x : h) { cin >> x; }

		int ans = 0;
		for (int i = 0; i < n; i++) {
			ans ^= mex[h[i]];
		}

		if (ans > 0) { cout << 1 << '\n'; }
		else { cout << 2 << '\n'; }
	}
}
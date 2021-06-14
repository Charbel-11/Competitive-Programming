#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

ll power(ll x, ll p, ll mod) {
	x %= mod; ll res = 1;
	for (; p; p >>= 1, x = (x * x) % mod)
		if (p & 1) res = (res * x) % mod;
	return res;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	ll A, B, C; cin >> A >> B >> C;
	A %= 10;

	set<int> seen; vector<int> cycle;
	int cur = A;
	while(true) {
		if (seen.count(cur)) { break; }
		seen.insert(cur); cycle.push_back(cur);
		cur *= A; cur %= 10;
	}

	int n = seen.size();
	int p = power(B, C, n);
	if (p == 0) { cout << cycle[n - 1] << '\n'; }
	else { cout << cycle[p - 1] << '\n'; }
}
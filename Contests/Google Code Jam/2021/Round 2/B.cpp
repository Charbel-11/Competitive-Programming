#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;
const int SVSZ = 1000009;

int spf[SVSZ]; //Smallest Prime Factor
vector<int> primes;
vector<int> dp, help;

void buildSieve() {
	vector<int> primes; spf[0] = spf[1] = 1;
	for (int i = 2; i < SVSZ; i++) {
		if (spf[i] == 0) { primes.push_back(i);	spf[i] = i; }
		for (int j = 0; j < int(primes.size()) && primes[j] <= spf[i] && i * primes[j] < SVSZ; j++)
			spf[i * primes[j]] = primes[j];
	}
}


//Iterates over all divisors
void getDivisorsHelper(int x, int i, int curr, vector<pair<int, int>>& v) {
	if (i == (int)v.size()) {
		if (curr == 1 || curr == x) { return; }
		help[x] = max(help[x], help[x / curr - 1] + 1);
		if (curr == 2) { return; }
		dp[x] = max(dp[x], help[x / curr - 1] + 1);
		return;
	}
	getDivisorsHelper(x, i + 1, curr, v);
	for (int j = 0; j < v[i].second; j++) {
		curr *= v[i].first;
		getDivisorsHelper(x, i + 1, curr, v);
	}
}

//Prime factorization
void getDivisors(int x, vector<int>& dp) {
	int num = x;
	vector<pair<int, int>> v;
	while (x > 1) {
		int d = spf[x], cnt = 0;
		while (x % d == 0) { x /= d; cnt++; }
		v.push_back({ d, cnt });
	}
	getDivisorsHelper(num, 0, 1, v);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	buildSieve();
	dp.resize(SVSZ, 1); 
	help.resize(SVSZ, 1); 
	dp[0] = dp[1] = dp[2] = 0;
	help[1] = help[0] = 0;

	for (int i = 3; i <= SVSZ - 1; i++) {
		getDivisors(i, dp);
	}

	int t; cin >> t;
	for (int qq = 1; qq <= t; qq++) {
		int N; cin >> N;
		cout << "Case #" << qq << ": " << dp[N] << '\n';
	}
}

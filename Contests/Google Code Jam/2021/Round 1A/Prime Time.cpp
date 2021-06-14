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
const int SVSZ = 100009;
int spf[SVSZ]; //Smallest Prime Factor

void buildSieve() {
	vector<int> primes; spf[0] = spf[1] = 1;
	for (int i = 2; i < SVSZ; i++) {
		if (spf[i] == 0) { primes.push_back(i);	spf[i] = i; }
		for (int j = 0; j < int(primes.size()) && primes[j] <= spf[i] && i * primes[j] < SVSZ; j++)
			spf[i * primes[j]] = primes[j];
	}
}

vector<pair<int, int>> getDivisors(int x) {
	vector<pair<int, int>> v;
	while (x > 1) {
		int d = spf[x], cnt = 0;
		while (x % d == 0) { x /= d; cnt++; }
		v.push_back({ d, cnt });
	}
	return move(v);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	buildSieve();
	int t; cin >> t;
	for (int qq = 1; qq <= t; qq++) {
		int M; cin >> M;
		vector<ll> primeFreq(500, 0); ll s = 0;
		for (int i = 0; i < M; i++) {
			int p; ll N; cin >> p >> N;
			primeFreq[p] = N;
			s += N * p;
		}

		ll ans = 0;
		for (int k = SVSZ - 1; k >= 0; k--) {
			vector<pair<int, int>> div = getDivisors(k);

			ll curS = s; bool OK = true;
			for (auto& p : div) {
				if (p.first >= 500 || p.second > primeFreq[p.first]) { OK = false; break; }
				curS -= p.second * p.first;
			}

			if (OK && curS == k) { ans = k; break; }
		}

		cout << "Case #" << qq << ": " << ans << '\n';
	}
}
// https://www.hackerearth.com/problem/algorithm/mancunian-and-factorization-game-b8794702/

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
typedef long long ll;
const int SVSZ = 1000009;

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

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	buildSieve();

	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		unordered_map<int, int> freq;
		for (int i = 0; i < n; i++) {
			int cur; cin >> cur;
			while (cur > 1) {
				int d = spf[cur], cnt = 0;
				while (cur % d == 0) { cur /= d; cnt++; }
				freq[d] += cnt;
			}
		}

		int GN = 0;
		for (auto& p : freq) { GN ^= p.second; }
		if (GN > 0) { cout << "Mancunian" << '\n'; }
		else { cout << "Liverbird" << '\n'; }
	}
}
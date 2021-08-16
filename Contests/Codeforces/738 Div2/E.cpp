#include <iostream>
#include <vector>
#include <numeric>
using namespace std;
typedef long long ll;
const ll mod = 998244353;

const int SVSZ = 100009;
typedef int(*func_ptr) (int&, int&, int&);

int spf[SVSZ]; //Smallest Prime Factor
int hpp[SVSZ]; //Highest Power of spf
int hpc[SVSZ]; //Highest Power Count of spf
int func[SVSZ];//Multiplicative Function
vector<int> primes; int ONE = 1;

int mobius(int& HPP, int& HPC, int& SPF) { return (HPC == 0) - (HPC == 1); }

void buildSieveMult(func_ptr Mult) { //Computes a multiplicative function over a range in O(n)
	spf[0] = spf[1] = hpp[1] = func[1] = 1; //Initial Values
	hpp[0] = hpc[0] = hpc[1] = func[0] = 0; //Initial Values

	for (int i = 2; i < SVSZ; i++) {
		if (spf[i] == 0) { //i is Prime
			primes.push_back(i); spf[i] = i;
			func[i] = Mult(i, ONE, i); hpp[i] = i; hpc[i] = 1;
		}
		for (int j = 0; j < (int)primes.size() && i * primes[j] < SVSZ; j++) {
			spf[i * primes[j]] = primes[j];
			if (i % primes[j]) { //primes[j] < spf[i]
				func[i * primes[j]] = func[i] * func[primes[j]];
				hpp[i * primes[j]] = primes[j]; hpc[i * primes[j]] = 1;
			}
			else { //primes[j] == spf[i]
				hpp[i * primes[j]] = primes[j] * hpp[i]; hpc[i * primes[j]] = 1 + hpc[i];
				func[i * primes[j]] = func[i / hpp[i]] * Mult(hpp[i * primes[j]], hpc[i * primes[j]], primes[j]);
				break;
			}
		}
	}
}

ll findNumWays(int n, int m, vector<pair<int, int>>& bounds) {
	vector<ll> dp(m + 2, 0); dp[0] = 1;

	for (int i = 0; i < n; i++) {
		vector<ll> curDP(m + 2, 0);
		for (int j = 0; j <= m; j++) {
			int newL = bounds[i].first + j, newR = bounds[i].second + j;
			if (newL > m) { break; }
			newR = min(newR, m);

			curDP[newL] += dp[j]; curDP[newL] %= mod;
			curDP[newR + 1] -= dp[j]; curDP[newR + 1] %= mod;
		}

		for (int i = 1; i <= m + 1; i++) { curDP[i] += curDP[i - 1]; curDP[i] %= mod; }
		dp = curDP;
	}

	ll ans = 0;
	for (int i = 0; i <= m; i++) { ans += dp[i]; ans %= mod; }
	return ans;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
	vector<pair<int, int>> bounds(n);
	for (auto& p : bounds) { cin >> p.first >> p.second; }
	buildSieveMult(mobius);

	ll ans = 0;
	for (int d = 1; d <= m; d++) {
		if (func[d] == 0) { continue; }

		vector<pair<int, int>> curBounds(n);
		for (int i = 0; i < n; i++) {
			curBounds[i].first = (bounds[i].first + d - 1) / d;
			curBounds[i].second = bounds[i].second / d;
		}

		ll cur = findNumWays(n, m/d, curBounds) * func[d]; cur %= mod;
		ans += cur; ans %= mod;
	}

	if (ans < 0) { ans += mod; }
	cout << ans << '\n';
}
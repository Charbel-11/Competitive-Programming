#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

const ll mod = 998244353;

ll dp[52][52][52];
ll choose[52][52];

// fast exponentiation modulo mod
ll powe(ll x, ll p) {
	ll res = 1;
	for (; p; p >>= 1, x = (x * x) % mod) {
		if (p & 1) { res = (res * x) % mod; }
	}
	return res;
}
// modular inverse (mod must be prime)
ll modinv(ll i) { return powe(i, mod - 2); }

void buildChoose() {
	int limit = 52;
	for (int i = 0; i < limit; i++) { choose[i][i] = 1; choose[i][0] = 1; }
	for (int i = 1; i < limit; i++)
		for (int j = 1; j < i; j++)
			choose[i][j] = (choose[i - 1][j - 1] + choose[i - 1][j]) % mod;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int N, M, K; cin >> N >> M >> K;
	vector<ll> p(N); ll S = 0;
	for (auto& x : p) { cin >> x;  S += x; }
	S = modinv(S);
	for (auto& x : p) { x = (x * S) % mod; }

	buildChoose(); 
	for (int k = 0; k <= N; k++) { dp[k][0][0] = 1; }

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			for (int k = j; k <= K; k++) {
				dp[i][j][k] = dp[i - 1][j][k];
				ll curPi = p[i - 1];
				for (int curFreq = 1; curFreq <= k; curFreq++) {
					ll curProb = (dp[i - 1][j - 1][k - curFreq] * curPi) % mod;
					curProb *= choose[k][curFreq]; curProb %= mod;

					dp[i][j][k] += curProb; dp[i][j][k] %= mod;
					curPi *= p[i - 1]; curPi %= mod;
				}
			}
		}
	}

	cout << dp[N][M][K] << '\n';
}
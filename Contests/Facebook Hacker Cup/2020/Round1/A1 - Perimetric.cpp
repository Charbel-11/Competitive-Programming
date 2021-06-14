#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <fstream>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;
const ll mod = 1000 * 1000 * 1000 + 7;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	ifstream ifs("input.txt");
	ofstream ofs("out.txt");

	int t; ifs >> t;

	for (int qq = 1; qq <= t; qq++) {
		int N, K, W; ifs >> N >> K >> W;

		vector<ll> L(N), H(N);
		for (int i = 0; i < K; i++) { ifs >> L[i]; }
		ll AL, BL, CL, DL; ifs >> AL >> BL >> CL >> DL;
		for (int i = K; i < N; i++) {
			ll cur = AL * L[i - 2]; cur %= DL;
			cur = cur + (BL*L[i - 1]) % DL; cur %= DL;
			cur += CL; cur %= DL;
			cur++; L[i] = cur;
		}

		for (int i = 0; i < K; i++) { ifs >> H[i]; }
		ll AH, BH, CH, DH; ifs >> AH >> BH >> CH >> DH;
		for (int i = K; i < N; i++) {
			ll cur = AH * H[i - 2]; cur %= DH;
			cur = cur + (BH*H[i - 1]) % DH; cur %= DH;
			cur += CH; cur %= DH;
			cur++; H[i] = cur;
		}

		vector<ll> P(N, 1), dp(N, -1);
		P[0] = H[0] * 2 + W * 2; P[0] %= mod;

		for (int i = 1; i < N; i++) {
			if (L[i] > L[i - 1] + W) {
				ll add = 2 * H[i] + 2 * W; add %= mod;
				P[i] = P[i - 1] + add; P[i] %= mod;
				continue;
			}

			ll add = 2 * (L[i] - L[i - 1]);
			int j = i - 1;
			while (H[j] <= H[i]) {	//need 1st strictly bigger to avoid n^2
				if (dp[j] == -1 || (L[i] - L[dp[j]] > W)) { break; }	//j gives the biggest in range
				j = dp[j];
			}
			if (H[j] < H[i]) { add += ((H[i] - H[j]) * 2); add %= mod; }
			P[i] = P[i - 1] + add; P[i] %= mod;

			if (H[j] <= H[i]) { dp[i] = -1; }
			else { dp[i] = j; }
		}

		ll ans = 1;
		for (int i = 0; i < N; i++) { ans *= P[i]; ans %= mod; }
		ofs << "Case #" << qq << ": " << ans << '\n';
	}
}
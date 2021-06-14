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
		int N, K; ifs >> N >> K;

		vector<ll> L(N), W(N), H(N);
		for (int i = 0; i < K; i++) { ifs >> L[i]; }
		ll AL, BL, CL, DL; ifs >> AL >> BL >> CL >> DL;
		for (int i = K; i < N; i++) {
			ll cur = AL * L[i - 2]; cur %= DL;
			cur = cur + (BL*L[i - 1]) % DL; cur %= DL;
			cur += CL; cur %= DL;
			cur++; L[i] = cur;
		}

		for (int i = 0; i < K; i++) { ifs >> W[i]; }
		ll AW, BW, CW, DW; ifs >> AW >> BW >> CW >> DW;
		for (int i = K; i < N; i++) {
			ll cur = AW * W[i - 2]; cur %= DW;
			cur = cur + (BW*W[i - 1]) % DW; cur %= DW;
			cur += CW; cur %= DW;
			cur++; W[i] = cur;
		}

		for (int i = 0; i < K; i++) { ifs >> H[i]; }
		ll AH, BH, CH, DH; ifs >> AH >> BH >> CH >> DH;
		for (int i = K; i < N; i++) {
			ll cur = AH * H[i - 2]; cur %= DH;
			cur = cur + (BH*H[i - 1]) % DH; cur %= DH;
			cur += CH; cur %= DH;
			cur++; H[i] = cur;
		}

		vector<ll> P(N, 0);
		
		map<ll, ll> m;
		for (int i = 0; i < N; i++) {
			ll add = 0;
			int l = L[i], r = L[i] + W[i];
			int newL = l, newR = r;
			int curL = l;

			auto it = m.upper_bound(l);
			if (m.empty() || it == m.begin() || prev(it)->second < l) {
				add = H[i]; 
			}
			else {
				it--;
				if (it->second >= r) { P[i] = P[i - 1]; continue; }
				add = -H[i]; curL = it->second;
				newL = it->first; m.erase(it);
			}

			while (curL < r) {
				it = m.lower_bound(curL);
				if (it == m.end() || it->first > r) { add += (r - curL) * 2 + H[i]; add %= mod; break; }

				add += (it->first - curL) * 2;
				add -= H[i]; add %= mod;
				curL = it->second;

				if (it->second < r) { add -= H[i]; }
				else { newR = it->second; }
				m.erase(it);
			}
			
			m[newL] = newR;

			P[i] = (i ? P[i - 1] : 0) + add; P[i] %= mod;
			while (P[i] < 0) { P[i] += mod; }
		}

		ll ans = 1;
		for (int i = 0; i < N; i++) { ans *= P[i]; ans %= mod; }
		ofs << "Case #" << qq << ": " << ans << '\n';
	}
}
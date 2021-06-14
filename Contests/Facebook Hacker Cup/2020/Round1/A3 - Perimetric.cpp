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

		map<ll, pair<ll, ll>> m;	//L->R,H
		for (int i = 0; i < N; i++) {
			ll add = H[i] * 2 + W[i] * 2; add %= mod;
			int l = L[i], r = L[i] + W[i];
			ll curL = l, curH = 0;

			auto it = m.upper_bound(l);
			if (!(m.empty() || it == m.begin() || prev(it)->second.first < l)) {
				it--;
				ll foundL = it->first, foundR = it->second.first, foundH = it->second.second;
				
				if (it != m.begin()) {
					auto it2 = prev(it);
					ll prevL = it2->first, prevR = it2->second.first, prevH = it2->second.second;
					if (prevR == foundL && prevR == l && prevH > foundH) {
						add -= 2 * (prevH - foundH); add %= mod;
					}
				}
				
				if (foundR != l) { m.erase(it); m.insert({ foundL, {l, foundH} }); }
				if (foundR > r) {
					m.insert({ r, {foundR, foundH} });
					add = add - (r - l) * 2 - foundH * 2; add %= mod;
				}
				else {
					add = add - (2 * foundH + 2 * (foundR - l)); add %= mod;
				}

				curL = foundR; curH = foundH;
			}

			while (curL < r) {
				it = m.lower_bound(curL);
				if (it == m.end() || it->first > r) { break; }
				ll foundL = it->first, foundR = it->second.first, foundH = it->second.second;

				if (foundL == curL) { add += 2 * min(foundH, curH); add %= mod; }
				if (foundR <= r) { add -= (foundH * 2 + (foundR - foundL) * 2); add %= mod; }

				m.erase(it);
				if (foundR > r) {
					m.insert({ r, {foundR, foundH} }); 
					add = add - (r - foundL) * 2 - foundH * 2; add %= mod;
				}

				curL = foundR; curH = foundH;
			}
			
			if (curL == r) {
				it = m.lower_bound(curL);
				if (!(it == m.end() || it->first > r)) {
					if (it->first == curL && it->second.second > curH) { add -= 2 * (it->second.second - curH); add %= mod; }
				}
			}

			m[l] = { r,H[i] };

			P[i] = (i ? P[i - 1] : 0) + add; P[i] %= mod;
			while (P[i] < 0) { P[i] += mod; }
		}

		ll ans = 1;
		for (int i = 0; i < N; i++) { ans *= P[i]; ans %= mod; }
		ofs << "Case #" << qq << ": " << ans << '\n';
	}
}
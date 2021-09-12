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
const ll mod = 1000000007;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	ifstream ifs("in.txt");
	ofstream ofs("out.txt");

	int t; ifs >> t;
	for (int qq = 1; qq <= t; qq++) {
		int n; ifs >> n;
		string s; ifs >> s;

		int posO = -1, posX = -1;
		for (int i = 0; i < n; i++) {
			if (s[i] == 'O' && posO == -1) { posO = i; }
			if (s[i] == 'X' && posX == -1) { posX = i; }
		}
		if (posO < posX) {
			for (int i = 0; i < n; i++) {
				if (s[i] == 'O') { s[i] = 'X'; }
				else if (s[i] == 'X') { s[i] = 'O'; }
			}
		}

		ll ans = 0, ansLastO = 0, ansLastX = 0, curLen = 0;
		ll lastX = -1, lastO = -1, firstO = -1, firstX = -1;
		ll prefValSum = 0, prefValLastO = 0, prefValLastX = 0;

		for (int r = 0; r < n; r++) {
			if (s[r] == 'F') {
				if (lastX > lastO) { ans += ansLastX; prefValSum += prefValLastX; }
				else { ans += ansLastO; prefValSum += prefValLastO; }
				curLen++; curLen %= mod; ans %= mod; prefValSum %= mod;
			}
			else if (s[r] == 'O') {
				ansLastO = ansLastX + lastX + 1; ansLastO %= mod;
				ans += ansLastO; lastO = curLen;
				if (firstO == -1) { firstO = curLen; }

				if (lastX != -1) { prefValLastO = prefValLastX + 1; }
				prefValSum += prefValLastO; prefValSum %= mod;
				curLen++; curLen %= mod; ans %= mod;
			}
			else if (s[r] == 'X') {
				ansLastX = ansLastO + lastO + 1; ansLastX %= mod;
				ans += ansLastX; lastX = curLen;
				if (firstX == -1) { firstX = curLen; }

				if (lastO != -1) { prefValLastX = prefValLastO + 1; }
				prefValSum += prefValLastX; prefValSum %= mod;
				curLen++; curLen %= mod; ans %= mod;
			}
			else {
				if (firstX != -1 && firstO != -1) {
					ll add = (ans + ((curLen * prefValSum) % mod)) % mod;
					ll curToAdd = (ansLastO + lastO + 1) * (curLen - firstX); curToAdd %= mod;
					if (curToAdd < 0) { curToAdd += mod; }
					add += curToAdd; add %= mod;

					ll prefF = firstX;
					if (lastX > lastO) { add = (add + ((prefF * ansLastX) % mod)) % mod; }
					else { add = (add + ((prefF * ansLastO) % mod)) % mod; }

					curToAdd = (curLen - firstX) * (prefValLastO + 1);  curToAdd %= mod;
					if (curToAdd < 0) { curToAdd += mod; }
					prefValSum = prefValSum * 2 + curToAdd; prefValSum %= mod;
					if (lastX > lastO) { prefValSum = (prefValSum + ((prefF * prefValLastX) % mod) % mod); }
					else { prefValSum = (prefValSum + ((prefF * prefValLastO) % mod) % mod); }

					ansLastX = ansLastX + ansLastO + lastO + 1 + prefValLastX * curLen; ansLastX %= mod;
					ansLastO = ansLastO * 2 + lastO + 1 + prefValLastO * curLen; ansLastO %= mod;
					prefValLastX = prefValLastX + prefValLastO + 1; prefValLastX %= mod;
					prefValLastO = prefValLastO * 2 + 1; prefValLastO %= mod;

					ans += add; ans %= mod;
				}

				if (lastX != -1) { lastX += curLen; lastX %= mod; }
				if (lastO != -1) { lastO += curLen; lastO %= mod; }
				curLen *= 2; curLen %= mod;
			}
		}

		ofs << "Case #" << qq << ": " << ans << '\n';
	}
}
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

struct tower {
	int w, s; ll v;
	tower(int _w, int _s, ll _v) :w(_w), s(_s), v(_v) {}

	bool operator<(const tower& rhs) const {
		return s + w < rhs.s + rhs.w;
	}
};

ll dp[10005];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	vector<tower> towers;
	for (int i = 0; i < n; i++) {
		int w, s; ll v;
		cin >> w >> s >> v;
		towers.push_back(tower(w, s, v));
	}
	sort(towers.begin(), towers.end());

	ll ans = 0;
	for (int i = 0; i < n; i++) {
		for (int j = towers[i].s; j >= 0; j--) {
			ans = max(ans, dp[j] + towers[i].v);
			if (j + towers[i].w < 1e4 + 4) { dp[j + towers[i].w] = max(dp[j + towers[i].w], dp[j] + towers[i].v); }
		}
	}

	cout << ans << '\n';
}
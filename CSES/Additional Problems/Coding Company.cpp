#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;

ll dp1[101][10002], dp2[101][10002];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, x; cin >> n >> x;
	vector<int> skill(n); for (auto& x : skill) { cin >> x; }
	sort(skill.begin(), skill.end());

	dp1[0][5000] = 1;	//shift evrthg by 5k
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			for (int curX = 0; curX <= 10000; curX++)
				dp2[j][curX] = 0;
		for (int j = 0; j < n; j++) {
			for (int curX = 0; curX <= 10000; curX++) {
				if (!dp1[j][curX]) { continue; }
				dp2[j][curX] += dp1[j][curX]; dp2[j][curX] %= mod;
				dp2[j][curX] += dp1[j][curX] * j; dp2[j][curX] %= mod;
				dp2[j + 1][curX - skill[i]] += dp1[j][curX]; dp2[j + 1][curX - skill[i]] %= mod;
				if (j) { dp2[j - 1][curX + skill[i]] += dp1[j][curX] * j; dp2[j - 1][curX + skill[i]] %= mod; }
			}
		}
		swap(dp1, dp2);
	}

	ll ans = 0;
	for (int j = 5000; j <= 5000 + x; j++) {
		ans += dp1[0][j]; ans %= mod;
	}
	cout << ans << '\n';
}
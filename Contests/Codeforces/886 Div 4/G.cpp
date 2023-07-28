#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while(t--){
		int n; cin >> n;
        map<int, ll> xs, ys, shiftedPts1, shiftedPts2;
        vector<pair<int, int>> pts(n);
        for(auto &p : pts){
            cin >> p.first >> p.second;
            xs[p.first]++;
            ys[p.second]++;

            shiftedPts1[p.second - p.first]++;
            shiftedPts2[p.second + p.first]++;
        }

        ll ans = 0;
        for(auto &p : pts){
            ans += xs[p.first] - 1;
            ans += ys[p.second] - 1;
            ans += shiftedPts1[p.second - p.first] - 1;
            ans += shiftedPts2[p.second + p.first] - 1;
        }

        cout << ans << '\n';
	}
}
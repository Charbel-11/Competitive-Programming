#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while(t--){
		ll m, k, a1, ak; cin >> m >> k >> a1 >> ak;

        ll curAchievable = 0;
        if(ak * k >= m){ curAchievable = k * (m/k); }
        else{curAchievable = ak*k; }

        if (curAchievable + a1 >= m){ cout << 0 << '\n'; continue; }
        else{
            ll left = m - (curAchievable + a1);
            ll ans = left/k + (left%k);

            ll joker = k - (left%k);
            if (a1 >= joker){
                left += joker;
                ans = min(ans, left/k + (left%k));
            }

            cout << ans << '\n';
        }
	}
}
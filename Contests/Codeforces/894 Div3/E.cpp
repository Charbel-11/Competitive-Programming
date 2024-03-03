#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while(t--){
		int n, m; ll d; cin >> n >> m >> d;
        vector<ll> a(n); for(auto &x : a){ cin >> x; }

        ll ans = 0, cur = 0;
        multiset<ll> topM;
        for(int i = 0; i < n; i++){
            cur -= d;
            if (a[i] > 0){
                if (topM.size() < m){
                    cur += a[i];
                    topM.insert(a[i]);
                }
                else{
                    if (*topM.begin() < a[i]){
                        cur += a[i] - *topM.begin();
                        topM.erase(topM.begin());
                        topM.insert(a[i]);
                    }
                }
            }
            ans = max(ans, cur);
        }

        cout << ans << '\n';
	}
}
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while(t--){
		int n; cin >> n;
        vector<int> a(n); for(auto &x : a){ cin >> x; }

        ll ans = 0;
        vector<ll> curSum(n, 0);
        for(int i = 0; i < n - 1; i++){
            ll diff = abs(a[i] - a[i+1]);
            ans += diff;
            if (a[i + 1] > a[i]){
                curSum[i+1] -= diff;
            }
            else{
                curSum[0] -= diff;
                curSum[i+1] += diff;
            }
        }
        ans += abs(curSum[0] + a[0]);
        cout << ans << '\n';
	}
}
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while(t--){
		int n, k; cin >> n >> k;
        vector<int> a(n); for(auto &x : a){ cin >> x; }
        sort(a.begin(), a.end());

        int ans = n, prefRem = 0;
        for(int i = 1; i < n; i++){
            if (a[i] - a[i-1] > k){
                ans = min(ans, prefRem + n-i);
                prefRem = i;
            }
        }
        ans = min(ans, prefRem);

        cout << ans << '\n';
	}
}
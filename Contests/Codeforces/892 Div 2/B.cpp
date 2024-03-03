#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while(t--){
		int n; cin >> n;
        ll allMin = 1e9+2, sumMin2 = 0;
        vector<ll> min2;
        for(int i = 0; i < n; i++){
            int m; cin >> m;
            vector<ll> a(m); for(auto &x : a){ cin >> x; }
            sort(a.begin(), a.end());
            min2.push_back(a[1]); sumMin2 += a[1];
            allMin=min(allMin, a[0]);
        }

        sort(min2.begin(), min2.end());
        cout << sumMin2 - min2[0] + allMin << '\n';
	}
}
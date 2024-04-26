#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while(t--){
		int n; cin >> n;
        vector<int> d(n); for (auto &x : d){ cin >> x; }
        vector<int> a(n); a[0] = d[0];
        bool unique = true;
        for(int i = 1; i < n; i++){
            if (d[i] && a[i-1] - d[i] >= 0){ unique = false; break; }
            a[i] = a[i-1] + d[i];
        }

        if (!unique) { cout << -1 << '\n'; }
        else{
            for(auto &x : a){ cout << x << ' '; }
            cout << '\n';
        }
	}
}
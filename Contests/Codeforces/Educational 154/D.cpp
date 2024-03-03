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

        vector<int> sufPosCost(n, n); sufPosCost[n-1] = 0;
        for(int i = n-2; i >= 0; i--){
            if (a[i] < a[i+1]){ sufPosCost[i] = sufPosCost[i+1]; }
            else{ sufPosCost[i] = sufPosCost[i+1] + 1; }
        }

        int ans = n;
        n = a.size(); int splitNeg = 0;
        for(int i = 0; i < n; i++){
            ans = min(ans, splitNeg + sufPosCost[i]);
            if (i == 0 || a[i] >= a[i-1]){ splitNeg++; }
        }
        ans = min(ans, splitNeg);

        cout << ans << '\n';
	}
}
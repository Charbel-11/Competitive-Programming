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
        sort(a.begin(), a.end());

        int ans = 0;
        for(int k = (n+1)/2; k >= 0; k--){
            vector<int> left;
            for(int j = k-1; j < k-1+k; j++){
                left.push_back(a[j]);
            }

            bool OK = true;
            for(int j = 1; j <= k; j++){
                if (left[j-1] > j) { OK = false; break; }
            }

            if (OK){ ans = k; break; }
        }

        cout << ans << '\n';
	}
}
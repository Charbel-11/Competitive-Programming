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
        vector<int> dp(n+1, n);

        dp[0] = 1;
        for(int i = 1; i < n; i++){
            if (a[i] > i){ dp[i] = 1; continue; }

            int lastNotCovered = i-a[i];
            int curCost = 1 + dp[lastNotCovered];
            for(int j = lastNotCovered + 1; j < i; j++){
                curCost = min(curCost, 1 + dp[j]);
            }
            dp[i] = curCost;

            for(int j = i-1; j >= 0; j--){
                int len = i - j + 1;
                if (a[j] < len){ continue; }
                if (j == 0){ dp[i] = 1; break; }

                curCost = 1 + dp[j-1];

                lastNotCovered = j-1;
                for(int k = j + 1; k < i; k++){
                    lastNotCovered = min(lastNotCovered, k - a[k]);
                }
                if (lastNotCovered < 0){ curCost = min(curCost, 2); }
                else {
                    for (int k = lastNotCovered; k < j; k++) {
                        curCost = min(curCost, 2 + dp[k]);
                    }
                }
                dp[i] = min(dp[i], curCost);
            }
        }

        cout << dp[n-1] << '\n';
	}
}


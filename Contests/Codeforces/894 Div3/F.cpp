#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int t; cin >> t;
    while(t--){
        int w, f; cin >> w >> f;
        int n; cin >> n;
        int S = 0; vector<int> s(n);
        for(auto &x : s){ cin >> x; S += x; }

        if (w >= S || f >= S) { cout << 1 << '\n'; continue; }

        S += w;
        vector<int> curDP(S+1, S+1), prevDP(S+1, S+1);
        prevDP[0] = 0; int cnt = 1;
        for(int i = w; i <= S; i += w){
            prevDP[i] = cnt++;
        }

        reverse(s.begin(), s.end());
        int prefSum = 0;
        for(int i = 1; i <= n; i++){
            prefSum += s[i-1];
            for(int j = 0; j <= S; j++){
                // kill monster with w
                if (j + s[i - 1] <= S) { curDP[j] = min(curDP[j], prevDP[j + s[i - 1]]); }

                // kill monster with f
                if (prevDP[j] > S){ continue; }
                int timeSpent = prevDP[j];
                int totalF = timeSpent * f, totalW = timeSpent * w;
                int spentW = totalW - j;
                totalF -= (prefSum - spentW);
                if (totalF >= 0) { curDP[j] = min(curDP[j], prevDP[j]); }
            }
            for(int i = 0; i <= S; i++){
                prevDP[i] = curDP[i];
                curDP[i] = S+1;
            }
        }

        int ans = *min_element(prevDP.begin(), prevDP.end());
        cout << ans << '\n';
    }
}
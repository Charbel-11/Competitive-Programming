#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while(t--){
		int n, m; cin >> n >> m;
        string s; cin >> s;

        vector<int> lRanges, rRanges, noRange;
        for(int i = 0; i < n; i++){
            if (s[i] == '1') { lRanges.push_back(i + 1); }
            else{ rRanges.push_back(i - 1); }
        }
        for(int i = 1; i < n; i++) {
            if (s[i] == '0' && s[i-1] == '1'){
                noRange.push_back(i);
            }
        }
        lRanges.push_back(n);
        rRanges.push_back(n);
        noRange.push_back(n);

        bool noChange = false;
        int ans = 0;

        set<pair<int, int>> S;
        for(int i = 0; i < m; i++){
            int l, r; cin >> l >> r; l--; r--;
            int realL = upper_bound(noRange.begin(), noRange.end(), l) - noRange.begin();
            int realR = upper_bound(noRange.begin(), noRange.end(), r) - noRange.begin();
            if (realL == realR){ noChange = true; continue; }

            realL = upper_bound(lRanges.begin(), lRanges.end(), l) - lRanges.begin();
            realR = lower_bound(rRanges.begin(), rRanges.end(), r) - rRanges.begin();
            S.insert({realL, realR});
        }

        ans += S.size();
        ans += noChange;
        cout << ans << '\n';
	}
}
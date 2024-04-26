#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while(t--){
		string x; cin >> x;
        int k; cin >> k;

        vector<vector<int>> indices(10);
        for(int i = 0; i < x.size(); i++){
            indices[x[i]-'0'].push_back(i);
        }

        int curL = 0;
        string ans;
        while(k > 0){
            if (x.size() - curL == k){
                curL = x.size();
                break;
            }

            int start = (curL == 0);
            for(int d = start; d <= 9; d++){
                int dIdx = lower_bound(indices[d].begin(), indices[d].end(), curL) - indices[d].begin();
                if (dIdx == indices[d].size()){ continue; }

                dIdx = indices[d][dIdx];
                if (dIdx - curL > k){ continue; }

                k -= (dIdx-curL);
                curL = dIdx + 1;
                ans.push_back('0' + d);
                break;
            }
        }
        while(curL < x.size()){
            ans.push_back(x[curL++]);
        }

        cout << ans << '\n';
	}
}
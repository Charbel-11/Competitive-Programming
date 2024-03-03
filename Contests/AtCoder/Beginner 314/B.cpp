#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
    vector<vector<int>> bets;
    for(int i = 0; i < n; i++){
        int c; cin >> c;
        vector<int> cur(c);
        for(auto &x : cur){ cin >> x; }
        bets.push_back(cur);
    }

    int x; cin >> x;
    vector<pair<int, int>> ans;

    for(int i = 0; i < n; i++){
        for(auto &el : bets[i]){
            if (el == x){
                ans.emplace_back(bets[i].size(), i+1);
                break;
            }
        }
    }

    sort(ans.begin(), ans.end());
    vector<int> realAns;
    if (ans.size() > 0) {
        int minBet = ans[0].first;
        for (auto &p: ans) {
            if (p.first > minBet){ break; }
            realAns.push_back(p.second);
        }
    }

    cout << realAns.size() << '\n';
    for(auto &x : realAns){ cout << x << ' '; }
    cout << '\n';
}
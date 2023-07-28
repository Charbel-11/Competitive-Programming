#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
    vector<int> next(n); for(auto &x : next){ cin >> x; x--; }

    int start = -1;
    int cur = 0; set<int> seen;
    vector<int> ans; ans.push_back(0);
    while(true){
        cur = next[cur];
        if (seen.count(cur)){ start = cur; break; }
        seen.insert(cur);
        ans.push_back(cur);
    }

    for(int i = 0; i < ans.size(); i++){
        if (ans[i] == start){ start = i; break; }
    }
    cout << ans.size() - start << '\n';
    for(int i = start; i < ans.size(); i++){
        cout << ans[i] + 1 << ' ';
    }
    cout << '\n';
}
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> getDivisors(int x){
    vector<int> ans = {1, x};
    if (x == 1){ ans.pop_back(); }
    for(int d = 2; d * d <= x; d++){
        if (x % d == 0){
            ans.push_back(d);
            if (x/d != d){ ans.push_back(x/d); }
        }
    }
    return ans;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while(t--){
		int n; cin >> n;
        vector<int> a;
        for(int i = 0; i < n; i++){
            int cur; cin >> cur;
            if (cur > n){ continue; }
            a.push_back(cur);
        }

        vector<int> freq(n + 1, 0);
        for(auto &x : a){ freq[x]++; }

        int ans = 0;
        for(int i = 1; i <= n; i++){
            int curF = 0;
            auto divs = getDivisors(i);
            for (auto &x : divs){
               curF += freq[x];
            }
            ans = max(ans, curF);
        }

        cout << ans << '\n';
	}
}
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while(t--){
		int k, n; cin >> n >> k;
        vector<int> ans;
        int l = 1, r = n;
        while(l < r){
            ans.push_back(r--);
            ans.push_back(l++);
        }
        if (l == r){ ans.push_back(l); }

        for(auto &x : ans){ cout << x << ' '; }
        cout << '\n';
	}
}
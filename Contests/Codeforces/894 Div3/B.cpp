#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while(t--){
		int n; cin >> n;
        vector<int> b(n); for(auto &x : b){ cin >> x; }
        vector<int> ans; ans.push_back(b[0]);

        for(int i = 1; i < n; i++){
            if (b[i] < b[i-1]){ ans.push_back(b[i]); }
            ans.push_back(b[i]);
        }

        cout << ans.size() << '\n';
        for(auto &x : ans){ cout << x << ' '; }
        cout << '\n';
	}
}
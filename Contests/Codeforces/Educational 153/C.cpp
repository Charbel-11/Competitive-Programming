#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while(t--){
		int n; cin >> n;
        vector<int> p(n); for(auto &x : p){ cin >> x; x--; }

        vector<int> order(n);
        for(int i = 0; i < n; i++){
            order[p[i]] = i;
        }

        set<int> allNums;
        set<int> losing; int ans = 0;
        for(int i = 0; i < n; i++){
            int idx = order[i];

            auto it2 = allNums.upper_bound(idx);
            if (allNums.empty() || it2 == allNums.begin()) {
                allNums.insert(idx);
                continue;
            }
            allNums.insert(idx);

            auto it = losing.upper_bound(idx);
            if (losing.empty() || it == losing.begin()){ ans++; losing.insert(idx); continue; }
        }

        cout << ans << '\n';
	}
}
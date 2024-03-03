#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while(t--){
		int n; cin >> n;
        map<int, int> m; vector<int> a(n);
        for(auto &x : a){ cin >> x; m[x]++; }

        multiset<int> deltas; vector<int> b = a;
        sort(b.begin(), b.end());
        for(int i = 1; i < n; i++) {
            if (b[i] != b[i - 1]) { deltas.insert(b[i] - b[i - 1]); }
        }

        int q; cin >> q;
        while(q--){
            int i, x; cin >> i >> x; i--;

            m[a[i]]--;
            if (m[a[i]] == 0) {
                auto it1 = m.upper_bound(a[i]);
                auto it2 = m.lower_bound(a[i]);
                if (it1 != m.end()) { deltas.erase(deltas.find(it1->first - a[i])); }
                if (it2 != m.begin()) {
                    it2--; deltas.erase(deltas.find(a[i] - it2->first));
                    if (it1 != m.end()) { deltas.insert(it1->first - it2->first); }
                }
                m.erase(a[i]);
            }

            a[i] = x; m[x]++;
            if (m[x] == 1) {
                auto it1 = m.upper_bound(x);
                auto it2 = m.lower_bound(x);
                if (it1 != m.end()) { deltas.insert(it1->first - x); }
                if (it2 != m.begin()) {
                    it2--; deltas.insert(x - it2->first);
                    if (it1 != m.end()) { deltas.erase(deltas.find(it1->first - it2->first)); }
                }
            }

            if (deltas.empty()){ cout << m.rbegin()->first << ' '; }
            else { cout << *deltas.rbegin() + m.rbegin()->first << ' '; }
        }
        cout << '\n';
	}
}
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct portal{
    int l, r, a, b;
    portal(int _l, int _r, int _a, int _b):l(_l), r(_r), a(_a), b(_b){}
    bool operator <(const portal &RHS) const{
        return b < RHS.b;
    }
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while(t--){
		int n; cin >> n;
        vector<portal> portals;
        for(int i = 0; i < n; i++){
            int l, r, a, b; cin >> l >> r >> a >> b;
            portals.emplace_back(l, r, a, b);
        }

        map<int, int> ansB;
        multiset<pair<int, int>> dq; multiset<int> activeB;
        sort(portals.rbegin(), portals.rend());
        for(auto &p : portals){
            ansB[p.b] = max(ansB[p.b], p.b);
            while(!dq.empty() && dq.rbegin()->first > p.b){
                activeB.erase(activeB.find(dq.rbegin()->second));
                dq.erase(dq.find(*dq.rbegin()));
            }
            if (!activeB.empty()) {
                ansB[p.b] = max(ansB[p.b], ansB[*activeB.rbegin()]);
            }
            activeB.insert(p.b);
            dq.insert({p.l, p.b});
        }

        int q; cin >> q;
        vector<int> ans(q);
        vector<pair<int, int>> x(q);
        for(int qq = 0; qq < q; qq++){
            int cur; cin >> cur;
            ans[qq] = cur;
            x[qq] = {cur, qq};
        }

        int idx = 0;
        sort(x.rbegin(), x.rend());
        for(int i = 0; i < q; i++){
            int curX = x[i].first, curIdx = x[i].second;
            while (idx < n && curX < portals[idx].l){ idx++; }
            if (idx >= n){ break; }
            ans[curIdx] = max(ans[curIdx], ansB[portals[idx].b]);
        }

        for(auto &xx : ans){ cout << xx << ' '; }
        cout << '\n';
	}
}
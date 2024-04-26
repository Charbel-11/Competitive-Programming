#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
    vector<int> p(n); for(auto &x : p){ cin >> x; }

    vector<vector<int>> deps(n);
    vector<int> outDeg(n, 0);
    for(int i = 0; i < m; i++){
        int u, v; cin >> u >> v; u--; v--;
        outDeg[u]++; deps[v].push_back(u);
    }

    vector<vector<int>> pToIdx(n+1);
    for(int i = 0; i < n; i++){
        pToIdx[p[i]].push_back(i);
    }

    for(int i = 0; i < n; i++) {
        set<int> candidates;
        auto curOutDeg = outDeg;
        for(int r = n; r >= 1; r--) {
            for(auto &x : pToIdx[r]){
                if (curOutDeg[x] == 0){ candidates.insert(x); }
            }

            int c1 = *candidates.begin();
            int c2 = *candidates.rbegin();
            if (c1 == i && c2 == i) {
                cout << r << ' ';
                break;
            }
            if (c1 == i) { swap(c1, c2); }

            candidates.erase(c1);
            for (auto &x: deps[c1]) {
                curOutDeg[x]--;
                if (curOutDeg[x] == 0 && p[x] >= r){ candidates.insert(x); }
            }
        }
    }
}
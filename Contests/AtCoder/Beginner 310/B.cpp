#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
    vector<pair<int, vector<bool>>> v(n);
    for(int i = 0; i < n; i++){
        int p; cin >> p;
        vector<bool> cur(m, 0);
        int c; cin >> c;
        for(int j = 0; j < c; j++){
            int x; cin >> x; x--;
            cur[x] = true;
        }
        v[i] = {p, cur};
    }

    bool available = false;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if (i == j){ continue; }
            if (v[i].first < v[j].first) { continue; }

            int numI = 0, numJ = 0;
            bool OK = true;
            for(int k = 0; k < m; k++) {
                numI += v[i].second[k];
                numJ += v[j].second[k];
                if (v[i].second[k] && !v[j].second[k]){ OK = false; break; }
            }
            if (!OK){ continue; }

            if (v[i].first > v[j].first || numI < numJ) { available = true; break; }
        }
        if (available){ break; }
    }

    cout << (available ? "Yes" : "No") << '\n';
}
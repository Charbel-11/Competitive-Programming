#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while(t--){
		int n; cin >> n;
        vector<pair<int, int>> nodes(n);
        vector<vector<int>> edges(n);

        map<string, int> genre, writer;
        for(int i = 0; i < n; i++){
            string g, w; cin >> g >> w;
            if (!genre.contains(g)){ genre[g] = genre.size(); }
            if (!writer.contains(w)){ writer[w] = writer.size(); }

            nodes[i] = {genre[g], writer[w]};
        }

        for(int i = 0; i < n; i++){
            for(int j = i+1; j < n; j++){
                if (nodes[i].first == nodes[j].first || nodes[i].second == nodes[j].second){
                    edges[i].push_back(j);
                    edges[j].push_back(i);
                }
            }
        }

        vector<vector<bool>> dp((1<<n), vector<bool>(n));
        for(int i = 0; i < n; i++){
            dp[(1<<i)][i] = true;
        }

        for(int i = 1; i < (1<<n); i++) {
            for(int j = 0; j < n; j++) {
                if (!dp[i][j]){ continue; }
                for(auto k : edges[j]){
                    if (i & (1 << k)){ continue; }
                    int newI = i ^ (1 << k);
                    dp[newI][k] = true;
                }
            }
        }

        int ans = n-1;
        for(int i = 1; i < (1<<n); i++){
            int num1s = 0, tmp = i;
            while(tmp){
                if (tmp & 1){ num1s++; }
                tmp /= 2;
            }
            for(int j = 0; j < n; j++){
                if (dp[i][j]){ ans = min(ans, n-num1s); }
            }
        }
        cout << ans << '\n';
	}
}


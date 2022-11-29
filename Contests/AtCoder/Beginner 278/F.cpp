#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
    vector<string> S(n); for(auto &s : S){ cin >> s; }

    vector<vector<int>> dp((1<<n), vector<int>(n, -1));
    for(int m = (1<<n)-1; m > 0; m--){
        for(int last = 0; last < n; last++){
            if (!((m >> last) & 1)) { continue; }

            dp[m][last] = 0;
            for(int j = 0; j < n; j++){
                if ((m >> j) & 1){ continue; }
                if (S[last].back() != S[j][0]) { continue; }
                int nM = m ^ (1 << j);
                if (dp[nM][j] == 0){
                    dp[m][last] = 1;
                }
            }
        }
    }

    bool first = false;
    for(int i = 0; i < n; i++){
        if (dp[(1<<i)][i] == 0){
            first = true; break;
        }
    }

    cout << (first ? "First" : "Second") << '\n';
}
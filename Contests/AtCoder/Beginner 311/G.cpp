#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
    vector<vector<ll>> A(n, vector<ll>(m));
    for(auto &v : A)
        for(auto &x : v)
            cin >> x;

    ll ans = 0;
    for(int l = 0; l < m; l++){
        vector<ll> rowMin(n + 2, 310), rowSum(n + 2, 0), prefSum(n + 2, 0);
        rowMin[0] = 0;
        for(int r = l; r < m; r++){
            for(int i = 1; i <= n; i++){
                rowMin[i] = min(rowMin[i], A[i-1][r]);
                rowSum[i] += A[i-1][r];
                prefSum[i] = rowSum[i] + prefSum[i-1];
            }
            prefSum[n+1] = prefSum[n];

            vector<int> bef(n + 1, 0), after(n + 1, n + 1);
            stack<int> s; s.push(0);
            for(int i = 1; i <= n; i++){
                while(rowMin[s.top()] > rowMin[i]){
                    after[s.top()] = i;
                    s.pop();
                }
                bef[i] = s.top();
                s.push(i);
            }
            while(!s.empty()){
                after[s.top()] = n + 1;
                s.pop();
            }

            for(int i = 1; i <= n; i++){
                ll cur = rowMin[i] * (prefSum[after[i] - 1] - prefSum[bef[i]]);
                ans = max(ans, cur);
            }
        }
    }

    cout << ans << '\n';
}
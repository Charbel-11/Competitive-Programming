#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, x; cin >> n >> x;
    vector<int> h(n), s(n), k(n);
    for(auto &xx : h){ cin >> xx; }
    for(auto &xx : s){ cin >> xx; }
    for(auto &xx : k){ cin >> xx; }

    vector<int> prevDP(x+1, 0), curDP(x+1, 0);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < min(x, h[i]); j++){
            curDP[j] = prevDP[j];
            deque<pair<int, int>> dq; dq.emplace_back(prevDP[j], j);
            for(int kk = j + h[i]; kk <= x; kk += h[i]){
                while(!dq.empty() && dq.back().first + (kk - dq.back().second)/h[i] * s[i] <= prevDP[kk]){
                    dq.pop_back();
                }
                dq.emplace_back(prevDP[kk], kk);
                if ((kk - dq.front().second)/h[i] > k[i]){ dq.pop_front(); }

                int curVal = dq.front().first + (kk - dq.front().second)/h[i] * s[i];
                curDP[kk] = curVal;
            }
        }
        swap(prevDP, curDP);
    }

    cout << prevDP[x] << '\n';
}
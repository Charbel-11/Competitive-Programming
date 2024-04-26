#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

    int r, s, m, d, n; cin >> r >> s >> m >> d >> n;
    vector<ll> brands(r); for(auto &x : brands){ cin >> x; }

    vector<vector<int>> dishes;
    for(int i = 0; i < s + m + d; i++){
        int k; cin >> k;
        vector<int> curDish(k);
        for(auto &x : curDish){ cin >> x; x--; }
        dishes.push_back(curDish);
    }

    set<pair<int, int>> incompatible;
    for(int i = 0; i < n; i++){
        int u, v; cin >> u >> v; u--; v--;
        incompatible.insert({u, v});
        incompatible.insert({v, u});
    }

    ll limit = 1e18, ans = 0;
    bool tooMany = false;
    for(int c1 = 0; c1 < s; c1++){
        for(int c2 = s; c2 < s + m; c2++){
            for(int c3 = s + m; c3 < s + m + d; c3++){
                if (incompatible.contains({c1, c2}) || incompatible.contains({c1, c3}) || incompatible.contains({c2, c3})){
                    continue;
                }

                set<int> curDishes;
                for(auto x : dishes[c1]){ curDishes.insert(x); }
                for(auto x : dishes[c2]){ curDishes.insert(x); }
                for(auto x : dishes[c3]){ curDishes.insert(x); }

                ll curWays = 1;
                for(auto x : curDishes){
                    if (to_string(curWays).size() + to_string(brands[x]).size() - 1 > 18
                    || curWays * brands[x] > limit){
                        tooMany = true; break;
                    }
                    curWays *= brands[x];
                }
                if (curWays + ans > limit){ tooMany = true; break; }
                else{ ans += curWays; }
            }
        }
    }

    if (tooMany){ cout << "too many\n"; }
    else{ cout << ans << '\n'; }
}

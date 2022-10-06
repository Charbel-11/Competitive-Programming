#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct seed{
    ll n, daysNeeded, val;
    seed(ll q, ll l, ll v) : n(q), daysNeeded(l), val(v){}

    bool operator<(const seed& rhs){
        return daysNeeded < rhs.daysNeeded;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int t; cin >> t;
    for (int qq = 1; qq <= t; qq++) {
        ll D, N, X; cin >> D >> N >> X;

        vector<seed> seeds;
        for(int i = 0; i < N; i++){
            ll q, l, v; cin >> q >> l >> v;
            if (l != D) seeds.emplace_back(q, l, v);
        }
        seeds.emplace_back(0, D, 0);
        N = seeds.size();
        sort(seeds.begin(), seeds.end());

        ll ans = 0; int i = 0;
        map<ll, ll> curSeeds;
        while (i < N - 1){
            ll curTime = seeds[i].daysNeeded;
            while (i < N && seeds[i].daysNeeded == curTime){
                curSeeds[seeds[i].val] += seeds[i].n;
                i++;
            }
            ll availableTime = X * (seeds[i].daysNeeded - curTime);

            while(availableTime > 0 && !curSeeds.empty()){
                auto best = prev(curSeeds.end());
                ll curAvailable = min(availableTime, best->second);
                ans += curAvailable * best->first;
                best->second -= curAvailable;
                availableTime -= curAvailable;
                if (best->second == 0){ curSeeds.erase(best); }
            }
        }

        cout << "Case #" << qq << ": " << ans << '\n';
    }
}

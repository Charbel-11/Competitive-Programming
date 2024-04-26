#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
    vector<long double> p(4); for(auto &x : p){ cin >> x; }

    vector<ll> fact(n + 1); fact[0] = 1;
    for(int i = 1; i <= n; i++){ fact[i] = fact[i-1] * i; }

    map<double, ll> probCnt;
    for(int w1 = 0; w1 <= n; w1++){
        for(int w2 = 0; w2 + w1 <= n; w2++){
            for(int w3 = 0; w3 + w2 + w1 <= n; w3++){
                int w4 = n-w1-w2-w3; long double curProb = 1;
                for(int i = 0; i < w1; i++){ curProb *= p[0]; }
                for(int i = 0; i < w2; i++){ curProb *= p[1]; }
                for(int i = 0; i < w3; i++){ curProb *= p[2]; }
                for(int i = 0; i < w4; i++){ curProb *= p[3]; }

                ll curCnt = fact[n] / fact[w1] / fact[w2] / fact[w3] / fact[w4];
                probCnt[curProb] += curCnt;
            }
        }
    }

    long double ans = 0;
    while(probCnt.size() > 1 || probCnt.begin()->second > 1){
        auto [curP, curCnt] = *probCnt.begin();
        probCnt.erase(probCnt.begin());

        ll contribution = 2*(curCnt/2ll);
        ans += curP * contribution;
        bool isOdd = (curCnt % 2) == 1;

        if (curCnt/2ll != 0) { probCnt[curP * 2.0] += curCnt/2ll; }
        if (isOdd){
            auto& [newMinP, newMinCnt] = *probCnt.begin();
            ans += newMinP + curP;
            probCnt[newMinP + curP] += 1;
            newMinCnt--;
            if (newMinCnt == 0){ probCnt.erase(probCnt.begin()); }
        }
    }

    cout << setprecision(6) << fixed << ans << '\n';
}


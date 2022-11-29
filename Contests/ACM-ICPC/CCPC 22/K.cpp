#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll INF = 1e14;

ll findFirstLarger(ll num, ll k){
    ll l = 1, r = num + 1;
    while(l < r){
        ll mid = (l+r)/2;
        ll prevLast = mid-1, curLast = mid + k - 1;
        ll curSum = (curLast * (curLast+1))/2 - (prevLast * (prevLast+1))/2;
        if (curSum > num){
            r = mid;
        }
        else{
            l = mid + 1;
        }
    }
    return l;
}

ll findLastSmaller(ll num, ll k){
    if (k * (k+1) / 2 >= num){ return k - 1; }

    ll l = k, r = num + 1;
    while(l < r){
        ll mid = (l+r+1)/2;
        ll prevLast = mid-k, curLast = mid;
        ll curSum = (curLast * (curLast+1))/2 - (prevLast * (prevLast+1))/2;
        if (curSum < num){
            l = mid;
        }
        else{
            r = mid - 1;
        }
    }
    return l;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while(t--){
		int n; cin >> n;

        vector<pair<ll, ll>> choices;
        ll maxL = INF, minR = 0;
        for(int i = 0; i < n; i++){
            int type; ll k, x; cin >> type >> k >> x;
            if (type == 1){
                maxL = min(maxL, findFirstLarger(x, k) - 1);
                minR = max(minR, findLastSmaller(x, k) + 1);
            }
            else{
                ll minBadL = findFirstLarger(x, k);
                ll maxBadR = findLastSmaller(x, k);
                choices.emplace_back(minBadL, maxBadR);
            }
        }

        if (maxL == INF){
            cout << -1 << '\n';
            continue;
        }
        if (maxL == 0){
            cout << 0 << '\n';
            continue;
        }

        ll ans = 0;
        sort(choices.rbegin(), choices.rend());

        ll maxR = INF;
        for(auto &p : choices){
            if (p.first > maxL){
                maxR = min(maxR, p.second);
                if (maxR < minR){ break; }
            }
            else{
                if (maxR == INF){ ans = -1; break; }
                ans += (maxL - p.first + 1) * (maxR - minR + 1);
                maxL = p.first - 1;
                maxR = min(maxR, p.second);
                if (maxR < minR){ break; }
            }
        }

        if (maxR == INF){ ans = -1; }
        if (ans != -1 && maxL >= 1 && maxR >= minR){
            ans += maxL * (maxR - minR + 1);
        }

        cout << ans << '\n';
	}
}
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while(t--){
		int n, k; cin >> n >> k;
        vector<ll> a(n); for(auto &x : a){ cin >> x; }
        vector<ll> b(k); for(auto &x : b){ cin >> x; }

        vector<vector<ll>> aBits;
        for(int i = 0; i < n; i++){
            vector<ll> curBits(32, 0);

            ll curNum = a[i];
            int bIdx = 0;
            while(curNum){
                if (curNum & 1){ curBits[bIdx]++; }
                bIdx++; curNum /= 2;
            }

            aBits.push_back(curBits);
        }

        auto check = [&](ll num){
           vector<vector<ll>> neededBits;
            for(int i = 0; i < n; i++){
                vector<ll> curBits(32, 0);
                for(int j = 0; j < 31; j++){
                    curBits[j] += aBits[i][j] * num;
                    curBits[j+1] += curBits[j]/2;
                    curBits[j] %= 2;
                }
                neededBits.push_back(curBits);
            }

            for(int j = 31; j >= 0; j--){
                ll available = 0;
                if (k > j){ available += b[j]; }

                for(int i = 0; i < n; i++){
                    if (neededBits[i][j] > 1e13){
                        return false;
                    }

                    ll mi = min(neededBits[i][j], available);
                    neededBits[i][j] -= mi;
                    available -= mi;

                    if (j){ neededBits[i][j-1] += neededBits[i][j] * 2; }
                }

                if (available == 0){ continue; }
                if (available >= n){ return true; }

                vector<pair<ll, int>> realNums;
                for(int i = 0; i < n; i++) {
                    ll curNum = 0;
                    for(int jj = j; jj >= 0; jj--){
                        curNum *= 2; curNum += neededBits[i][jj];
                    }
                    realNums.emplace_back(curNum, i);
                }
                sort(realNums.rbegin(), realNums.rend());
                for(int i = 0; i < (int)available; i++){
                    int idx = realNums[i].second;
                    for(int jj = 0; jj < j; jj++){
                        neededBits[idx][jj] = 0;
                    }
                }
            }

            for(int i = 0; i < n; i++){
                if (neededBits[i][0] > 0){ return false; }
            }

            return true;
        };

        ll l = 0, r = 3e16;
        while(l < r){
            ll mid = (l+r+1)/2;
            if (check(mid)){
                l = mid;
            }
            else{
                r = mid-1;
            }
        }

        cout << l << '\n';
	}
}
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll ans;
vector<pair<ll, ll>> U, D;
auto val(int uIdx, int dIdx){
    return (U[uIdx].first - D[dIdx].first) * (U[uIdx].second - D[dIdx].second);
}

void findMax(int lU, int rU, int lD, int rD){
    if (lU > rU || lD > rD){ return; }

    int midD = (lD + rD)/2;
    ll curMax = 0; int curMaxIdx = -1;
    for(int i = lU; i <= rU; i++){
        if (U[i].first < D[midD].first && U[i].second < D[midD].second){ continue; }
        else if (U[i].first < D[midD].first && curMax == 0) { curMaxIdx = i; continue; }
        else if (U[i].second < D[midD].second && curMaxIdx == -1){ curMaxIdx = i; continue; }
        ll curVal = val(i, midD);
        if (curVal >= curMax) {
            curMax = curVal; curMaxIdx = i;
        }
    }

    if (curMaxIdx == -1){ return; }
    ans = max(ans, curMax);
    findMax(lU, curMaxIdx, lD, midD - 1);
    findMax(curMaxIdx, rU, midD + 1, rD);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int m, n; cin >> m >> n;
    for(int i = 0; i < m; i++){
        ll p, d; cin >> p >> d;
        D.emplace_back(p, d);
    }
    sort(D.begin(), D.end());

    ll minY = 1e10;
    vector<pair<ll, ll>> goodD;
    for(auto& [x,y] : D){
        if (y >= minY){ continue; }
        minY = y; goodD.emplace_back(x, y);
    }
    swap(goodD, D);

    for(int i = 0; i < n; i++){
        ll p, d; cin >> p >> d;
        U.emplace_back(p, d);
    }
    sort(U.rbegin(), U.rend());

    ll maxY = 0;
    vector<pair<ll, ll>> goodU;
    for(auto& [x,y] : U){
        if (y <= maxY){ continue; }
        maxY = y; goodU.emplace_back(x, y);
    }
    swap(goodU, U);
    reverse(U.begin(), U.end());

    ans = 0;
    findMax(0, U.size()-1, 0, D.size()-1);
    cout << ans << '\n';
}


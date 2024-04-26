#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n; ll S = 0;
    vector<pair<ll, ll>> good, badRev;
    for(int i = 0; i < n; i++){
        ll a, b; cin >> a >> b; S += a;
        if (b >= a){ good.emplace_back(a, b); }
        else{ badRev.emplace_back(b, a); }
    }

    sort(good.begin(), good.end());
    sort(badRev.rbegin(), badRev.rend());

    auto check = [&](ll x)->bool{
        for(auto &p : good){
            if (x < p.first){ return false; }
            x += p.second - p.first;
        }

        for(auto &p : badRev){
            if (x < p.second){ return false; }
            x += p.first - p.second;
        }

        return true;
    };

    ll l = 1, r = S;
    while(l < r){
        ll mid = (l + r) / 2;
        if (check(mid)){ r = mid; }
        else{ l = mid+1; }
    }

    cout << l << '\n';
}


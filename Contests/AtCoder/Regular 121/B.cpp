#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll findMin(vector<ll>& v1, vector<ll>& v2){
	ll ans = 1e17;
	for(auto &x : v1){
		int idx = lower_bound(v2.begin(), v2.end(), x) - v2.begin();
		if (idx < v2.size()){ ans = min(ans, v2[idx] - x); }
		if (idx - 1 >= 0){ ans = min(ans, x - v2[idx-1]);}
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	vector<ll> r, g, b;
	for (int i = 0; i < 2 * n; i++) {
		ll a; char c; cin >> a >> c;
		if (c == 'R') { r.push_back(a); }
		else if (c == 'G') { g.push_back(a); }
		else { b.push_back(a); }
	}
	
	sort(r.begin(), r.end());
	sort(b.begin(), b.end());
	sort(g.begin(), g.end());
	
    vector<vector<ll>> odd, even;
    for(auto &v : {r, g, b}) {
	    if (v.size() % 2) { odd.push_back(v); }
	    else { even.push_back(v); }
    }

    ll ans;
    if (odd.empty()) { ans = 0; }
    else{
        auto &v1 = odd[0], &v2 = odd[1];
		auto &v3 = even[0];
		ans = min(findMin(v1, v2), findMin(v1, v3) + findMin(v2, v3));
    }
    
    cout << ans << '\n';
}


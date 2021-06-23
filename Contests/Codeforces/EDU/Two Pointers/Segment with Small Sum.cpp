#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	int n; cin >> n;
	ll s; cin >> s;
	vector<ll> a(n); for(auto &x : a){ cin >> x; }
	
	int l = 0, ans = 0;
	ll curS = 0;
	for(int r = 0; r < n; r++){
	    curS += a[r];
	    while (curS > s) { curS -= a[l++]; }
	    
	    ans = max(ans, r-l+1);
	}
	
	cout << ans << '\n';
}
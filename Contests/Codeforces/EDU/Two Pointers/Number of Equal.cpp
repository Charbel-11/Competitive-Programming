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
	
	int n, m; cin >> n >> m;
	vector<int> a(n); for(auto &x : a){ cin >> x; }
	vector<int> b(m); for(auto &x : b){ cin >> x; }
	
	ll ans = 0;
	int i = 0, j = 0;
	while (i < n && j < m){
	    if (a[i] < b[j]){ i++; continue; }
	    if (b[j] < a[i]){ j++; continue; }
	    
	    int cntA = 1, cntB = 1;
	    while(i < n-1 && a[i] == a[i+1]) { cntA++; i++; }
	    while(j < m-1 && b[j] == b[j+1]) { cntB++; j++; }
	    
	    ans += (ll)cntA*cntB;
	    i++; j++;
	}
	
	cout << ans << '\n';
}
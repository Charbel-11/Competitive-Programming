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
	
	vector<int> ans(m, 0);
	int i = 0;
	for(int j = 0; j < m; j++){
	    while(i < n && a[i] < b[j]){ i++; }
	    ans[j] = i;
	}
	
	for(auto &x : ans){ cout << x << ' '; }
	cout << '\n';
}
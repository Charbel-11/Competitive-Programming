#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int getMin(vector<int>& a){
	int n = a.size();
	int maxV = a[0] + a.back();
	int minV = maxV;
	
	for(int i = 1; i < n - 1; i++){
		maxV = max(maxV, a[i] + a[n-i-1]);
		minV = min(minV, a[i] + a[n-i-1]);
	}
	
	return maxV - minV;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	int n; cin >> n;
	vector<int> a(n); for(auto &x : a){ cin >> x; }
	sort(a.begin(), a.end());
	
	if (n <= 2){ cout << 0 << '\n'; return 0; }
	
	int idx0 = lower_bound(a.begin(), a.end(), 0) - a.begin();
	if (n % 2){ a.insert(a.begin() + idx0, 0); }
	
	int ans = getMin(a);
	for(int i = 0; i < n; i += 2) {
		a.insert(a.begin() + idx0, 0);
		a.insert(a.begin() + idx0, 0);
		ans = min(ans, getMin(a));
	}
	
	cout << ans << '\n';
}
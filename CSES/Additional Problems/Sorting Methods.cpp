#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;
typedef long long ll;
 
struct FT {
	int n; vector<ll> vals;
	FT(const int n) : n(n), vals(vector<ll>(n + 1, 0)) { }
 
	//Adds x
	void update(int i, const ll x) {
		for (++i; i <= n; i += i & -i)
			vals[i] += x;
	}
	ll query(int i) const { // sum from 0 ... i
		ll sum = 0;
		for (++i; i; i -= i & -i)
			sum += vals[i];
		return sum;
	}
	ll query(int i, int j) const {		// sum from i ... j
		return query(j) - query(i - 1);
	}
};
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    
    int n; cin >> n;
    vector<int> nums(n); for(auto &x : nums){ cin >> x; x--; }
    
    FT ft(n + 1); ll ans = 0;
    for(int i = 0; i < n; i++){
        ans += ft.query(nums[i] + 1, n);
        ft.update(nums[i], 1);
    }
    cout << ans << ' ';
    
    ans = 0;
    vector<bool> seen(n, 0);
    for(int i = 0; i < n; i++){
        if (seen[i]){ continue; }
        int len = 0, cur = i;
        while(!seen[cur]){
            seen[cur] = true;
            len++;
            cur = nums[cur];
        }
        ans += len - 1;
    }
    cout << ans << ' ';
 
    ans = 0; int LIS = 1;
    vector<int> dp(n, n + 2);
    for(int i = 0; i < n; i++){
        int idx = upper_bound(dp.begin(), dp.end(), nums[i]) - dp.begin();
        dp[idx] = nums[i];
        LIS = max(LIS, idx + 1);
    }
    cout << n - LIS << ' ';
    
    ans = 0;
    vector<int> idx(n);
    for(int i = 0; i < n; i++){ idx[nums[i]] = i; }
    for(int i = n-2; i >= 0; i--){
        if (idx[i] > idx[i+1]){ ans = i + 1; break; }
    }
    cout << ans << ' ';
}
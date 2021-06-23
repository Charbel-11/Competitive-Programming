#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
#include <unordered_map>
#include <deque>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	int n; ll k; cin >> n >> k;
	vector<ll> nums(n); for(auto &x : nums){ cin >> x; }

    deque<ll> sMax, sMin;
    int l = 0; ll ans = 0;
    for(int r = 0; r < n; r++){
        while (!sMax.empty() && sMax.back() < nums[r]){ sMax.pop_back(); }
        while (!sMin.empty() && sMin.back() > nums[r]){ sMin.pop_back(); }
        sMax.push_back(nums[r]); sMin.push_back(nums[r]);
        
        ll curMax = sMax.front(), curMin = sMin.front();
        while(curMax - curMin > k){
            if (sMax.front() == nums[l]){ sMax.pop_front(); }
            if (sMin.front() == nums[l]){ sMin.pop_front(); }
            l++; curMax = sMax.front(); curMin = sMin.front();
        }
        
        ans += (r-l+1);
    }
    
    cout << ans << '\n';
}
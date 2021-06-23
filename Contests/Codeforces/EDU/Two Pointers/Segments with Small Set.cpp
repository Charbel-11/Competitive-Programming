#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
#include <unordered_map>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	int n, k; cin >> n >> k;
	vector<int> nums(n); for(auto &x : nums){ cin >> x; }
	vector<int> freq(1e5+2, 0);
	
	int l = 0, curN = 0; 
	ll ans = 0;
	for(int r = 0; r < n; r++){
	    freq[nums[r]]++;
	    if (freq[nums[r]] == 1){ curN++; }
	    while(curN > k){
	        freq[nums[l]]--;
	        if (freq[nums[l]] == 0){ curN--; }
	        l++;
	    }
	    ans += (r-l+1);
	}
	
	cout << ans << '\n';
}
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, k; cin >> n >> k;
    vector<int> A(k); for(auto &x : A){ cin >> x; }

    vector<int> nums; int idx = 0;
    for(int i = 1; i <= n; i++){
        for(int j = 0; j < 2; j++) {
            if (idx < k && A[idx] == i) { idx++; }
            else{ nums.push_back(i); }
        }
    }

    ll ans = 0;
    for(int i = 1; i < nums.size(); i += 2){
        ans += nums[i] - nums[i-1];
    }
    if (nums.size() % 2 == 1){
        ll curAns = ans;
        for(int i = (int)nums.size() - 3; i >= 0; i-=2){
            curAns += nums[i + 2] - nums[i+1];
            curAns -= (nums[i + 1] - nums[i]);
            ans = min(curAns, ans);
        }
    }

    cout << ans << '\n';
}


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;
typedef long long ll;
 
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	int n; cin >> n;
	vector<ll> h(n); for(auto &x : h){ cin >> x; }
	ll ans = 0;
	
	stack<ll> S; S.push(-1);
	for(int i = 0; i < n; i++){
	    while(S.size() > 1 && h[S.top()] > h[i]){
	        int curIdx = S.top(); S.pop();
	        ll cur = h[curIdx] * (i - S.top() - 1);
	        ans = max(ans, cur); 
	    }
	    S.push(i);
	}
	
	while(S.size() > 1){
	    int curIdx = S.top(); S.pop();
	    ll cur = h[curIdx] * (n - S.top() - 1);
	    ans = max(ans, cur);
	}
	
	cout << ans << '\n';
}
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int x, n; cin >> x >> n;
	priority_queue<ll, vector<ll>, greater<ll>> pq;
	for (int i = 0; i < n; i++) {
		int cur; cin >> cur; 
		pq.push(cur); 
	}

	ll ans = 0;
	while (pq.size() > 1) {
		ll min1 = pq.top(); pq.pop();
		ll min2 = pq.top(); pq.pop();
		ll newVal = min1 + min2;
		ans += newVal; pq.push(newVal);
	}

	cout << ans << '\n';
}
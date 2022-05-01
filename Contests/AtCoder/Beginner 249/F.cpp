#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, k; cin >> n >> k;
	vector<pair<int, ll>> op(n + 1); op[0] = { 1,0 };
	for (int i = 1; i <= n; i++) { cin >> op[i].first >> op[i].second; }

	priority_queue<ll> pq; int pqCapacity = k;
	ll ans = -1e15, totalSum = 0, pqSum = 0; 
	for (int i = n; i >= 0; i--) {
		ll y = op[i].second;

		if (op[i].first == 1) {
			ans = max(ans, y + totalSum - pqSum);

			pqCapacity--;
			if (pqCapacity < 0) { break; }
		}
		else {
			totalSum += y;
			if (y < 0) {
				pq.push(y); pqSum += y;
			}
		}

		while (pq.size() > pqCapacity) {
			pqSum -= pq.top();
			pq.pop();
		}
	}

	cout << ans << '\n';
}
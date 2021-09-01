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
	ll s, A, B; cin >> s >> A >> B;

	vector<ll> a(n), b(m); 
	for (auto& x : a) { cin >> x; }
	for (auto& x : b) { cin >> x; }
	sort(a.rbegin(), a.rend());
	sort(b.rbegin(), b.rend());

	ll curC = 0, curW = 0; int j = 0;
	for (; j < m; j++) {
		if (curW + B > s) { j--; break; }
		curW += B; curC += b[j];
	}
	if (j == m) { j--; }

	ll ans = curC;
	for (int i = 0; i < n; i++) {
		curC += a[i]; curW += A;
		while (curW > s && j >= 0) {
			curC -= b[j--]; curW -= B;
		}
		if (curW > s) { break; }

		ans = max(ans, curC);
	}

	cout << ans << '\n';
}
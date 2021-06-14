#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

ll digits(ll num) {
	int a = 0;
	while (num) { a++; num /= 10; }
	return a;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int T; cin >> T;
	while (T--) {
		ll N, X; cin >> N >> X;
		ll d = digits(X); ll milestone = 1, ans = 0;
		for (int i = 0; i < d; i++) { milestone *= 10; }

		while ((milestone - X)*d <= N) {
			ans += milestone - X; N -= (milestone - X)*d;
			X = milestone; d++; milestone *= 10;
		}

		if (N%d) { cout << -1 << endl; continue; }
		ans += N / d;
		cout << ans << endl;
	}
}
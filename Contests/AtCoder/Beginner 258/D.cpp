#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <climits>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, x; cin >> n >> x;
	vector<ll> A(n), B(n);
	for (int i = 0; i < n; i++) {
		cin >> A[i] >> B[i];
	}

	ll ans = LLONG_MAX, sumA = 0, sumB = 0, minB = B[0];
	for (int i = 0; i < min(n, x); i++) {
		sumA += A[i]; sumB += B[i];
		minB = min(minB, B[i]);

		ll left = x - (i + 1);
		ans = min(ans, sumA + sumB + minB * left);
	}

	cout << ans << '\n';
}

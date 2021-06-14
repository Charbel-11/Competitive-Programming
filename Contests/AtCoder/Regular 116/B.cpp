#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll mod = 998244353;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	vector<ll> A(n); for (auto& x : A) { cin >> x; }
	sort(A.begin(), A.end());

	ll minW = A[0], ans = (A[0] * A[0]) % mod;
	for (int i = 1; i < n; i++) {
		minW *= 2; minW += A[i]; minW %= mod;
		minW -= A[i - 1]; minW += mod; minW %= mod;
		ll cur = minW * A[i]; cur %= mod;
		ans += cur; ans %= mod;
	}

	cout << ans << '\n';
}
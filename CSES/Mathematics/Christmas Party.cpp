#include <iostream>
#include <string>
#include <vector>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;

int main() {
	int n; cin >> n;
	vector<ll> ans(n + 2, 0);
	ans[2] = 1;
	for (int i = 3; i <= n; i++) {
		ans[i] = ans[i - 1] + ans[i - 2];
		ans[i] %= mod;
		ans[i] *= (i - 1); ans[i] %= mod;
	}

	cout << ans[n] << '\n';
}
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int findKth(int n, int k, bool start0) {
	if (n == 1) { return 1; }

	int dead = n / 2;
	if (start0) { dead = (n + 1) / 2; }
	if (k <= dead) { return k * 2 - start0; }

	if (n % 2 == 0) { return findKth(n - dead, k - dead, start0) * 2 - (!start0); }
	else { return findKth(n - dead, k - dead, !start0) * 2 - (!start0); }
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int q; cin >> q;
	while (q--) {
		int n, k; cin >> n >> k;
		cout << findKth(n, k, false) << '\n';
	}
}

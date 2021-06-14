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

ll sum(ll l, ll r) {
	return (r*(r + 1) / 2) - ((l - 1)*l / 2);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int A, B, C, D; cin >> A >> B >> C >> D;
	ll res = 0;
	for (int z = C + 1; z <= D + 1; z++) {
		int l1 = A, r1 = B, l2 = B, r2 = C;

		int other = z - l2; 
		if (other > r1) { l2 += (other - r1); }
		else if (other <= r1) {
			other = max(other, l1);
			res += (ll)(r1 - other + 1)*(r2 - l2 + 1);
			l2++; r1 = other - 1;
		}

		if (l1 > r1 || l2 > r2) { continue; }
		int length = min(r2 - l2 + 1, r1 - l1 + 1);
		res += sum((r2 - l2 + 1) - length + 1, r2 - l2 + 1);
	}

	cout << res << endl;
}
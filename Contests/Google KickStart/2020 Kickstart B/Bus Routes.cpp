#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

int N;
ll D;
vector<ll>x;

bool check(ll time) {
	for (int i = 0; i < N; i++) {
		if (time%x[i] == 0) { continue; }
		time += (x[i]-time%x[i]);
	}
	return time<=D;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int T; cin >> T;
	for (int q = 1; q <= T; q++) {
		cin >> N >> D;
		x.clear(); x.resize(N);
		for (auto &y : x) { cin >> y; }

		ll l = 1, r = D;
		while (l < r) {
			ll mid = (l + r + 1) / 2;
			bool b = check(mid);
			if (b) { l = mid; }
			else { r = mid - 1; }
		}

		cout << "Case #" << q << ": " << l << endl;
	}
}
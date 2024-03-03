#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Day {
	int L, R, V; Day() {}
	Day(int l, int r, int v) : L(l), R(r), V(v) {}
	bool operator<(Day& rhs) {
		return L < rhs.L;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	vector<int> S(n); for (auto& x : S) { cin >> x; }

	int D; cin >> D;
	vector<Day> days(D);
	for (int i = 0; i < D; i++) {
		int l, r, v; cin >> l >> r >> v;
		days[i] = Day(l, r, v);
	}

	sort(days.begin(), days.end());
	
	int ans = 0, d = 0;
	int available = 0;
	for (int i = 0; i < n; i++) {
		if (days[d].L == i) {
			available += days[d].V;
		}

		int saved = min(available, S[i]);
		S[i] -= saved; 
		available -= saved;
	}

	cout << ans << '\n';
}
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

	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		vector<int> A(n), B(n);
		for (auto& x : A) { cin >> x; }
		for (auto& x : B) { cin >> x; }

		vector<pair<int, int>> C(n);
		for (int i = 0; i < n; i++) {
			C[i] = { A[i] + B[i], i };
		}
		sort(C.rbegin(), C.rend());

		int p1 = 0, p2 = 0;
		for (int i = 0; i < n; i++) {
			int idx = C[i].second;
			if (i % 2 == 0) { p1 += A[idx]; }
			else { p2 += B[idx]; }
		}

		if (p1 > p2) { cout << "First" << '\n'; }
		else if (p2 > p1) { cout << "Second" << '\n'; }
		else { cout << "Tie" << '\n'; }
	}
}
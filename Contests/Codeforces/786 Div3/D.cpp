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
		vector<int> a(n); for (auto& x : a) { cin >> x; }
		vector<int> aS = a;
		sort(aS.begin(), aS.end());

		bool OK = true;
		for (int i = n - 1; i >= 0; i -= 2) {
			if (i == 0 && a[i] != aS[i]) { OK = false; break; }
			else if (i > 0) {
				if ((a[i - 1] == aS[i - 1] && a[i] == aS[i]) || (a[i - 1] == aS[i] && a[i] == aS[i - 1])) { continue; }
				else { OK = false; break; }
			}
		}

		cout << (OK ? "YES" : "NO") << '\n';
	}
}
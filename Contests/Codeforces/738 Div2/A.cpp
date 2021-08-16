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
		int ans; cin >> ans;
		for (int i = 0; i < n - 1; i++) {
			int cur; cin >> cur; 
			ans &= cur;
		}
		cout << ans << '\n';
	}
}
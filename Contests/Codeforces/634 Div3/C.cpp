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

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;

	while (t--) {
		int n; cin >> n;
		map<int, int> m;
		int maxFreq = 0;
		for (int i = 0; i < n; i++) {
			int temp; cin >> temp;
			m[temp]++; maxFreq = max(maxFreq, m[temp]);
		}
		int distinct = m.size() - 1;
		int ans = min(maxFreq, distinct);
		ans = max(ans, min(maxFreq - 1, distinct + 1));
		cout << ans << endl;
	}
}
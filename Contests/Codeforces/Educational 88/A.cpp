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
		int n, m, k; cin >> n >> m >> k;
		int all = min(m, n / k);  m -= all;

		int others = (m + k - 2) / (k - 1);

		cout << all -others << endl;
	}
}
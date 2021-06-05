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

	int n; cin >> n;
	vector<int> id(n);
	for (auto &x : id) { cin >> x; }
	map<int, int> freq;

	int l = 0, res = 0;
	for (int r = 0; r < n; r++) {
		freq[id[r]]++;
		while (freq[id[r]] > 1) {
			freq[id[l]]--; l++;
		}
		res = max(res, r - l + 1);
	}

	cout << res << '\n';
}
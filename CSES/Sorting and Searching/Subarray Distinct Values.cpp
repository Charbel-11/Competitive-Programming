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

	int n, k; cin >> n >> k;
	vector<int> x(n); for (auto& xx : x) { cin >> xx; }

	ll ans = 0;
	int l = 0; map<int, int> freq;
	for (int r = 0; r < n; r++) {
		freq[x[r]]++;
		while (freq.size() > k) { 
			freq[x[l]]--;
			if (freq[x[l]] == 0) { freq.erase(x[l]); }
			l++;
		}

		ans += (r - l + 1);
	}

	cout << ans << '\n';
}
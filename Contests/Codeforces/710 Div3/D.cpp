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
		map<int, int> freq;
		for (int i = 0; i < n; i++) {
			int cur; cin >> cur; freq[cur]++;
		}

		int maxFreq = 0;
		for (auto& p : freq) { maxFreq = max(maxFreq, p.second); }

		if (maxFreq <= n / 2) { cout << (n % 2) << '\n'; }
		else { cout << (2 * maxFreq - n) << '\n'; }
	}
}
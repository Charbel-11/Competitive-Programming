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
	vector<string> S(n); for (auto& s : S) { cin >> s; }

	int maxAns = 0;
	for (int i = 0; i < (1 << n); i++) {
		vector<int> freq(26, 0);
		for (int j = 0; j < n; j++) {
			if (!((1 << j) & i)) { continue; }
			for (auto& c : S[j]) {
				freq[c - 'a']++;
			}
		}
		int curAns = 0;
		for (auto& x : freq) { curAns += (x == k); }
		maxAns = max(maxAns, curAns);
	}

	cout << maxAns << '\n';
}
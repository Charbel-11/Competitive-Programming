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

	int n, m; cin >> n >> m;
	string s; cin >> s;
	string cards; cin >> cards;

	vector<int> freq(26, 0);
	for (auto& c : cards) { freq[c - 'a']++; }

	int l = 0; ll ans = 0;
	for (int r = 0; r < n; r++) {
		int curIdx = s[r] - 'a';
		freq[curIdx]--;
		while (freq[curIdx] < 0) {
			freq[s[l] - 'a']++; 
			++l;
		}

		ans += (r - l + 1);
	}

	cout << ans << '\n';
}
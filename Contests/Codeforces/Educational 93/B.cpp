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
		string s; cin >> s;
		int n = s.size();
		vector<int> consOnes;
		int curOnes = 0;
		for (int i = 0; i < n; i++) {
			if (s[i] == '0') {
				if (curOnes) { consOnes.push_back(curOnes); }
				curOnes = 0;
			}
			else { curOnes++; }
		}
		if (curOnes) { consOnes.push_back(curOnes); }
		sort(consOnes.begin(), consOnes.end());

		bool alt = 1; int ans = 0;
		for (int i = (int)consOnes.size() - 1; i >= 0; i--) {
			ans += (alt ? consOnes[i] : 0);
			alt = !alt;
		}
		cout << ans << '\n';
	}
}
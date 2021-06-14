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
		vector<int> freq(10, 0);
		string s; cin >> s;
		int n = (int)s.size();
		for (int i = 0; i < n; i++) { freq[s[i] - '0']++; }
		sort(freq.begin(), freq.end());

		int res = n - freq.back();
		
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (i == j) { continue; }
				int needed = 0; bool alt = 0;
				for (int k = 0; k < n; k++) {
					int cur = s[k] - '0';
					if (cur != i && cur != j) { needed++; }
					else if (cur == i && alt) { needed++; }
					else if (cur == j && !alt) { needed++; }
					else { alt = !alt; }
				}
				if ((n - needed) % 2) { needed++; }
				res = min(res, needed);
			}
		}

		cout << res << '\n';
	}
}
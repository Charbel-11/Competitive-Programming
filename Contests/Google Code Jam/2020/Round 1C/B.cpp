#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;
typedef long double ld;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

//ifstream ifs("in2.txt");

	int T; cin >> T;
	for (int q = 1; q <= T; q++) {
		int u; cin >> u;

		vector<ll> freq(26, 0), freq2(26, 0);

		for (int tt = 0; tt < 10000; tt++) {
			ll M; cin >> M;
			string r; cin >> r;

			freq[r[0] - 'A']++;
			freq2[r[r.size() - 1] - 'A']++;
		}

		vector<bool> used(26, 0);

		string ans('s', 10);
		for (int i = 1; i < 10; i++) {
			int cur = 0; ll maxF = 0;
			for (int j = 0; j < 26; j++) {
				if (used[j]) { continue; }
				if (freq[j] > maxF) {
					maxF = freq[j]; cur = j;
				}
			}
			ans[i] = cur + 'A';
			used[cur] = 1;
		}
		int cur = 0; ll maxF = 0;
		for (int j = 0; j < 26; j++) {
			if (used[j]) { continue; }
			if (freq2[j] > maxF) {
				maxF = freq2[j]; cur = j;
			}

		}
		ans[0] = cur + 'A';

		cout << "Case #" << q << ": " << ans << endl;
	}
}
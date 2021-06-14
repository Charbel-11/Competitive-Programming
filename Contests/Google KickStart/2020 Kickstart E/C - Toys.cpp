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
const ll INF = 1e15;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;

	for (int qq = 1; qq <= t; qq++) {
		int n; cin >> n;
		vector<ll> E(n), R(n);
		for (int i = 0; i < n; i++) { cin >> E[i] >> R[i]; }

		int minRem = n; ll maxScore = 0;
		ll totalPlayTime = 0, prefE = 0, removedE = 0; 
		int removed = 0;
		map<ll, vector<ll>> m;	//spare time -> E

		for (int i = 0; i < n; i++) { totalPlayTime += E[i]; }
		maxScore = totalPlayTime; minRem = 0;
		for (int i = 0; i < n; i++) { 
			ll spare = (totalPlayTime - E[i]) - R[i];
			prefE += E[i];

			if (spare >= removedE) { m[spare].push_back(E[i]); }
			else {
				removedE += E[i]; removed++;
				auto it = m.begin();
				while (it != m.end() && it->first < removedE) {
					for (auto &v : it->second) { removedE += v; removed++; }
					m.erase(m.begin()); it = m.begin();
				}
			}

			ll curScore = totalPlayTime + prefE - 2*removedE;
			if (curScore > maxScore) { maxScore = curScore; minRem = removed; }
			else if (curScore == maxScore) { minRem = min(minRem, removed); }
		}

		if (!m.empty()) { minRem = removed; maxScore = INF; }

		cout << "Case #" << qq << ": " << minRem << " ";
		if (maxScore == INF) { cout << "INDEFINITELY" << '\n'; }
		else { cout << maxScore << '\n'; }
	}
}
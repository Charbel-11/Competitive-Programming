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

int timeToInt(string& s) {
	return (s[0] - '0') * 60 * 10 + (s[1] - '0') * 60 + (s[3] - '0') * 10 + (s[4] - '0');
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;

	for (int qq = 1; qq <= t; qq++) {
		int tt; cin >> tt;
		int na, nb; cin >> na >> nb;
		multiset<pair<int, int>> timeA, timeB;

		for (int i = 0; i < na; i++) {
			string s, e; cin >> s >> e;
			timeA.insert({ timeToInt(s), timeToInt(e) });
		}
		for (int i = 0; i < nb; i++) {
			string s, e; cin >> s >> e;
			timeB.insert({ timeToInt(s), timeToInt(e) });
		}

		int ansA = 0, ansB = 0;
		while (!timeA.empty() && !timeB.empty()) {
			bool atA = false; int availableAt = timeB.begin()->second + tt;
			if (timeA.begin()->first < timeB.begin()->first) {
				atA = true; availableAt = timeA.begin()->second + tt;
				timeA.erase(timeA.begin()); ansA++;
			}
			else { timeB.erase(timeB.begin()); ansB++; }

			while (true) {
				if (atA){ 
					auto it = timeB.lower_bound({ availableAt, availableAt });
					if (it == timeB.end()) { break; }
					availableAt = it->second + tt;
					timeB.erase(it);
				}
				else {
					auto it = timeA.lower_bound({ availableAt, availableAt });
					if (it == timeA.end()) { break; }
					availableAt = it->second + tt;
					timeA.erase(it);
				}
				atA = !atA;
			}
		}
		ansA += timeA.size();
		ansB += timeB.size();

		cout << "Case #" << qq << ": " << ansA << " " << ansB << '\n';
	}
}
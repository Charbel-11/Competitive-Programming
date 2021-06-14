#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

struct comp {
	bool operator()(const pair<int, int>& p1, const pair<int, int>&p2) const {
		if (p1.first == p2.first) { return p1.second > p2.second; }
		return p1.first < p2.first;
	}
};

int main() {
	int n, m; cin >> n >> m;

	multiset<pair<int, int>, comp> teams;
	for (int i = 0; i < n; i++) { teams.insert({ 0,0 }); }
	vector<pair<int, int>> values(n + 1, { 0,0 });
	int aboveMe = 0;
	int mySolved = 0, myPen = 0;

	for (int z = 0; z < m; z++) {
		int t, p; cin >> t >> p;

		if (t == 1) {
			auto itr = teams.upper_bound({ mySolved, myPen });
			auto temp = teams.find({ mySolved, myPen });
			teams.erase(temp);
			mySolved++; myPen += p;
			auto itr2 = teams.upper_bound({ mySolved, myPen });
			while (itr != itr2) {
				itr++; aboveMe--;
			}
			teams.insert({ mySolved, myPen });
		}
		else {
			int curSolved = values[t].first;
			int curPen = values[t].second;

			if ((curSolved + 1 == mySolved && curPen + p < myPen) || (curSolved == mySolved && myPen <= curPen)) {
				aboveMe++;
			}
			auto it = teams.find({ curSolved, curPen });
			teams.erase(it);
			curSolved++; curPen += p;
			values[t] = { curSolved, curPen };
			teams.insert({ curSolved, curPen });
		}

		cout << aboveMe + 1 << endl;
	}
}
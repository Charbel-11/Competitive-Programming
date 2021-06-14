#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>

using namespace std;

vector<int> agility;
vector<int> L, R, D;
int n, m, k, t;

bool check(int numOfSoldiers) {
	int minAg = agility[m - numOfSoldiers];
	vector<pair<int, int>> curTraps;

	for (int i = 0; i < k; i++) {
		if (D[i] <= minAg) { continue; }
		curTraps.push_back({ L[i], R[i] });
	}
	sort(curTraps.begin(), curTraps.end());

	int res = 0, masterRange = 0;
	for (auto it2 : curTraps) {
		if (it2.second <= masterRange) { continue; }

		if (it2.first > masterRange) {
			masterRange = it2.first - 1;
		}

		res += it2.second - masterRange;
		masterRange = it2.second;
	}

	long long temp = res * 2ll + n + 1;
	return temp <= t;
}

int main() {
	cin >> m >> n >> k >> t;

	agility.resize(m);
	for (auto &x : agility) { cin >> x; }
	sort(agility.begin(), agility.end());

	for (int i = 0; i < k; i++) {
		int li, ri, di; cin >> li >> ri >> di;
		L.push_back(li); R.push_back(ri); D.push_back(di);
	}

	int l = 0, h = m;
	while (l < h) {
		int mid = (l + h + 1) / 2;
		if (check(mid)) {
			l = mid;
		}
		else {
			h = mid - 1;
		}
	}

	cout << l << endl;
}
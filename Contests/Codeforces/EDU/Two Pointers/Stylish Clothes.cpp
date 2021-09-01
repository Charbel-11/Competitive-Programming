#include <iostream>
#include <string>
#include <array>
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

	array<vector<int>, 4> clothes;
	for (int i = 0; i < 4; i++) {
		int n; cin >> n;
		clothes[i].resize(n);
		for (auto& x : clothes[i]) { cin >> x; }
		sort(clothes[i].begin(), clothes[i].end());
	}

	int minAns = 1e6; array<int, 4> minIdx;
	for (int i = 0; i < 4; i++) {
		array<int, 4> idx = { 0,0,0,0 };
		for (int j = 0; j < clothes[i].size(); j++) {
			int curMin = clothes[i][j], curAns = 0;

			for (int k = 1; k <= 3; k++) {
				int clIdx = (i + k) % 4;
				while (idx[clIdx] < clothes[clIdx].size() && clothes[clIdx][idx[clIdx]] < curMin) { idx[clIdx]++; }
				if (idx[clIdx] < clothes[clIdx].size()) { curAns = max(curAns, clothes[clIdx][idx[clIdx]] - curMin); }
				else { curAns = 1e6; break; }
			}

			if (curAns < minAns) {
				minAns = curAns; minIdx[i] = j;
				for (int k = 1; k <= 3; k++) {
					int clIdx = (i + k) % 4;
					minIdx[clIdx] = idx[clIdx];
				}
			}
		}
	}
	
	for (int i = 0; i < 4; i++) { cout << clothes[i][minIdx[i]] << ' '; }
}
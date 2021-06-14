#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

vector<int> c;
vector<pair<int, int>> ans;
vector<vector<int>> lca;
int n, k;

int buildTree(int rootVal, set<int> curNodes) {
	if (curNodes.size() == 1) { return *curNodes.begin(); }
	int curIdx = k++; c.push_back(rootVal);

	while (!curNodes.empty()) {
		int cur = *curNodes.begin(), nxtRootVal = 0; 
		set<int> nxtNodes; nxtNodes.insert(cur);

		for (auto& v : curNodes) {
			if (cur == v) { continue; }
			if (lca[cur][v] < rootVal) {
				nxtRootVal = max(nxtRootVal, lca[cur][v]);
				nxtNodes.insert(v);
			}
		}
		for (auto& v : nxtNodes) { curNodes.erase(v); }

		int child = buildTree(nxtRootVal, nxtNodes);
		ans.push_back({ child, curIdx });
	}

	return curIdx;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	cin >> n; k = n;
	lca.resize(n, vector<int>(n));
	c.resize(n);
	int rootVal = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> lca[i][j];
			rootVal = max(rootVal, lca[i][j]);
		}
		c[i] = lca[i][i];
	}

	set<int> nodes;
	for (int i = 0; i < n; i++) { nodes.insert(i); }
	int r = buildTree(rootVal, nodes);

	cout << k << '\n';
	for (auto& x : c) { cout << x << ' '; } cout << '\n';
	cout << r + 1 << '\n';
	for (auto& p : ans) { cout << p.first + 1 << " " << p.second + 1 << '\n'; }
}
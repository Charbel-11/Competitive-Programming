#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <climits>
#include <string>
using namespace std;

vector<vector<int>> D; int n;
const int inf = INT_MAX;
vector<int> path; int m;

void allPairsShortestPath() {
	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (D[i][k] != inf && D[k][j] != inf && D[i][k] + D[k][j] < D[i][j])
					D[i][j] = D[i][k] + D[k][j];
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n; D.resize(n);
	for (int i = 0; i < n; i++) {
		string s; cin >> s;
		D[i].resize(n, inf);
		for (int j = 0; j < n; j++) {
			if (s[j] == '1') { D[i][j] = 1; } 
		}
	}
	for (int i = 0; i < n; i++) { D[i][i] = 0; }

	cin >> m; path.resize(m); for (auto &x : path) { cin >> x; x--; }
	vector<int> answ; answ.push_back(path[0]);
	allPairsShortestPath();

	int i = 0, k = 2;
	while (k < path.size()) {
		k = i + 2;
		while (k < path.size() && D[path[i]][path[k]] == k - i) { k++; }
		if (k == path.size()) { break; }

		answ.push_back(path[--k]); i = k;
	}
	answ.push_back(path[m - 1]);

	cout << answ.size() << endl;
	for (auto x : answ) { cout << ++x << " "; }
}
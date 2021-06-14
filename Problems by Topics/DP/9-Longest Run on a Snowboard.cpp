//https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1226
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int DP[105][105];
vector<vector<int>> grid;

//find adjacent numbers that are < than the current one, 
//returns [{1,2},{-1,-1},{-1,-1},{-1,-1}] if only (1,2) is acceptable
vector<pair<int, int>> findAdj(int rows, int columns, int i, int j) {
	vector<pair<int, int>> adj(4);
	for (int a = 0; a < 4; a++) { adj[a].first = -1; adj[a].second = -1; }

	if (j > 0) {
		if (grid[i][j - 1] < grid[i][j]) { adj[0].first = i; adj[0].second = j - 1; }
	}
	if (j < columns - 1) {
		if (grid[i][j + 1] < grid[i][j]) { adj[1].first = i; adj[1].second = j + 1; }
	}
	if (i > 0) {
		if (grid[i - 1][j] < grid[i][j]) { adj[2].first = i - 1; adj[2].second = j; }
	}
	if (i < rows - 1) {
		if (grid[i + 1][j] < grid[i][j]) { adj[3].first = i + 1; adj[3].second = j; }
	}

	return adj;
}

//find the longest path starting with i,j
//We are testing all start points using a loop in main
int findLongest(int rows, int columns, int i, int j) {
	if (DP[i][j] != -1) { return DP[i][j]; }

	vector<pair<int, int>> adj = findAdj(rows, columns, i, j);

	int longestPath = 1;
	for (int a = 0; a < 4; a++) {
		if (adj[a].first != -1) {
			int curPath = 1 + findLongest(rows, columns, adj[a].first, adj[a].second);
			longestPath = max(longestPath, curPath);
		}
	}

	DP[i][j] = longestPath; return longestPath;
}

void resetDP() {
	for (int i = 0; i < 105; i++)
		for (int j = 0; j < 105; j++)
			DP[i][j] = -1;
}

int main() {
	int testCases; cin >> testCases;
	for (int i = 0; i < testCases; i++) {
		resetDP();
		string name; cin >> name;
		int rows, columns; cin >> rows >> columns;

		grid.resize(rows); for (int i = 0; i < rows; i++) { grid[i].resize(columns); }
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < columns; j++)
				cin >> grid[i][j];

		int longest = 0;
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				int cur = findLongest(rows, columns, i, j);
				longest = max(longest, cur);
			}
		}

		cout << name << ": " << longest << endl;
	}
}
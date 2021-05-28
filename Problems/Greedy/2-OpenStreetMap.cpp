//https://codeforces.com/problemset/problem/1195/E
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <queue>

using namespace std;

long long g[10000000];
vector<vector<int>> grid;
vector<vector<int>> vertMin;
long long a, b, n, m, x, y, z, g0;

void fill_g() {
	g[0] = g0;
	for (int i = 1; i < (n * m) + m + 5; i++) {
		g[i] = (g[i - 1] * x + y) % z;
	}
}

void vM() {
	list<pair<int, int>> curList;
	for (int j = 0; j < m; j++) {
		curList.clear();

		curList.push_back({ grid[0][j], 0 });
		for (int i = 1; i < a; i++) {
			int cur = grid[i][j];
			while (!curList.empty() && cur <= curList.back().first) { curList.pop_back(); }
			curList.push_back({ cur, i });
		}
		vertMin[0][j] = curList.front().first;

		for (int i = 1; i + a - 1 < n; i++) {
			if (curList.front().first == grid[i - 1][j] && curList.front().second == i-1) { curList.pop_front(); }

			int cur = grid[i + a - 1][j];
			while (!curList.empty() && cur <= curList.back().first) { curList.pop_back(); }
			curList.push_back({ cur, i + a - 1 });

			vertMin[i][j] = curList.front().first;
		}
	}
}

long long minS() {
	long long res = 0;

	list<pair<int, int>> curList;
	for (int i = 0; i + a - 1 < n; i++) {
		curList.clear();

		curList.push_back({ vertMin[i][0],0 });
		for (int j = 1; j < b; j++) {
			int cur = vertMin[i][j];

			while (!curList.empty() && cur <= curList.back().first) { curList.pop_back(); }
			curList.push_back({ cur, j });
		}
		res += curList.front().first;

		for (int j = 1; j + b - 1 < m; j++) {
			if (curList.front().first == vertMin[i][j-1] && curList.front().second == j-1) { curList.pop_front(); }

			long long cur = vertMin[i][j + b - 1];
			while (!curList.empty() && cur <= curList.back().first) { curList.pop_back(); }
			curList.push_back({ cur, j + b - 1});
			res += curList.front().first;
		}
	}

	return res;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	cin >> n >> m >> a >> b >> g0 >> x >> y >> z;

	grid.resize(n);
	fill_g();
	for (int i = 0; i < n; i++) {
		grid[i].resize(m);
		for (int j = 0; j < m; j++) {
			grid[i][j] = g[i*m + j];
		}
	}


	vertMin.resize(n-a+2);
	for (int i = 0; i < n-a+2; i++) { vertMin[i].resize(m); }
	vM();

	cout << minS() << endl;
}
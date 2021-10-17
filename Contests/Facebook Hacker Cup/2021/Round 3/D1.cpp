#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <numeric>
using namespace std;
typedef long long ll;

int R, C;
vector<vector<int>> H, S;

struct Event {
	int r, c, h, s;
	Event(int _r, int _c, int _h, int _s) :r(_r), c(_c), h(_h), s(_s) {}

	bool operator<(Event& rhs) {
		return s < rhs.s;
	}
};

struct DSU {
	vector<int> rank, parent, robots;

	DSU(int n) {
		rank.resize(n, 1); parent.resize(n);
		iota(parent.begin(), parent.end(), 0);
		robots.resize(n, 0);
	}

	int find(const int u) { return parent[u] == u ? u : (parent[u] = find(parent[u])); }
	int size(int u) { return rank[find(u)]; }

	bool merge(int u, int v) {
		u = find(u); v = find(v);
		if (u == v) { return false; }
		if (rank[u] < rank[v]) { swap(u, v); }
		rank[u] += rank[v];	parent[v] = u;
		robots[u] += robots[v];
		return true;
	}

	bool findRobot(int idx) {
		idx = find(idx);
		if (robots[idx] > 0) { return true; }
		robots[idx]++; return false;
	}
};

int dx[] = { -1,1,0,0 };
int dy[] = { 0,0,-1,1 };

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	ifstream ifs("in.txt");
	ofstream ofs("out.txt");

	int t; ifs >> t;
	for (int qq = 1; qq <= t; qq++) {
		ofs << "Case #" << qq << ": ";

		ifs >> R >> C;
		H.clear(); H.resize(R, vector<int>(C));
		S.clear(); S.resize(R, vector<int>(C));
		for (int i = 0; i < R; i++)
			for (int j = 0; j < C; j++)
				ifs >> H[i][j];
		for (int i = 0; i < R; i++)
			for (int j = 0; j < C; j++)
				ifs >> S[i][j];

		int maxSamples = 0; vector<Event> events;
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				if (H[i][j] > S[i][j]) { 
					maxSamples++; 
					events.push_back(Event(i, j, H[i][j], S[i][j]));
				}
			}
		}
		if (maxSamples == 0) { ofs << "0 0" << '\n'; continue; }
		sort(events.rbegin(), events.rend());

		DSU dsu(R * C);
		vector<vector<bool>> on(R, vector<bool>(C, false));

		vector<pair<int, pair<int, int>>> enable;
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				enable.push_back({ H[i][j] - 1,{i, j} });
			}
		}
		sort(enable.rbegin(), enable.rend());

		int minRobots = 0, idxE = 0;
		for (auto& ev : events) {
			while (idxE < enable.size() && enable[idxE].first >= ev.s) {
				int i = enable[idxE].second.first, j = enable[idxE].second.second;
				on[i][j] = true;
				for (int k = 0; k < 4; k++) {
					int ni = i + dx[k], nj = j + dy[k];
					if (ni < 0 || ni >= R || nj < 0 || nj >= C) { continue; }
					if (on[ni][nj]) { dsu.merge(i * C + j, ni * C + nj); }
				}
				idxE++;
			}

			if (!dsu.findRobot(ev.r * C + ev.c)) { minRobots++; }
		}

		ofs << maxSamples << " " << minRobots << '\n';
	}
}
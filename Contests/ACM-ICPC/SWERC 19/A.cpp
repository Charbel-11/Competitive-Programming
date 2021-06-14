#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>
#include <stack>
#include <map>
using namespace std;
typedef long long ll;
const int INF = 1 << 30;

int xS, yS, xD, yD;
int B, C0;

vector<pair<int, int>> coord;	//node index -> (x, y)
vector<vector<int>> dist;

int findDist(int i, int j) {
	int dx = coord[i].first - coord[j].first;
	int dy = coord[i].second - coord[j].second;
	dx *= dx; dy *= dy;
	int t = dx + dy;

	//return (int)(ceil(sqrt(dx + dy)) + 0.1);

	int l = 0, r = t;
	while (l < r) {
		int mid = (l + r) >> 1;
		int mid2 = mid * mid;
		if (mid2 >= t) { r = mid; }
		else { l = mid + 1; }
	}

	return l;
}

struct graph {
	int n;
	vector<vector<int>> w;
	vector<vector<int>> cost;
	graph(int _n) : n(_n) { w.resize(n, vector<int>(n, INF)); cost.resize(n, vector<int>(B + 1, INF)); }

	void dijkstra_sp(int s) {
		vector<vector<bool>> visited(n, vector<bool>(B + 1, false));
		cost[s][0] = 0;

		for (int b = 0; b <= B; b++) {
			while (true) {
				int curM = -1;
				for (int i = 0; i < n; i++) {
					if (visited[i][b] || cost[i][b] == INF) { continue; }
					if (curM == -1) { curM = i; }
					else if (cost[i][b] < cost[curM][b]) { curM = i; }
				}
				if (curM == -1) { break; }
				visited[curM][b] = true;

				for (int j = 0; j < n; j++) {
					int realD = dist[curM][j];
					if (b + realD <= B && cost[curM][b] + w[curM][j] < cost[j][b + realD]) {
						cost[j][b + realD] = cost[curM][b] + w[curM][j];
					}
				}
			}
		}
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	cin >> xS >> yS;
	cin >> xD >> yD;
	cin >> B;
	cin >> C0;

	int T; cin >> T;
	vector<int> Ci(T);
	for (auto& x : Ci) { cin >> x; }

	map<pair<int, int>, int> m;

	int N; cin >> N;
	coord.resize(N);

	vector<vector<pair<int, int>>> edges(N);
	for (int i = 0; i < N; i++) {
		int xi, yi, l; cin >> xi >> yi >> l;
		coord[i] = { xi, yi }; m[coord[i]] = i;
		for (int j = 0; j < l; j++) {
			int s2, m; cin >> s2 >> m; m--;
			edges[i].push_back({ s2, m });
		}
	}

	int n = N, S = -1, D = -1;
	if (m.count({ xS, yS })) { S = m[{xS, yS}]; }
	else { coord.push_back({ xS, yS }); S = n++; }
	if (m.count({ xD, yD })) { D = m[{xD, yD}]; }
	else { coord.push_back({ xD, yD }); D = n++; }

	graph g(n);
	dist.resize(n, vector<int>(n));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) 
			dist[i][j] = findDist(i, j);

	for (int i = 0; i < N; i++) {
		for (auto& e : edges[i]) {
			int j = e.first, m = e.second;
			g.w[i][j] = g.w[j][i] = min(g.w[i][j], Ci[m] * dist[i][j]);
		}
	}

	for (int i = 0; i < n; i++) {
		g.w[i][i] = 0;
		g.w[i][S] = g.w[S][i] = min(g.w[i][S], C0 * dist[i][S]);
		g.w[i][D] = g.w[D][i] = min(g.w[i][D], C0 * dist[i][D]);
	}

	g.dijkstra_sp(S);

	int ans = INF;
	for (int b = 0; b <= B; b++) {
		ans = min(ans, g.cost[D][b]);
	}

	if (ans == INF) { cout << -1 << '\n'; }
	else { cout << ans << '\n'; }
}
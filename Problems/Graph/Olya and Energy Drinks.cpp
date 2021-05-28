//https://codeforces.com/contest/877/problem/D

#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <queue>
#include <stdio.h>
#include <string.h>

using namespace std;
typedef long long ll;
const int INF = 1 << 30;

int n, m, k;
int mx[4] = { 1,-1,0,0 };
int my[4] = { 0,0,1,-1 };
bool visited[1002][1002];
int dist[1002][1002];

bool check(int i, int j) {
	return (i >= 0 && j >= 0 && i < n && j < m);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	cin >> n >> m >> k;
	vector<string> grid(n);
	for (auto &s : grid) { cin >> s; }

	int si, sj, ei, ej; cin >> si >> sj >> ei >> ej;
	si--; sj--; ei--; ej--;

	memset(visited, 0, sizeof(visited));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			dist[i][j] = INF;

	queue<pair<int, int>> Q; Q.push({ si,sj });
	visited[si][sj] = 1; dist[si][sj] = 0;

	while (!Q.empty()) {
		auto p = Q.front(); Q.pop();
		int i = p.first, j = p.second;

		for (int m = 0; m < 4; m++) {
			for (int kk = 1; kk <= k; kk++) {
				int ni = i + kk * mx[m], nj = j + kk * my[m];
				//Complexity is still n*m since we will break for <= distances
				//At any pt in the queue, we have level i and i+1 only so if we encounter
				//nodes at level i, we can break since we will try going that path with it
				//If we encounter nodes at i+1, then we should continue because we might
				//get to unvisited nodes after that i+1 which will have its dist i+1 instead of i+2
				//Each node is vistied at most once in each direction -> 4 times -> O(4nm)
				//This is because assume we got a visit from each direction, then we are at level i+1
				//As are all the ones at the left/right/top/below up to one node at level i
				//Any subsequent traversal will be stopped by that node at level i since everything <i already dealt with
				//Hence no way to get to that node again
				if (!check(ni, nj) || grid[ni][nj] == '#' || dist[ni][nj] <= dist[i][j]) { break; }
				if (visited[ni][nj]) { continue; }		//visited means in the queue (or popped and done with), but the cur dist might be <
				visited[ni][nj] = 1;
				dist[ni][nj] = 1 + dist[i][j];
				Q.push({ ni,nj });
			}
		}
	}

	cout << (dist[ei][ej] == INF ? -1 : dist[ei][ej]) << '\n';
}
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
    vector<string> grid(n);
    for(auto &s : grid){ cin >> s; }

    set<pair<int, int>> visited;
    stack<pair<int, int>> starts;
    starts.push({1,1});
    while(!starts.empty()){
        auto cur = starts.top(); starts.pop();
        visited.insert(cur);
        auto [x, y] = cur;

        for(int k = 0; k < 4; k++){
            int curX = x + dx[k], curY = y + dy[k];
            while(grid[curX][curY] != '#'){
                int nextX = curX + dx[k], nextY = curY + dy[k];
                if (grid[nextX][nextY] == '#' && !visited.count({curX, curY})){
                    starts.push({curX, curY});
                }
                visited.insert({curX, curY});
                curX += dx[k]; curY += dy[k];
            }
        }
    }

    cout << visited.size() << '\n';
}
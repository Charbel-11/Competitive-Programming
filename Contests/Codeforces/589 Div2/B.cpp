#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

const long long mod = 1000000007;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int h, w; cin >> h >> w;
	vector<int> r, c;

	for (int i = 0; i < h; i++) {
		int temp; cin >> temp;
		r.push_back(temp);
	}
	for (int i = 0; i < w; i++) {
		int temp; cin >> temp;
		c.push_back(temp);
	}

	vector<vector<int>> grid(h);
	for (auto &x : grid) { x.resize(w, -1); }
	for (int i = 0; i < h; i++) {
		int cur = r[i];
		for (int j = 0; j < cur; j++) {
			grid[i][j] = 1;
		}
		if (cur < w) grid[i][cur] = 0;
	}
	for (int i = 0; i < w; i++) {
		int cur = c[i];
		for (int j = 0; j < cur; j++) {
			if (grid[j][i] != -1 && grid[j][i] != 1) { cout << 0 << endl; return 0; }
			grid[j][i] = 1;
		}
		if (cur < h) {
			if (grid[cur][i] != -1 && grid[cur][i] != 0){ cout << 0 << endl; return 0; }
			grid[cur][i] = 0;
		}
	}
	
	long long answ = 1;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (grid[i][j] == -1) {
				answ *= 2;
				answ %= mod;
			}
		}
	}

	cout << answ << endl;
}
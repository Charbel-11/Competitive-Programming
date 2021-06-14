#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;
const ll mod = (ll)1e9 + 7;

int main() {
	int H, W; cin >> H >> W;
	vector<string> grid(H);
	vector<vector<ll>> ways(H);
	for (auto &x : grid) { cin >> x; }
	for (auto &x : ways) { x.resize(W); }
	ways[0][0] = 0;
	for (int j = 1; j < W; j++) {
		if (grid[0][j] == '#') { break; }
		ways[0][j] = 1;
	}
	for (int i = 1; i < H; i++) {
		if (grid[i][0] == '#') { break; }
		ways[i][0] = 1;
	}

	for (int i = 1; i < H; i++) {
		for (int j = 1; j < W; j++) {
			if (grid[i][j] == '#') { continue; }
			ways[i][j] = ways[i - 1][j] + ways[i][j - 1];
			ways[i][j] %= mod;
		}
	}

	cout << ways[H - 1][W - 1] << endl;
}
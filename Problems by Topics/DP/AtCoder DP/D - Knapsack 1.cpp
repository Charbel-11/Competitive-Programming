#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

ll DP[101][(int)1e5 + 1];
vector<pair<int, int>> objects;

ll Knapsack(int i, int w) {
	if (DP[i][w] != -1) { return DP[i][w]; }
	if (i >= objects.size()) { return DP[i][w] = 0; }

	ll c1 = Knapsack(i + 1, w), c2 = 0;
	if (objects[i].first <= w) {
		c2 = Knapsack(i + 1, w - objects[i].first) + objects[i].second;
	}

	DP[i][w] = max(c1, c2);
	return DP[i][w];
}

int main() {
	for (int i = 0; i < 101; i++)
		for (int j = 0; j < (int)1e5 + 1; j++)
			DP[i][j] = -1;
	
	int N, W; cin >> N >> W;
	objects.resize(N);
	for (auto &x : objects) { cin >> x.first >> x.second; }

	cout << Knapsack(0, W) << endl;
}
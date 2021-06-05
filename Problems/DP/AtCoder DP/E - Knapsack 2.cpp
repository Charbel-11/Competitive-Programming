#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <climits>
#include <algorithm>

using namespace std;
typedef long long ll;

//Usual array doesn't check for out of bound problems!
ll DP[101][(int)1e5 + 1];
vector<pair<int, int>> objects;
ll N, W;

ll Knapsack(int i, int v) {
	if (v <= 0) { return 0; }
	if (DP[i][v] != -1) { return DP[i][v]; }
	if (i >= objects.size()) { return DP[i][v] = LLONG_MAX / 8; }

	ll c1 = Knapsack(i + 1, v);
	ll c2 = Knapsack(i + 1, v - objects[i].second) + objects[i].first;

	DP[i][v] = min(c1, c2);
	return DP[i][v];
}

int main() {
	for (int i = 0; i < 101; i++)
		for (int j = 0; j < (int)1e5 + 1; j++)
			DP[i][j] = -1;

	cin >> N >> W;
	objects.resize(N);
	for (auto &x : objects) { cin >> x.first >> x.second; }

	for (int i = (int)1e5; i >= 0; i--) {
		if (Knapsack(0, i) <= W) { cout << i << endl; break; }
	}
}
//https://code.google.com/codejam/contest/1842485/dashboard
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int DP[10005][10005];
vector<int> distances;
vector<int> lengths;
int totalDistance;
int numOfVines;

bool reachable(int prevVine, int curVine) {
	if (curVine >= numOfVines) { return false; }
	if (prevVine != -1 && DP[prevVine][curVine] != -1) { return DP[prevVine][curVine]; }

	int range = distances[curVine] * 2;
	if (prevVine != -1) {
		range = distances[curVine];
		int delta = distances[curVine] - distances[prevVine];
		range += min(delta, lengths[curVine]);
	}
	if (range >= totalDistance) { return true; }

	for (int i = curVine + 1; i < numOfVines && distances[i] <= range; i++) {
		bool trial = reachable(curVine, i);
		if (trial) {
			if (prevVine != -1) { DP[prevVine][curVine] = true; }
			return true;
		}
	}

	if (prevVine != -1) { DP[prevVine][curVine] = false; }
	return false;
}

void resetDP(int numOfVines) {
	for (int i = 0; i < numOfVines + 1; i++)
		for (int j = 0; j < numOfVines + 1; j++)
			DP[i][j] = -1;
}

int main() {
	int T; cin >> T;

	for (int i = 0; i < T; i++) {
		cin >> numOfVines;
		resetDP(numOfVines);
		distances.clear(); lengths.clear();

		for (int j = 0; j < numOfVines; j++) {
			int temp; cin >> temp;
			distances.push_back(temp);
			cin >> temp;
			lengths.push_back(temp);
		}

		cin >> totalDistance;
		string res = reachable(-1, 0) ? "YES" : "NO";
		cout << "Case #" << i+1 << ": " << res << endl;
	}
}
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int mex[15][15];

int dx[] = { -2,-2,1,-1 };
int dy[] = { 1,-1,-2,-2 };

int getMex(int i, int j) {
	if (mex[i][j] != -1) { return mex[i][j]; }

	int ans = 0; vector<int> choices;
	for (int k = 0; k < 4; k++) {
		int ni = i + dx[k], nj = j + dy[k];
		if (ni < 0 || nj < 0 || ni>14 || nj>14) { continue; }
		choices.push_back(getMex(ni, nj));
	}
	sort(choices.begin(), choices.end());
	choices.erase(unique(choices.begin(), choices.end()), choices.end());

	for (int k = 0; k < choices.size(); k++) {
		if (ans == choices[k]) { ans++; }
		else { break; }
	}

	return mex[i][j] = ans;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
			mex[i][j] = -1;

	int t; cin >> t;
	while (t--) {
		int k; cin >> k;

		int ans = 0;
		for (int i = 0; i < k; i++){
			int x, y; cin >> x >> y; x--; y--;
			ans ^= getMex(x, y);
		}

		if (ans > 0) { cout << "First" << '\n'; }
		else { cout << "Second" << '\n'; }
	}
}
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll mod = 998244353;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int h, w, k; cin >> h >> w >> k;
	vector<vector<char>> ins(h, vector<char>(w, '.'));
	vector<vector<ll>> grid(h, vector<ll>(w, 0)); grid[0][0] = 1;
	for (int i = 0; i < k; i++) {
		int hi, wi; cin >> hi >> wi; hi--; wi--;
		cin >> ins[hi][wi];
	}

	vector<ll> pow3(max(h, w), 1);
	for (int i = 1; i < pow3.size(); i++) { pow3[i] = pow3[i - 1] * 3; pow3[i] %= mod; }

	vector<vector<int>> jokersH(h + 1, vector<int>(w + 1, 0));
	vector<vector<int>> jokersV(h + 1, vector<int>(w + 1, 0));
	for (int i = h - 1; i >= 0; i--) {
		for (int j = w - 1; j >= 0; j--) {
			if (ins[i][j] == '.') { jokersH[i][j] = jokersV[i][j] = 1; }
			jokersV[i][j] += jokersV[i + 1][j];
			jokersH[i][j] += jokersH[i][j + 1];
		}
	}

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			int addD = 0, addR = 0;
			if (ins[i][j] == 'R') { addR++; }
			else if (ins[i][j] == 'D') { addD++; }
			else if (ins[i][j] == 'X') { addD++; addR++; }
			else { addD = addR = 2; }
			if (j < w - 1) { 
				ll add = addR * grid[i][j]; add %= mod;
				add *= pow3[jokersV[i + 1][j]]; add %= mod;
				grid[i][j + 1] += add; grid[i][j + 1] %= mod;
			}
			if (i < h - 1) {
				ll add = addD * grid[i][j]; add %= mod;
				add *= pow3[jokersH[i][j + 1]]; add %= mod;
				grid[i + 1][j] += add; grid[i + 1][j] %= mod;
			}
		}
	}
	if (ins[h - 1][w - 1] == '.') { grid[h - 1][w - 1] *= 3; grid[h - 1][w - 1] %= mod; }

	cout << grid[h - 1][w - 1] << '\n';
}
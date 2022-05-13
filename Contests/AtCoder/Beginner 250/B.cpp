#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, a, b; cin >> n >> a >> b;
	vector<vector<char>> grid(n * a, vector<char>(n * b, '.'));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if ((i + j) % 2) {
				for (int ii = i * a; ii < (i + 1) * a; ii++) {
					for (int jj = j * b; jj < (j + 1) * b; jj++) {
						grid[ii][jj] = '#';
					}
				}
			}
		}
	}

	for (auto& v : grid) {
		for (auto& c : v) { cout << c; }
		cout << '\n';
	}
}

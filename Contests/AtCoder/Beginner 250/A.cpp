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

	int h, w; cin >> h >> w;
	int r, c; cin >> r >> c;
	int ans = 0;

	for (int i = 1; i <= h; i++) {
		for (int j = 1; j <= w; j++) {
			if (abs(i - r) + abs(c - j) == 1) { ans++; }
		}
	}

	cout << ans << '\n';
}

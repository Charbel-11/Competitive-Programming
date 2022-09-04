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

	int t; cin >> t;
	while (t--) {
		int n, H, M; cin >> n >> H >> M;

		int minutes = H * 60 + M, ansMin = 24 * 60;
		for (int i = 0; i < n; i++) {
			int curH, curM; cin >> curH >> curM;
			int curMin = curH * 60 + curM;
			if (curMin >= minutes) { ansMin = min(ansMin, curMin - minutes); }
			else { ansMin = min(ansMin, 24 * 60 - (minutes - curMin)); }
		}

		cout << ansMin / 60 << " " << ansMin % 60 << '\n';
	}
}

#include <iostream>
#include <string>
#include <map>
#include <set>
#include <iomanip>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

double dist(pair<int, int>& p1, pair<int, int>& p2) {
	int dx = p1.first - p2.first, dy = p1.second - p2.second;
	return sqrt(dx * dx + dy * dy);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int N; cin >> N;
	vector<pair<int, int>> pts(N);
	for (auto& p : pts) { cin >> p.first >> p.second; }

	double ans = dist(pts[0], pts[1]);
	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++) {
			ans = max(ans, dist(pts[i], pts[j]));
		}
	}

	cout << fixed << setprecision(7) << ans << '\n';
}
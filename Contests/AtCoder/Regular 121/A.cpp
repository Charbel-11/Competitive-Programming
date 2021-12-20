#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int dist(pair<int, int>& p1, pair<int, int>& p2) {
	int dx = abs(p1.first - p2.first);
	int dy = abs(p1.second - p2.second);
	return max(dx, dy);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	vector<pair<int, int>> pts(n);
	for (auto& p : pts) { cin >> p.first >> p.second; }
	sort(pts.begin(), pts.end());

    vector<pair<int, int>> minMax;
	minMax.push_back(pts[0]); minMax.push_back(pts.back());
    pair<int, int> minY, maxY; minY = maxY = pts[1];
	int minYIdx = 1, maxYIdx = 1;

	for (int i = 2; i < n - 1; i++) {
		if (pts[i].second < minY.second) { minY = pts[i]; minYIdx = i; }
		else if (pts[i].second > maxY.second) { maxY = pts[i]; maxYIdx = i; }
	}
    minMax.push_back(minY); minMax.push_back(maxY);

    vector<int> distances;
	for (int i = 1; i < n - 1; i++) {
        if (i == minYIdx || i == maxYIdx){ continue; }
        for(auto &p : minMax)
            distances.push_back(dist(pts[i], p));
	}

    for(int i = 0; i < minMax.size(); i++) {
        for (int j = i + 1; j < minMax.size(); j++) {
            distances.push_back(dist(minMax[i], minMax[j]));
        }
    }

	sort(distances.rbegin(), distances.rend());
	cout << distances[1] << '\n';
}

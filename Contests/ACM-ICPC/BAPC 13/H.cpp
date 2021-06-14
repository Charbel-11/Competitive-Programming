#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;
int n;

//Polygon area
ll area(vector<pair<int, int>> &p) {
	ll a = 0;
	for (int i = 0; i < n; i++) {
		a += (p[i].first*p[i + 1].second - p[i + 1].first*p[i].second);
	}
	return abs(a);
}

void rotatePoint(double &x, double &y, double angle) {
	double X = x * cos(angle) - y * sin(angle);
	double Y = x * sin(angle) + y * cos(angle);
	x = X; y = Y;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	cin >> n;
	vector<pair<int, int>> points(n);
	for (auto &p : points) { cin >> p.first >> p.second; }

	ll totArea = area(points);

	int camX = (points[0].first + points[1].first) / 2;
	int camY = (points[0].second + points[1].second) / 2;


}
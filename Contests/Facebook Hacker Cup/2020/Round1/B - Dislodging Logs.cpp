#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <fstream>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

vector<pair<ll, bool>> points;	//0 = log, 1 = driver

bool check(ll time) {
	bool state = 0;
	int NM = points.size();

	int curDriver = -1, nextDriver = -1, leftmostLog = -1;
	ll left = 0, right = 0;
	for (int i = 0; i < NM; i++) {
		if (!state) {
			if (points[i].second) { 
				if (leftmostLog != -1 && (points[i].first - points[leftmostLog].first > time)) { return false; }
				else if (leftmostLog != -1) { 
					left = points[i].first - points[leftmostLog].first;
					leftmostLog = -1;
				}
				else { left = 0; }
				curDriver = i; state = 1;
			}
			else if (leftmostLog == -1) { leftmostLog = i; }
		}
		else {
			if (points[i].second) { nextDriver = i; continue; }

			right = points[i].first - points[curDriver].first;
			ll timeNeeded = min(left, right) + left + right;
			if (timeNeeded > time) {
				if (nextDriver != -1 && (points[i].first - points[nextDriver].first <= time))
				{
					left = 0;
					curDriver = nextDriver;
					nextDriver = -1;
				}
				else {
					curDriver = nextDriver = -1;
					state = 0; leftmostLog = i;
				}
			}
		}
	}

	return state;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	ifstream ifs("input.txt");
	ofstream ofs("out.txt");

	int t; ifs >> t;

	for (int qq = 1; qq <= t; qq++) {
		points.clear();
		int N, M, K, S; ifs >> N >> M >> K >> S;	//S=0

		for (int i = 0; i < K; i++) {
			ll temp; ifs >> temp;
			points.push_back({ temp, 1 });
		}
		ll AP, BP, CP, DP; ifs >> AP >> BP >> CP >> DP;
		for (int i = K; i < N; i++) {
			ll cur = AP * points[i - 2].first; cur %= DP;
			cur = cur + (BP*points[i - 1].first) % DP; cur %= DP;
			cur += CP; cur %= DP;
			cur++;
			points.push_back({ cur, 1 });
		}

		for (int i = 0; i < K; i++) {
			ll temp; ifs >> temp;
			points.push_back({ temp, 0 });
		}
		ll AQ, BQ, CQ, DQ; ifs >> AQ >> BQ >> CQ >> DQ;
		for (int i = N + K; i < N + M; i++) {
			ll cur = AQ * points[i - 2].first; cur %= DQ;
			cur = cur + (BQ*points[i - 1].first) % DQ; cur %= DQ;
			cur += CQ; cur %= DQ;
			cur++;
			points.push_back({ cur, 0 });
		}
		sort(points.begin(), points.end());

		ll l = 0, r = points.back().first * 2;
		while (l < r) {
			ll mid = (l + r) >> 1;
			if (check(mid)) { r = mid; }
			else { l = mid + 1; }
		}

		ofs << "Case #" << qq << ": " << l << '\n';
	}
}
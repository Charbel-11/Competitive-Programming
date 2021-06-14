#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct timee {
	int start, end;
	int idx;

	timee(int s, int e, int i) :start(s), end(e), idx(i) {}

	bool operator <(const timee &rhs) {
		if (start != rhs.start) { return start < rhs.start; }
		return end < rhs.end;
	}
};

int main() {
	int T; cin >> T;
	for (int q = 1; q <= T; q++) {
		int N; cin >> N;
		vector<timee> times;
		for (int i = 0; i < N; i++) {
			int u, v; cin >> u >> v;
			times.push_back(timee(u, v, i));
		}
		sort(times.begin(), times.end());

		string ans(N, 'C'); bool OK = true;
		int endC = times[0].end, endJ = 0;
		for (int i = 1; i < N; i++) {
			if (times[i].start >= endC) {
				endC = times[i].end;
			}
			else if (times[i].start >= endJ) {
				ans[times[i].idx] = 'J'; endJ = times[i].end;
			}
			else {
				OK = false; break;
			}
		}

		cout << "Case #" << q << ": ";
		if (!OK) { cout << "IMPOSSIBLE" << endl; }
		else { 
			for (int i = 0; i < ans.size(); i++) {
				cout << ans[i];
			}
			cout << endl;
		}
	}
}
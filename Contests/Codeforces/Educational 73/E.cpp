#include <string>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

int DP[300002][2];
int a, b;
string s;

//p = 0: Alice
int mex(int i, bool p) {
	if (DP[i][p] != -1) { return DP[i][p]; }
	if (!p) {
		if (a >= i) { return a==i; }
	}
	else {
		if (b >= i) { return b==i; }
	}

	set<int> ms;
	int remove = p ? b : a;
	int x = i - remove;
	for (int j = 0; j <= x/2; j++) {
		ms.insert(mex(j, !p) ^ mex(x - j, !p));
	}

	int count = 0;
	for (auto y : ms) {
		if (y == count) { count++; }
		else { break; }
	}

	DP[i][p] = count; return count;
}

void resetDP(int n) {
	for (int i = 0; i < n; i++) { DP[i][0] = -1; DP[i][1] = -1; }
}

int main() {
	int q; cin >> q;
	for (int z = 0; z < q; z++) {
		cin >> a >> b;
		cin >> s;
		resetDP(s.size());

		vector<int> events;
		int pts = 0; 
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == '.') { pts++; }
			else { 
				if (pts) {
					events.push_back(pts);
					pts = 0;
				}
			}
		}
		if (pts) { events.push_back(pts); }

		if (events.size() == 0) { cout << "NO" << endl; continue; }
		int xors = mex(events[0], 1);
		for (int i = 1; i < events.size(); i++) {
			xors ^= mex(events[i], 1);
		}

		set<int> ms; bool stop = false;
		for (int i = 0; i < events.size(); i++) {
			if (events[i] < a) { continue; }
			
			int res = xors ^ mex(events[i], 1);
			if (events[i] == a) { ms.insert(res); continue; }
			int x = events[i] - a;
			for (int j = 0; j <= x / 2; j++) {
				res ^= mex(j, 1);
				res ^= mex(x - j, 1);
				ms.insert(res);
				if (res == 0) { stop = true; break; }
			}
			if (stop) { break; }
		}
		if (stop) {
			cout << "YES" << endl;
			continue; 
		}

		int answ = 0;
		for (auto y : ms) {
			if (y == answ) { answ++; }
			else { break; }
		}

		if (answ) { cout << "YES" << endl; }
		else { cout << "NO" << endl; }
	}
}
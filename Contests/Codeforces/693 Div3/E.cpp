#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct person {
	int w, h, id;
	person(int _w, int _h, int _id) :w(_w), h(_h), id(_id) {}
	bool operator <(person& rhs) {
		if (w == rhs.w) { return h > rhs.h; }
		return w < rhs.w;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while (t--) {
		int n; cin >> n; 
		vector<person> f; vector<int> ws;
		for (int i = 0; i < n; i++) {
			int w, h; cin >> w >> h; ws.push_back(w);
			f.push_back(person(w, h, i));
		}
		sort(f.begin(), f.end()); sort(ws.begin(), ws.end());

		vector<int> pMin(n, INT_MAX), pMinIdx(n, -1);
		vector<int> ans(n, -1); 
		for (int i = 0; i < n; i++) {
			if (i) { pMin[i] = pMin[i - 1]; pMinIdx[i] = pMinIdx[i - 1]; }
			if (pMin[i] > f[i].h) { pMin[i] = f[i].h; pMinIdx[i] = f[i].id; }
		}

		for (int i = 0; i < n; i++) {
			int j = lower_bound(ws.begin(), ws.end(), f[i].h) - ws.begin() - 1;
			if (j >= 0 && pMin[j] < f[i].w) { ans[f[i].id] = pMinIdx[j] + 1; }
			if (pMin[i] < f[i].h) { ans[f[i].id] = pMinIdx[i] + 1; }
		}

		for (auto& x : ans) { cout << x << ' '; }
		cout << '\n';
	}
}
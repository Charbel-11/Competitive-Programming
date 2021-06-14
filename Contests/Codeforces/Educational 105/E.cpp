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

	int n, q; cin >> n >> q;
	set<pair<int, int>> edges;
	set<pair<int, int>> equalE;
	set<pair<int, int>> uE;
	map<pair<int, int>, char> m;
	while (q--) {
		char c; cin >> c;
		if (c == '+') {
			int u, v; cin >> u >> v >> c;
			edges.insert({ u,v });
			m[{u, v}] = c;
			if (edges.count({ v, u })) {
				uE.insert({ min(u,v), max(u,v) });
				if (m[{v, u}] == c) { equalE.insert({ min(u,v), max(u,v) }); }
			}
		}
		else if (c == '-') {
			int u, v; cin >> u >> v;
			edges.erase({ u,v });
			if (edges.count({ v, u })) {
				uE.erase({ min(u,v), max(u,v) });
				if (m[{v, u}] == m[{u, v}]) { equalE.erase({ min(u,v), max(u,v) }); }
				m.erase({ u,v });
			}
		}
		else {
			int k; cin >> k;
			if (uE.empty()) { cout << "NO" << '\n'; continue; }
			if (!equalE.empty() || k % 2) { cout << "YES" << '\n'; continue; }
			cout << "NO" << '\n'; 
		}
	}
}
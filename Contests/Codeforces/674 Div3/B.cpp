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

struct tile {
	int tl, tr, bl, br;
	bool checked;
	tile(int _tl, int _tr, int _bl, int _br) :tl(_tl), tr(_tr), bl(_bl), br(_br), checked(false) {}

	bool operator==(tile &rhs) {
		return (tl == rhs.tl && tr == rhs.tr && bl == rhs.bl && br == rhs.bl);
	}
	bool symmetric() {
		return (bl == tr);
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;

	while (t--) {
		int n, m; cin >> n >> m; 
		vector<tile> tiles;
		for (int i = 0; i < n; i++) {
			int tl, tr, bl, br; cin >> tl >> tr >> bl >> br;
			tiles.push_back(tile(tl, tr, bl, br));
		}
		if (m % 2) { cout << "NO" << '\n'; continue; }

		bool ss = false;
		for (int i = 0; i < n; i++) {
			if (tiles[i].symmetric()) { ss = true; break; }
		}

		if (ss) { cout << "YES\n"; }
		else { cout << "NO\n"; }
	}
}
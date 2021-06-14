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

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;

	while (t--) {
		int n; cin >> n;
		vector<int> p(n), pos(n);
		for (int i = 0; i < n; i++) {
			cin >> p[i]; p[i]--;
			pos[p[i]] = i;
		}

		vector<bool> used(n, 0); bool OK = true;
		int restriction = -1, r = n-1;
		for (int i = 0; i < n; i++) {
			used[pos[i]] = 1;
			if (restriction == -1) {
				if (pos[i] == r) { r--; continue; }
				restriction = pos[i] + 1;
			}
			else {
				if (pos[i] != restriction) { OK = false; break; }
				if (restriction == r) { 
					restriction = -1; 
					while (r >= 0 && used[r]) { r--; } 
				}
				else { restriction++; }
			}
		}
		cout << (OK ? "Yes" : "No") << endl;
	}
}
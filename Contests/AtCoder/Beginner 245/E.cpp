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

	int n, m; cin >> n >> m;
	vector<pair<int, int>> choc(n), boxes(m);
	for (int i = 0; i < n; i++) { cin >> choc[i].first; }
	for (int i = 0; i < n; i++) { cin >> choc[i].second; }
	for (int i = 0; i < m; i++) { cin >> boxes[i].first; }
	for (int i = 0; i < m; i++) { cin >> boxes[i].second; }

	sort(boxes.begin(), boxes.end());
	sort(choc.begin(), choc.end());

	bool OK = true;
	multiset<int> lengths; int boxIdx = m - 1;
	for (int i = n - 1; i >= 0; i--) {
		while (boxIdx >= 0 && boxes[boxIdx].first >= choc[i].first) {
			lengths.insert(boxes[boxIdx].second);
			boxIdx--;
		}
		auto it = lengths.lower_bound(choc[i].second);
		if (it == lengths.end()) { OK = false; break; }
		lengths.erase(it);
	}

	cout << (OK ? "Yes" : "No") << '\n';
}

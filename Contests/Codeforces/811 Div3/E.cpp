#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

bool canBeEqual(int x, int y) {
	x += (x % 10);
	if (x > y) { y += (y % 10); }
	if (x > y) { swap(x, y); }
	
	int cycles = (y - x) / 20;
	x += cycles * 20;

	if (x == y) { return true; }
	for (int i = 0; i < 10; i++) {
		x += x % 10;
		if (x == y) { return true; }
		if (x > y) { swap(x, y); }
	}

	return false;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		vector<int> a(n); for (auto& x : a) { cin >> x; }
		sort(a.begin(), a.end());
		a.erase(unique(a.begin(), a.end()), a.end());
		
		n = a.size();
		if (n == 1) { cout << "YES" << '\n'; continue; }

		vector<int> freq(10, 0);
		for (int i = 0; i < n; i++) {
			freq[a[i] % 10]++;
		}

		if (freq[0] > 1) { cout << "NO" << '\n'; continue; }
		else if (freq[0] == 1 && n > 2) { cout << "NO" << '\n'; continue; }
		else if (freq[0] == 1) {
			bool OK = true;
			if (freq[5] == 0) { OK = false; }
			if (!(a[0] % 10 == 5 && a[0] + 5 == a[1])) { OK = false; }

			if (!OK) { cout << "NO" << '\n'; }
			else { cout << "YES" << '\n'; }
			continue;
		}

		if (freq[5] > 0) { cout << "NO" << '\n'; continue; }

		bool OK = true;
		for (int i = 0; i < n - 1; i++) {
			if (!canBeEqual(a[i], a[i + 1])) { OK = false; break; }
		}

		if (!OK) { cout << "NO" << '\n'; }
		else { cout << "YES" << '\n'; }
	}
}

// 5->0->5
// 1->2->4->8->6->2
// 2->4->8->6->2
// 3->6->2->4->8->6
// 7->4->8->6->2->4
// 9->8->6->2->4->8
// cycle adds 20 -> need difference to be a multiple of 20 + 4 cases (simulate 4 times)
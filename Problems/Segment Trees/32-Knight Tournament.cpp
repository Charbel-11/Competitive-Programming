#include <string>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

int main() {
	int n, m;
	cin >> n >> m;

	vector<int> answ(n + 1, 0);
	set<int> knights;
	for (int i = 1; i <= n; i++) {
		knights.insert(i);
	}

	for (int i = 0; i < m; i++) {
		int l, r, w;
		cin >> l >> r >> w;

		set<int>::iterator itr = knights.lower_bound(l);
		while (itr != knights.end() && *itr <= r) {
			int cur = *itr;
			itr++;
			if (cur != w) {
				answ[cur] = w;
				knights.erase(cur);
			}
		}
	}

	for (int i = 1; i <= n; i++) {
		cout << answ[i] << " ";
	}
	cout << endl;
}
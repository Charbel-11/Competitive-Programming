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

int query(int i, int j) {
	cout << "? " << i + 1 << " " << j + 1 << endl;
	int ans; cin >> ans;
	if (ans == -1) { exit(0); }
	return ans;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	int a = 0, b = 1;
	int q1 = query(a, b);
	
	for (int c = 2; c < n; c++) {
		int q2 = query(b, c);
		if (q1 > q2) { a = c; q1 = q2; }
		else if (q2 > q1) { continue; }
		else { b = c; q1 = query(a, b); }
	}

	int zero = -1;
	set<int> used; used.insert(a); used.insert(b);
	while (true) {
		int r = rand() % n;
		while (used.count(r)) { r = rand() % n; }
		used.insert(r);
		q1 = query(a, r); int q2 = query(r, b);
		if (q1 == q2) { continue; }
		if (q1 < q2) { zero = a; }
		else { zero = b; }
		break;
	}

	vector<int> ans(n, 0);
	for (int i = 0; i < n; i++) {
		if (i == zero) { continue; }
		ans[i] = query(zero, i);
	}

	cout << "! ";
	for (auto &x : ans) { cout << x << ' '; }
	cout << endl;
}
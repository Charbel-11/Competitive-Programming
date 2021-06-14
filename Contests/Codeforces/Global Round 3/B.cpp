#include <iostream>
#include <string>
#include <vector>

using namespace std;
int n, m;
vector<int> a;
vector<int> b;


int maxTime(int i, int j, int k) {
	if (i >= n || j >= m) {
		return -1;
	}

	while (j < m && b[j] < a[i]) {
		j++;
	}

	if (k == 0) {
		if (j >= m) { return -1; }
		return b[j];
	}

	int c1 = maxTime(i + 1, j, k - 1);
	int c2 = maxTime(i, j + k, 0);

	if (c1 == -1 || c2 == -1) {
		return -1;
	}

	return c1 > c2 ? c1 : c2;
}

int main() {
	int ta, tb, k;
	cin >> n >> m >> ta >> tb >> k;

	for (int i = 0; i < n; i++) {
		int t;
		cin >> t;
		a.push_back(t+ta);
	}
	for (int i = 0; i < m; i++) {
		int t;
		cin >> t;
		b.push_back(t);
	}
	//both sorted

	if (k >= m || k >= n) {
		cout << -1 << endl;
		return 0;
	}

	int res = maxTime(0,0,k);
	if (res == -1) {
		cout << -1 << endl;
	}
	else {
		cout << tb + res << endl;
	}
}
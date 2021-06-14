#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int n, m;
	cin >> n >> m;

	vector<vector<int>> answ(m);
	for (int i = 0; i < m; i++) {
		answ[i] = vector<int>(5, 0);
	}

	for (int i = 0; i < n; i++) {
		string cur;
		cin >> cur;

		for (int j = 0; j < m; j++) {
			answ[j][cur[j] - 'A']++;
		}
	}

	long long res = 0;
	for (int i = 0; i < m; i++) {
		int points;
		cin >> points;

		sort(answ[i].begin(), answ[i].end());
		res += answ[i][4]*points;
	}

	cout << res << endl;
}
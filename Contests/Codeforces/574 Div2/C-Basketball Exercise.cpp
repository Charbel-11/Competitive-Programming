#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> t1;
vector<int> t2;
long long DP[100002][2];

long long maxHeight(int i, int t) {
	if (i >= t1.size()) { return 0; }

	if (DP[i][t] != -1) {
		return DP[i][t];
	}

	long long c1, c2;
	if (t==0){
		c1 = t1[i] + maxHeight(i + 1, !t);
		c2 = maxHeight(i + 1, t);
	}
	else {
		c1 = t2[i] + maxHeight(i + 1, !t);
		c2 = maxHeight(i + 1, t);
	}

	DP[i][t] = c1 > c2 ? c1 : c2;
	return DP[i][t];
}

void resetDP() {
	for (int i = 0; i < 100002; i++) {
		for (int j = 0; j < 2; j++) {
			DP[i][j] = -1;
		}
	}
}

int main() {
	int n;
	cin >> n;

	for (int i = 0; i < n; i++) {
		long long temp;
		cin >> temp;
		t1.push_back(temp);
	}
	for (int i = 0; i < n; i++) {
		long long temp;
		cin >> temp;
		t2.push_back(temp);
	}

	resetDP();

	long long c1 = maxHeight(0, 0);
	long long c2 = maxHeight(0, 1);
	long long res = c1 > c2 ? c1 : c2;

	cout << res << endl;
}
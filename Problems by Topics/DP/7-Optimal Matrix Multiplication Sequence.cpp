#include <iostream>
#include <string>
#include <climits>
#include <vector>
using namespace std;

int DP[12][12];
int Choice[12][12];
vector<pair<int, int>> A;

int findMin(int i, int j) {
	if (i > j) { return 0; }
	if (DP[i][j] != -1) { return DP[i][j]; }
	if (i == j) { return DP[i][j] = 0; }

	int min = INT_MAX;
	//We are cutting between the numbers; not on them so j-1 last choice and k represents the right operator of a number
	for (int k = i; k < j; k++) {
		int left = findMin(i, k); int right = findMin(k + 1, j);
		int cur = left + right + A[i].first * A[k].second * A[j].second;

		if (cur < min) { Choice[i][j] = k; min = cur; }
	}

	DP[i][j] = min; return min;
}

string createOutput(int start, int end) {
	if (start == end) { return "A" + to_string(start + 1); }
	if (start > end || Choice[start][end] == -1) { return ""; }
	int k = Choice[start][end];

	return "(" + createOutput(start, k) + " x " + createOutput(k + 1, end) + ")";
}

void resetDP() {
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			DP[i][j] = -1; Choice[i][j] = -1;
		}
	}
}

int main() {
	int caseNum = 1; int N; cin >> N;
	while (N != 0) {
		A.resize(N); for (auto &x : A) { cin >> x.first >> x.second; }
		resetDP();

		int min = findMin(0, N - 1); string res = createOutput(0, N - 1);
		cout << "Case " << caseNum << ": " << res << endl;

		caseNum++; cin >> N;
	}
}
//https://community.topcoder.com/stat?c=problem_statement&pm=11537
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;
long long mod = 1000000007;
long long DP[52][52];
vector<int> nums;
pair<int, int> pre[52][52];

long long comb[52][52];

//A choose B
long long choose(long long A, long long B) {
	if (A == B || B == 0) {
		return 1;
	}
	if (comb[A][B] != -1) { return comb[A][B]; }

	long long p1 = choose(A - 1, B - 1);
	long long p2 = choose(A - 1, B);
	p1 %= mod; p2 %= mod;

	comb[A][B] = (p1 + p2) % mod;
	return comb[A][B];
}

void resetComb() {
	for (int i = 0; i < 52; i++)
		for (int j = 0; j < 52; j++)
			comb[i][j] = -1;
}

bool check(int x, int i, int j) {
	return x == pre[i][j].first || x == pre[i][j].second;
}

int goodPerm(int i, int j) {
	if (DP[i][j] != -1) { return DP[i][j]; }
	if (j == i + 1) { DP[i][j] = nums[i] > nums[j]; return DP[i][j]; }

	int l = pre[i][j].first; int r = pre[i][j].second;

	long long res = 0;

	if (i + 1 == nums[i]) { res += goodPerm(i + 1, j); res %= mod; }
	if (j - 1 == nums[j]) { res += goodPerm(i, j - 1); res %= mod; }

	for (int k = i + 1; k < j - 1; k++) {
		if (!check(l, i, k) || !check(k + 1, i, k) || !check(k, k + 1, j) || !check(r, k + 1, j)) { continue; }
		long long a;
		long long b;

		a = goodPerm(i, k) % mod;
		b = goodPerm(k + 1, j) % mod;
		long long c = (a*b) % mod;
		res += choose(j - i - 1, k - i) * c; res %= mod;
	}

	DP[i][j] = res;
	return DP[i][j];
}

void resetDP() {
	for (int i = 0; i < 52; i++)
		for (int j = 0; j < 52; j++)
			DP[i][j] = -1;
}

int main() {
	char c;
	cin >> c;
	while (c != '}') {
		int a; cin >> a >> c;
		nums.push_back(a);
	}

	int n = nums.size();

	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			set<long long> sortedN;
			for (int k = i; k <= j; k++) {
				sortedN.insert(nums[k]);
			}
			bool missing = 0;
			for (int k = i + 1; k <= j - 1; k++) {
				if (sortedN.count(k) != 0) {
					sortedN.erase(k);
				}
				else {
					missing = 1; break;
				}
			}
			if (missing || sortedN.size() > 2) { pre[i][j] = { -1,-1 }; }
			else {
				pre[i][j] = { *sortedN.begin(), *next(sortedN.begin()) };
			}
		}
	}

	resetComb();
	resetDP();

	cout << goodPerm(0, n - 1) << endl;
}
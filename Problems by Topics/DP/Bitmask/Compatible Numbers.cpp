// https://codeforces.com/contest/165/problem/E

#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;
const int M = (1 << 22);

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n; 
	vector<int> a(n), dp(M, -1);
	for (int i = 0; i < n; i++) {
		cin >> a[i]; dp[a[i]] = a[i];
	}

	for (int mask = 2; mask < M; mask++) {
		for (int i = 0; i < 22; i++) {
			if (!((1 << i) & mask)) { continue; }
			int prevM = mask ^ (1 << i);
			dp[mask] = max(dp[mask], dp[prevM]);
		}
	}

	int allOnes = M - 1;
	for (int i = 0; i < n; i++) {
		int curFlipped = a[i] ^ allOnes;
		cout << dp[curFlipped] << ' ';
	}
}
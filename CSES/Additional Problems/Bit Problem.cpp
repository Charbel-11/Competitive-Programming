#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

const int M = 1 << 21;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	vector<int> freq(M, 0), x(n);
	for (int i = 0; i < n; i++) {
		cin >> x[i]; 
		freq[x[i]]++;
	}

	vector<int> dp1(M, 0), dp2(M, 0);
	for (int i = 0; i < M; i++) { dp1[i] = dp2[i] = freq[i]; }

	for (int k = 0; k < 21; k++) {
		for (int i = M - 1; i >= 0; i--) {
			if (i & (1 << k)) { dp1[i] += dp1[i ^ (1 << k)]; }
		}
	}

	for (int k = 0; k < 21; k++) {
		for (int i = 0; i < M; i++) {
			if (!(i & (1 << k))) { dp2[i] += dp2[i ^ (1 << k)]; }
		}
	}

	for (int i = 0; i < n; i++) {
		int dp3 = n - dp1[((1 << 21) - 1) ^ x[i]];
		cout << dp1[x[i]] << " " << dp2[x[i]] << " " << dp3 << '\n';
	}
}
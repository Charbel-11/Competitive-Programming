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

int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

const int SVSZ = 10000001;
int spf[SVSZ];

void buildSieve() {
	vector<int> primes; spf[0] = spf[1] = 1;
	for (int i = 2; i < SVSZ; i++) {
		if (spf[i] == 0) { primes.push_back(i);	spf[i] = i; }
		for (int j = 0; j < int(primes.size()) && primes[j] <= spf[i] && i * primes[j] < SVSZ; j++)
			spf[i * primes[j]] = primes[j];
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	buildSieve();
	int n; cin >> n;
	vector<int> nums(n);
	for (auto &x : nums) { cin >> x; }

	vector<pair<int, int>> res(n, { -1,-1 });

	for (int i = 0; i < n; i++) {
		vector<int> curP; int initialNum = nums[i];
		while (nums[i] > 1) {
			curP.push_back(spf[nums[i]]);
			while (nums[i] % curP.back() == 0) { nums[i] /= curP.back(); }
		}

		if (curP.size() <= 1) { continue; }

		int x = curP[0], y = 1;
		for (int i = 1; i < curP.size(); i++) { y *= curP[i]; }
		res[i] = { x,y };
	}

	for (int i = 0; i < n; i++) {
		cout << res[i].first << ' ';
	}
	cout << '\n';
	for (int i = 0; i < n; i++) {
		cout << res[i].second << ' ';
	}
}
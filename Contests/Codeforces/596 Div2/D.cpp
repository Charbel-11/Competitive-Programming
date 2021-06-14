#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>

using namespace std;
long long p[(int)1e5 + 1];

void sieve2() {
	for (int i = 0; i < 1e5 + 1; i++) { p[i] = i; }
	for (int i = 2; i < 1e5 + 1; i++) {
		if (p[i] != i) { continue; }
		for (int j = i + i; j < 1e5 + 1; j+=i) {
			p[j] = i;
		}
	}
}

int main() {
	int n, k; cin >> n >> k;
	sieve2();

	map<long long, long long> seen;
	long long res = 0;
	for (int i = 0; i < n; i++) {
		int a; cin >> a;
		long long cur = 1, needed = 1;
		while (a > 1) {
			long long curP = p[a];
			int rep = 0;
			while (a%curP == 0) {
				rep++; a /= curP;
			}
			rep %= k;
			if (rep == 0) { continue; }
			for (int i = 0; i < rep; i++) {
				cur *= curP;
			}
			for (int i = 0; i < k - rep; i++) {
				needed *= curP;
			}
		}
		res += seen[needed];
		seen[cur]++;
	}

	cout << res << endl;
}
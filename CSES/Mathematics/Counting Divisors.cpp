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

int nDiv[(int)1e6 + 5];

void sieve() {
	for (int i = 1; i < (int)1e6 + 5; i++)
		for (int j = i; j < (int)1e6 + 5; j += i)
			nDiv[j]++;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	sieve();
	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		cout << nDiv[n] << '\n';
	}
}
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

int main() {
	int n; cin >> n;
	int k = n / 2, l = 0;
	while (true) {
		cout << k << ' ';
		if (k == 0) { return 0; }
		for (int i = 0; i < k; i++) {
			int idx = (l + 2 * i) % n;
			cout << idx + 1 << ' ';
		}
		cout << endl;
		cin >> l; if (l == -1) { return 0; }
		k /= 2; l--;
		if (l % 2) { l++; l %= n; }
		if (n % 2 && l == n - 1) { l = 0; }
	}
}
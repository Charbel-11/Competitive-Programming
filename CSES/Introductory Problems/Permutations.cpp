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
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	if (n == 1) { cout << 1 << '\n'; return 0; }
	if (n == 4) { cout << "2 4 1 3\n"; return 0; }
	if (n < 5) { cout << "NO SOLUTION\n"; return 0; }

	int add = (n + 1) / 2;
	for (int i = 0; i < n / 2; i++) {
		cout << i + 1 << ' ' << i + 1 + add << ' ';
	}
	if (n % 2) { cout << n / 2 + 1 << '\n'; }
}
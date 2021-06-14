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

	int n, x, y; cin >> n >> x >> y; n--;
	if (x > y) { swap(x, y); }
	int l = 0, r = n * y;
	while (l < r) {
		int mid = r - (r - l + 1) / 2;
		if (mid / x + mid / y >= n) { r = mid; }
		else { l = mid + 1; }
	}
	cout << l + x << '\n';
}
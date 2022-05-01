#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int pos(int a, int b, int c, int x) {
	int ans = 0;
	while (x > 0) {
		if (a >= x) { ans += x * b; break; }
		else {
			ans += a * b;
			x = x - (a + c);
		}
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int a, b, c, d, e, f, x;
	cin >> a >> b >> c >> d >> e >> f >> x;
	int p1 = pos(a, b, c, x), p2 = pos(d, e, f, x);

	if (p1 > p2) { cout << "Takahashi" << '\n'; }
	else if (p2 > p1) { cout << "Aoki" << '\n'; }
	else { cout << "Draw" << '\n'; }
}
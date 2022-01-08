#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	ll X; cin >> X;
	ll ans = 1e18;
	for (int start = 1; start < 10; start++) {
		for (int r = -9; r <= 9; r++) {
			ll curN = start;
			int lastDigit = start;
			while (curN < X) {
				lastDigit += r; 
				if (lastDigit > 9 || lastDigit < 0) { break; }
				curN *= 10; curN += lastDigit;
			}
			if (curN >= X) { ans = min(ans, curN); }
		}
	}

	cout << ans << '\n';
}
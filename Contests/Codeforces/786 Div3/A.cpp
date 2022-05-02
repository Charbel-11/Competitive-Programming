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

	int t; cin >> t;
	while (t--) {
		int x, y; cin >> x >> y;
		int ansA = 0, ansB = 0;

		for (int b = 1; b <= 100; b++) {
			int curB = b;
			for (int a = 1; a <= 10; a++) {
				if (x * curB == y) { ansA = a; ansB = b; break; }
				curB *= b;
			}
			if (ansA != 0) { break; }
		}

		cout << ansA << " " << ansB << '\n';
	}
}
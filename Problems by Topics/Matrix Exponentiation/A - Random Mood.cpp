#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	double p; cin >> p;
	double pH = 1.0;

	while (n) {
		if (n & 1) { pH = pH * (1 - p) + (1 - pH)*p; }
		p = p * (1 - p) + (1 - p)*p;
		n >>= 1;
	}

	cout << setprecision(7) << fixed << pH << '\n';
}
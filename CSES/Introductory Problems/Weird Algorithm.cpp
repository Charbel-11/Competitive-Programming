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

	ll n; cin >> n;
	while (n != 1) {
		cout << n << ' ';
		if (n % 2) { n *= 3; n++; }
		else { n /= 2; }
	}
	cout << 1 << '\n';
}
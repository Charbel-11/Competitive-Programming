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
	ll res = 0, pow5 = 5;
	while (n >= pow5) { res += n / pow5; pow5 *= 5; }
	cout << res << '\n';
}
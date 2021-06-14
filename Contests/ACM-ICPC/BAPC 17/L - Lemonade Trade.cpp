//BAPC17 L

#include <iostream>
#include <string>
#include <map>
#include <set>
#include <iomanip>
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
	map<string, double> m;
	double inf = -1e14;
	m["pink"] = 0.0; m["blue"] = inf;

	while (n--) {
		string t, s; cin >> t >> s;
		double d; cin >> d; d = log2(d);
		if (m.count(t) == 0) { m[t] = inf; }
		if (m.count(s) == 0) { m[s] = inf; }
		m[t] = max(m[t], m[s] + d);
	}

	cout << setprecision(7) << min(10.0, pow(2, m["blue"])) << endl;
}
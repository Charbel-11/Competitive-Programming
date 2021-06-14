#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;
typedef long long ll;

int main() {
	ifstream ifs("katryoshka.in");
	int T; ifs >> T;

	for(int z = 0; z < T; z++) {
		ll e, m, b; ifs >> e >> m >> b;

		ll curMin = min(e, min(m, b));
		ll res = curMin;
		e -= curMin; m -= curMin; b -= curMin;

		res += min(e / 2, b);

		cout << "Case " << z + 1 << ": " << res << endl;
	}
}
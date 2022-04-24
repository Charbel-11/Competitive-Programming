#include <iostream>
#include <string>
#include <map>
#include <set>
#include <iomanip>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

const double PI = 3.14159265358979323;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	for (int qq = 1; qq <= t; qq++) {
		ll R, A, B; cin >> R >> A >> B;
		ll ans = 0;

		while (R) {
			ans += R * R;
			R *= A;
			ans += R * R;
			R /= B;
		}

		cout << "Case #" << qq << ": " << setprecision(7) << fixed << (double)ans * PI << '\n';
	}
}

#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	double n, k; cin >> n >> k;
	double ans = 0;
	for (int ma = 1; ma <= k; ma++) {
		double curP = 1, prevP = 1;
		for (int i = 0; i < n; i++) {
			curP *= ma / k; 
			prevP *= (ma - 1) / k;
		}
		curP -= prevP;
		ans += curP * ma;		
	}
	cout << fixed << setprecision(6) << ans << '\n';
}
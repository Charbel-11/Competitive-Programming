#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <fstream>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	ifstream ifs("in.txt");
	ofstream ofs("out.txt");

	int t; ifs >> t;
	for (int qq = 1; qq <= t; qq++) {
		int n; ifs >> n;
		string s; ifs >> s;

		ll ans = 0, ansLastO = 0, ansLastX = 0;
		int lastX = -1, lastO = -1;

		for (int r = 0; r < n; r++) {
			if (s[r] == 'F') {
				if (lastX > lastO) { ans += ansLastX; }
				else { ans += ansLastO; }
			}
			else if (s[r] == 'O') {
				ansLastO = ansLastX + lastX + 1;
				ans += ansLastO; lastO = r;
			}
			else {
				ansLastX = ansLastO + lastO + 1;
				ans += ansLastX; lastX = r;
			}
			ans %= mod;
		}

		ofs << "Case #" << qq << ": " << ans << '\n';
	}
}
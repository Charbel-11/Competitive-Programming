#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	int t; cin >> t;

	while (t--) {
		int n, m; cin >> n >> m;
		while (n != 1) {
			string s(m, 'B'); cout << s << endl;
			n--;
		}
		if (m == 2) {
			cout << "BW" << endl;
		}
		else {
			string s2(m - 2, 'B'); cout << s2 << "WW" << endl;
		}
	}
}
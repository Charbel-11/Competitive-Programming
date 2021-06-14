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

	int t; cin >> t;
	for (int qq = 1; qq <= t; qq++) {
		int n; cin >> n;
		string s; cin >> s;
		cout << "Case #" << qq << ": ";

		int cur = 1; cout << 1 << " ";
		for (int i = 1; i < n; i++) {
			if (s[i] > s[i - 1]) { cur++; }
			else { cur = 1; }
			cout << cur << " ";
		}
		cout << '\n';
	}
}
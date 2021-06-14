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

	while (t--) {
		int n, a, b; cin >> n >> a >> b;
		string s(n, 'a');
		for (int i = 1; i < b; i++) {
			s[i] = 'a' + i;
		}
		for (int i = a; i < n; i++) {
			s[i] = s[i - a];
		}
		cout << s << endl;
	}
}
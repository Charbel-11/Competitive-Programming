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
		int n; cin >> n;
		int a, b, c, d; cin >> a >> b >> c >> d;
		int mini = (a - b)*n, maxi = (a + b)*n;
		if (maxi<c - d || mini>c + d) { cout << "No" << endl; }
		else { cout << "Yes" << endl; }
	}
}
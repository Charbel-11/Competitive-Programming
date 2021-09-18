#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; ll k; cin >> n >> k;
	int l = 1, r = n;
	for (int inv = n - 1; inv >= 0; inv--) {
		if (k >= inv) {
			k -= inv;
			cout << r-- << ' ';
		}
		else { cout << l++ << ' '; }
	}
}
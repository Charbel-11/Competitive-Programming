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

	ll k; cin >> k;

	string ans;
	while (k) {
		if (k & 1) { ans.push_back('2'); }
		else { ans.push_back('0'); }
		k /= 2;
	}
	reverse(ans.begin(), ans.end());

	cout << ans << '\n';
}
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

ll craftCost, nSlots, pileSize, wood;

bool check(ll target) {
	ll curWood = wood;
	ll rem = nSlots - target;
	curWood -= target * craftCost;

	if (rem == 0) { return curWood <= 0; }
	return ((curWood + rem - 1) / rem) <= pileSize;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	cin >> craftCost >> nSlots >> pileSize >> wood;

	ll l = 0;
	ll r = wood / craftCost;

	while (l < r) {
		ll mid = (l + r + 1) / 2ll;
		if (check(mid)) { l = mid; }
		else { r = mid - 1; }
	}
	
	cout << l << '\n';
}
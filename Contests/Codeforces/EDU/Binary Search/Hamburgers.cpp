#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

ll b, s, c;
ll nb, ns, nc;
ll pb, ps, pc;
ll n;

bool check(ll h) {
	ll neededB = b * h, neededS = s * h, neededC = c * h;
	neededB -= nb; neededS -= ns; neededC -= nc;
	neededB = max(neededB, 0ll);
	neededS = max(neededS, 0ll);
	neededC = max(neededC, 0ll);

	return n >= (neededB * pb + neededS * ps + neededC * pc);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	string st; cin >> st;
	for (auto& ch : st) {
		if (ch == 'B') { b++; }
		else if (ch == 'S') { s++; }
		else { c++; }
	}

	cin >> nb >> ns >> nc;
	cin >> pb >> ps >> pc;
	cin >> n;

	ll l = 0, r = 1e15;
	while (l < r) {
		ll mid = (l + r + 1) / 2;
		if (check(mid)) { l = mid; }
		else { r = mid - 1; }
	}
	cout << l << '\n';
}
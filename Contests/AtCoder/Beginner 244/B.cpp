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

	int n; cin >> n;
	string step; cin >> step;
	int x = 0, y = 0, state = 0;

	for (auto& c : step) {
		if (c == 'R') { state++; state %= 4; }
		else if (state == 0) { x++; }
		else if (state == 1) { y--; }
		else if (state == 2) { x--; }
		else { y++; }
	}

	cout << x << ' ' << y << '\n';
}
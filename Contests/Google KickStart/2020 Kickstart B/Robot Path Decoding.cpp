#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;
string in;
int i; ll x, y;

void normalize() {
	while (x > 1000 * 1000 * 1000) {
		x -= 1000 * 1000 * 1000;
	}
	while (x <= 0) {
		x += 1000 * 1000 * 1000;
	}
	while (y > 1000 * 1000 * 1000) {
		y -= 1000 * 1000 * 1000;
	}
	while (y <= 0) {
		y += 1000 * 1000 * 1000;
	}
}

pair<ll, ll> generateStr() {
	ll rep = in[i] - '0';
	i += 2;
	pair<ll, ll> ans = { 0,0 };
	while (in[i] != ')') {
		if (in[i] > '1' && in[i] <= '9') {
			auto p = generateStr();
			ans.first += p.first; ans.second += p.second;
			ans.first %= (1000 * 1000 * 1000);
			ans.second %= (1000 * 1000 * 1000);
		}
		if (in[i] == 'S') { ans.first++; }
		else if (in[i] == 'N') { ans.first--; }
		else if (in[i] == 'W') { ans.second--; }
		else if (in[i]=='E') { ans.second++; }
		i++;
	}
	ans.first *= rep; ans.second *= rep;
	ans.first %= (1000 * 1000 * 1000);
	ans.second %= (1000 * 1000 * 1000);
	return ans;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int T; cin >> T;
	for (int q = 1; q <= T; q++) {
		cin >> in;
		x = y = 1;

		for (i = 0; i < in.size(); i++) {
			if (in[i] > '1' && in[i] <= '9') {
				pair<ll, ll> p = generateStr();
				x += p.first; y += p.second;
				normalize();
			}
			else { 
				if (in[i] == 'N') { x--; if (x == 0) { x = 1000 * 1000 * 1000; } }
				else if (in[i] == 'S') { x++; if (x == 1000 * 1000 * 1000 + 1) { x = 1; } }
				else if (in[i] == 'W') { y--; if (y == 0) { y = 1000 * 1000 * 1000; } }
				else if (in[i] == 'E') { y++; if (y == 1000 * 1000 * 1000 + 1) { y = 1; } }
			}
		}

		cout << "Case #" << q << ": " << y << " " << x << endl;
	}
}
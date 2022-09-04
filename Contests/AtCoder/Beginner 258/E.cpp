#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

const int lg = 50;

int getKth(int x, ll k, vector<vector<int>>& anc) {
	int pow = 0;
	while (k) {
		if ((k % 2) == 1) { x = anc[x][pow]; }
		pow++; k /= 2;
	}
	return x;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, q; ll X; cin >> n >> q >> X;
	ll S = 0;
	vector<ll> W(n); for (auto& x : W) { cin >> x; S += x; }

	ll add = X / S; X %= S;

	vector<vector<int>> anc(n, vector<int>(lg));
	vector<ll> size(n, add * n);

	int r = 0, curSz = 1; ll curS = W[0];
	for (int l = 0; l < n; l++) {
		while (curS < X) {
			r++; r %= n;
			curS += W[r];
			curSz++;
		}
		anc[l][0] = (r + 1) % n;
		size[l] += curSz;
		curS -= W[l]; curSz--;
	}

	for (int i = 1; i < lg; i++) {
		for (int j = 0; j < n; j++) {
			anc[j][i] = anc[anc[j][i - 1]][i - 1];
		}
	}

	while (q--) {
		ll k; cin >> k;
		cout << size[getKth(0, k - 1, anc)] << '\n';
	}
}

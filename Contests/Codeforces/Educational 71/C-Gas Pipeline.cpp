#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

typedef long long ll;
using namespace std;

ll n, a, b; string s;
vector<ll> consZeros;
vector<ll> consOnes;

ll minCost() {
	ll added = 0;
	bool up = false;
	for (int i = n - 2; i >= 0; i--) {
		if (i == 0 && up) { added += a; continue; }
		if (s[i] == '1') {
			ll cons = consOnes[i];
			if (!up) { added += a; }
			added += (cons + 1) * b;
			up = true; i -= cons;
		}
		else {
			int cons = consZeros[i];
			if (cons == 1 && up) { continue; }

			ll c1 = 0, c2 = 0;
			if (up) {
				c1 = 2 * a;
				if (i - cons + 1 == 0) { up = false; added += a; break; }
				c2 = (cons - 1)*b;
			}

			if (c2 > c1) { added += c1; }
			else { added += c2; }

			i -= cons;
		}
		i++;
	}

	return added;
}

int main() {
	int T; cin >> T;

	for (int z = 0; z < T; z++) {
		cin >> n >> a >> b;
		cin >> s;

		consZeros.clear(); consOnes.clear();
		consZeros.resize(n, 0); consOnes.resize(n, 0);
		for (int i = 0; i < n; i++) {
			if (s[i] == '0') {
				consZeros[i]++;
				if (i > 0) { consZeros[i] += consZeros[i - 1]; }
			}
			else {
				consOnes[i]++;
				if (i > 0) { consOnes[i] += consOnes[i - 1]; }
			}
		}

		ll res = (n + 1)*b + n * a;
		res += minCost();

		cout << res << endl;
	}
}
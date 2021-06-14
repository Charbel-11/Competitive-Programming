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

vector<pair<ll, int>> primeFactors(ll x) {
	vector<pair<ll, int>> ans;
	ll num = 2;
	while (x != 1 && num*num <= x) {
		if (x % num == 0) {
			int k = 0;
			while (x % num == 0) {
				x /= num; k++;
			}
			ans.push_back({ num,k });
		}
		num++;
	}
	if (x != 1) { ans.push_back({ x,1 }); }
	return move(ans);
}

int main() {
	ll B, N; cin >> B >> N;

	vector<pair<ll, int>> factors = primeFactors(N);

	bool OK = true;
	vector<ll> digitsBaseB;
	for (auto &p : factors) { 
		if (p.first >= B) { OK = false; break; }
		while (p.second) {
			ll cur = p.first; p.second--;
			while (cur*p.first < B && p.second) {
				p.second--;
				cur *= p.first;
			}
			digitsBaseB.push_back(cur);
		}
	}

	if (!OK) { cout << "impossible" << endl; return 0; }

	sort(digitsBaseB.rbegin(), digitsBaseB.rend());

	ll ans = 0, factor = 1;;
	for (int i = 0; i < digitsBaseB.size(); i++) {
		cout << digitsBaseB[i] << " ";
		ans += digitsBaseB[i] * factor;
		factor *= B;
	}cout << endl;

	cout << ans << endl;
}
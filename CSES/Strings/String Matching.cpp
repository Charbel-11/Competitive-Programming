#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <array>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

ll to_ll(array<ll, 2> a) {
	return ((a[0] << 32) + a[1]);
}

struct RabinKarp {
	const int mod[2] = { (int)1e9 + 7, (int)1e9 + 9 };
	const int prime[2] = { 179, 233 };
	vector<vector<ll>> pPow, h;
	int n;

	RabinKarp(string& s) {
		pPow.resize(s.size() + 5, vector<ll>(2));
		h.resize(s.size() + 5, vector<ll>(2));
		n = s.size(); init(s);
	}

	void init(const string& s) {
		if (!pPow[0][0]) {
			pPow[0][0] = pPow[0][1] = 1;
			for (int i = 1; i <= n; ++i)
				for (int z = 0; z < 2; ++z)
					pPow[i][z] = pPow[i - 1][z] * prime[z] % mod[z];
		}
		for (int i = 0; i < n; ++i)
			for (int z = 0; z < 2; ++z)
				h[i + 1][z] = (h[i][z] * prime[z] + s[i]) % mod[z];
	}

	array<ll, 2> getHash(const string &s) {
		array<ll, 2> curhash = { 0, 0 };
		for (int i = 0; i < s.size(); ++i)
			for (int z = 0; z < 2; ++z)
				curhash[z] = (curhash[z] * prime[z] + s[i]) % mod[z];

		return curhash;
	}

	array<ll, 2> query(const int l, const int r) {	//returns the hash of s[l..r]
		array<ll, 2> res;
		for (int z = 0; z < 2; ++z) {
			res[z] = (h[r + 1][z] - h[l][z] * pPow[r - l + 1][z]) % mod[z];
			if (res[z] < 0) { res[z] += mod[z]; }
		}
		return res;
	}

	//# of times t is a substr of s
	int checkIfSubstr(string &t) {
		int len = t.size();
		ll hashOfT = to_ll(getHash(t));

		int ans = 0;
		for (int i = len - 1; i < n; i++) {
			ll hashOfS = to_ll(query(i - len + 1, i));
			if (hashOfT == hashOfS) { ans++; }
		}

		return ans;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	string a, b; cin >> a >> b;
	RabinKarp rka(a);
	cout << rka.checkIfSubstr(b) << '\n';
}
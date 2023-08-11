#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct custom_hash {
	static ll splitmix64(ll x) {
		x += 0x9e3779b97f4a7c15;
		x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
		x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
		return x ^ (x >> 31);
	}

	ll operator()(ll x) const {
		static const ll FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
		return splitmix64(x + FIXED_RANDOM);
	}
};

int main() {
	unordered_map<ll, ll, custom_hash> m;
}
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>

typedef long long ll;
using namespace std;
const ll mod = 998244353; int n;
vector<ll> factorials;
vector<pair<ll, ll>> nums;

void fillFact() {
	factorials.resize(300002, 1ll);
	for (ll i = 2ll; i < 300002ll; i++) { factorials[i] = factorials[i - 1] * i; factorials[i] %= mod; }
}

bool comp1(const pair<ll, ll> &p1, const pair<ll, ll> &p2) {
	if (p1.first == p2.first) { return p1.second < p2.second; }
	return p1.first < p2.first;
}

bool comp2(const pair<ll, ll> &p1, const pair<ll, ll> &p2) {
	if (p1.second == p2.second) { return p1.first < p2.first; }
	return p1.second < p2.second;
}

ll sorted1() {
	ll res = 1ll;
	for (int i = 0; i < n; i++) {
		int cur = 1;
		while (i < n - 1 && nums[i].first == nums[i + 1].first) { cur++; i++; }
		res *= factorials[cur]; res %= mod;
	}
	return res;
}

ll sorted2() {
	ll res = 1ll;
	for (int i = 0; i < n; i++) {
		int cur = 1;
		while (i < n - 1 && nums[i].second == nums[i + 1].second) { cur++; i++; }
		res *= factorials[cur]; res %= mod;
	}
	return res;
}

ll sortedBoth() {
	ll res = 1ll;
	for (int i = 0; i < n - 1; i++) {
		if (nums[i].second > nums[i + 1].second) { return 0; }
		int count = 1;
		while (i < n - 1 && nums[i].first == nums[i + 1].first && nums[i].second == nums[i + 1].second) { count++; i++; }
		// 2 2 1 1  i would stop at 1, then increase at 2 and skip checking nums[1]>nums[2]
		if (i < n - 1 && nums[i].second > nums[i + 1].second) { return 0; }
		res *= factorials[count]; res %= mod;
	}
	return res;
}

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		ll a, b; cin >> a >> b;
		nums.push_back({ a, b });
	}

	fillFact();
	ll res = factorials[n];
	sort(nums.begin(), nums.end(), comp2);
	res -= sorted2(); while (res < 0) { res += mod; } res %= mod;
	sort(nums.begin(), nums.end(), comp1);
	res -= sorted1(); while (res < 0) { res += mod; } res %= mod;
	res += sortedBoth(); res %= mod;

	cout << res << endl;
}
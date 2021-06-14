#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <assert.h>
using namespace std;
typedef long long ll;

vector<ll> nums;

struct FT {
	int n;
	vector<ll> vals;
	FT(const int n) :
		n(n), vals(vector<ll>(n + 1, 0)) {
	}

	void update(int i, const ll x) {
		for (++i; i <= n; i += i & -i) {
			vals[i] += x;
		}
	}
	ll query(int i) const { // sum from 0 ... i
		assert(i >= -1 && i < n);
		ll sum = 0;
		for (++i; i; i -= i & -i)
			sum += vals[i];
		return sum;
	}
	ll query(int i, int j) const {
		return query(j) - query(i - 1);
	}
};


int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n;
	cin >> n;
	map<int, int> compress;
	nums.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> nums[i];
		compress[nums[i]] = i;
	}

	ll cur = 0;
	map<int, int>::iterator itr = compress.begin();
	while (itr != compress.end()) {
		nums[itr->second] = cur;
		cur++;
		itr++;
	}

	vector<ll> greater(n, 0);
	vector<ll> smaller(n, 0);

	FT tree(n);
	for (int i = 0; i < n; i++) {
		tree.update(nums[i], 1);
		greater[i] = i-tree.query(nums[i]-1);
	}

	tree = FT(n);
	for (int i = n - 1; i > -1; i--) {
		tree.update(nums[i], 1);
		smaller[i] = tree.query(nums[i]-1);
	}

	ll res = 0;
	for (int i = 0; i < n; i++) {
		res += greater[i] * smaller[i];
	}

	cout << res << endl;
	return 0;
}
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>

using namespace std;
typedef long long ll;

struct FT {
	int n;
	vector<ll> vals;
	FT(const int n) :
		n(n), vals(vector<ll>(n + 1, 0)) {
	}

	void update(int i, const ll x = 1) {
		for (++i; i <= n; i += i & -i)
			vals[i] += x;
	}
	ll query(int i) const { // sum from 0 ... i
		ll sum = 0;
		for (++i; i; i -= i & -i)
			sum += vals[i];
		return sum;
	}
	ll query(int i, int j) const {		// sum from i ... j
		return query(j) - query(i - 1);
	}
};


int main() {
	int n; cin >> n;
	vector<ll> nums(n);
	for (auto &x : nums) { cin >> x; }

	vector<ll> goingUp(n), goingDown(n);
	FT tree(n), treeCount(n);

	map<int, int> m;
	for (int i = 0; i < n; i++) {
		m[nums[i]] = i;
	}
	int counter = 0;
	for (auto &x : m) { x.second = counter++; }
	vector<ll> numsComp(n);
	for (int i = 0; i < n; i++) {
		numsComp[i] = m[nums[i]];
	}

	goingUp[0] = nums[0];
	tree.update(numsComp[0], nums[0]);
	treeCount.update(numsComp[0], 1);
	for (int i = 1; i < n; i++) {
		goingUp[i] = tree.query(numsComp[i]) + nums[i] + treeCount.query(numsComp[i]+1, n-1)*nums[i];
		tree.update(numsComp[i], nums[i]);
		treeCount.update(numsComp[i], 1);
	}

	FT tree2(n), treeCount2(n);
	goingDown[n - 1] = nums[n - 1];
	tree2.update(numsComp[n-1], nums[n-1]);
	treeCount2.update(numsComp[n-1], 1);
	for (int i = n-2; i >=0; i--) {
		goingDown[i] = tree2.query(numsComp[i]) + nums[i] + treeCount2.query(numsComp[i] + 1, n - 1)*nums[i];
		tree2.update(numsComp[i], nums[i]);
		treeCount2.update(numsComp[i], 1);
	}

	ll center = 0, maxAns = goingDown[0];
	for (int i = 0; i < n; i++) {
		ll cur = goingUp[i] + goingDown[i] - nums[i];

		if (cur > maxAns) { maxAns = cur; center = i; }
	}

	vector<ll> answ(n); answ[center] = nums[center];

	ll prevMax = nums[center];
	for (int j = center - 1; j >= 0; j--) {
		answ[j] = min(nums[j], prevMax);
		prevMax = answ[j];
	}

	prevMax = nums[center];
	for (int j = center + 1; j < n; j++) {
		answ[j] = min(nums[j], prevMax);
		prevMax = answ[j];
	}

	for (auto &x : answ) { cout << x << " "; }
}
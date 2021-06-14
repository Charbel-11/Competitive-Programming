#include <vector>
#include <string>
#include <assert.h>
#include <iostream>
using namespace std;
typedef long long ll;

struct FT {
	int n;
	vector<ll> vals;

	FT() {}
	FT(const int n) : n(n), vals(vector<ll>(n + 1, 0)) { }

	void update(int i, const ll x) {
		for (++i; i <= n; i += i & -i)
			vals[i] += x;
	}
	ll query(int i) const { // sum from 0 ... i
		assert(i >= -1 && i < n);
		ll sum = 0;
		for (++i; i; i -= i & -i)
			sum += vals[i];
		return sum;
	}
};

int main() {
	int n, k; cin >> n >> k; k++;
	vector<int> nums; nums.resize(n); 
	for (auto &x : nums) { cin >> x; }

	vector<FT> trees(k+1);
	for (int i = 0; i <= k; i++) { trees[i] = FT(n+1); } 
	
	for (int i = 0; i < n; i++) {
		trees[1].update(nums[i], 1);
		for (int j = 2; j <= k; j++) {
			ll cur = trees[j - 1].query(nums[i] - 1);
			if (cur) { trees[j].update(nums[i], cur); }
		}
	}

	cout << trees[k].query(n) << endl;
}
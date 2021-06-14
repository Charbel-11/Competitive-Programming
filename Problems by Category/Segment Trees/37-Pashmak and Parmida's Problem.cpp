#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;
typedef long long ll;

struct FT {
	int n;
	vector<ll> vals;
	FT(const int n) :
		n(n), vals(vector<ll>(n + 1, 0)) {
	}

	void update(int i) {
		for (++i; i <= n; i += i & -i)
			vals[i] ++;
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
	int n;
	cin >> n;

	multimap<int, int> compress;
	vector<int> nums(n);
	for (int i = 0; i < n; i++) {
		cin >> nums[i];
		compress.insert({ nums[i], i });
	}

	ll cur = 0;
	multimap<int, int>::iterator itr = compress.begin();
	while (itr != compress.end()) {
		int t = itr->first;
		while (itr != compress.end() && itr->first == t) { nums[itr->second] = cur; itr++; }
		cur++;
	}

	vector<int> fi(n, 0);
	vector<int> fj(n, 0);
	vector<int> freq(n, 0);

	for (int i = 0; i < n; i++) {
		freq[nums[i]]++;
		fi[i] = freq[nums[i]];
	}

	freq = vector<int>(n, 0);
	for (int j = n - 1;  j >= 0; j--) {
		freq[nums[j]]++;
		fj[j] = freq[nums[j]];
	}

	FT tree(n);
	long long res = 0;
	for (int j = 1; j < n; j++) {
		tree.update(fi[j-1]);
		res += tree.query(fj[j] + 1, n - 1);
	}

	cout << res << endl;
}
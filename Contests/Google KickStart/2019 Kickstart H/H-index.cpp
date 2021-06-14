#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

struct FT {
	int n;
	vector<ll> vals;
	FT(const int n) :
		n(n), vals(vector<ll>(n + 1, 0)) {
	}

	void update(int i, const ll x=1ll) {
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
	int t; cin >> t;

	for(int z = 0; z < t; z++) {
		int N; cin >> N;
		cout << "Case #" << z + 1 << ": ";
		FT tree(1e5 + 1);
		
		int idx = 0;
		for (int i = 0; i < N; i++) {
			int temp; cin >> temp;
			tree.update(temp);
			if (tree.query(idx + 1, 1e5) > idx) {
				idx++;
			}
			cout << idx << " ";
		}
		cout << endl;
	}
}
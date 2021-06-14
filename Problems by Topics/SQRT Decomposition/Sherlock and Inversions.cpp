//https://www.codechef.com/problems/IITI15

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

int block = 142;			//Set it to sqrt(n)
int freq[(int)2e4 + 2];		//Set to the range of numbers
vector<int> nums; int n;
ll curAns;

struct FT {
	int n;
	vector<ll> vals;
	FT() {}
	FT(const int n) :
		n(n), vals(vector<ll>(n + 1, 0)) {
	}

	//Adds x
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
		if (i > j) { return 0; }
		return query(j) - query(i - 1);
	}
};

FT tree;

struct query {
	int L, R, idx;
	query(int l, int r, int i) : L(l), R(r), idx(i) {}

	bool operator<(const query& q2) {
		int b1 = L / block, b2 = q2.L / block;
		if (b1 != b2) { return b1 < b2; }
		return R < q2.R;
	}
};

//Modify accordingly
void addR(int i) {
	tree.update(nums[i]);
	curAns += tree.query(nums[i] + 1, n);
}

void addL(int i) {
	tree.update(nums[i]);
	curAns += tree.query(0, nums[i] - 1);
}

void removeR(int i) {
	tree.update(nums[i], -1);
	curAns -= tree.query(nums[i] + 1, n);
}

void removeL(int i) {
	tree.update(nums[i], -1);
	curAns -= tree.query(0, nums[i] - 1);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	map<int, int> m;
	cin >> n; tree = FT(n+1);
	nums.resize(n);
	for (auto &x : nums) { cin >> x; m.insert({ x,-1 }); }
	int idx = 0;
	for (auto &p : m) { p.second = idx++; }
	for (auto &x : nums) { x = m[x]; }

	int t; cin >> t;
	vector<query> queries;
	for (int i = 0; i < t; i++) {
		int l, r; cin >> l >> r; l--; r--;
		queries.push_back(query(l, r, i));
	}
	sort(queries.begin(), queries.end());

	vector<ll> ans(t);
	int L = 0, R = -1;
	for (auto &q : queries) {
		while (R < q.R) { addR(++R); }
		while (L > q.L) { addL(--L); }
		while (L < q.L) { removeL(L++); }
		while (R > q.R) { removeR(R--); }
		ans[q.idx] = curAns;
	}

	for (auto &x : ans) { cout << x << '\n'; }
}
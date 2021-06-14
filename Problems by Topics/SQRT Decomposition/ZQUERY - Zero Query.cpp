//https://www.spoj.com/problems/ZQUERY/
//TLE...

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

int block = 225;			//Set it to sqrt(n)
int shift = 50000;
set<int> occ[(int)1e6 + 2];		
vector<int> nums;
multiset<int> curAnswers;
int curAns;

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
void add(int i) {
	int idx = nums[i] + shift;
	occ[idx].insert(i);

	int newAns = *(--occ[idx].end()) - *(occ[idx].begin());
	curAnswers.insert(newAns);
	curAns = max(curAns, newAns);
}

void remove(int i) {
	int idx = nums[i] + shift;
	int newAns = *(--occ[idx].end()) - *(occ[idx].begin());
	occ[idx].erase(i);
	curAnswers.erase(curAnswers.find(newAns));
	if (!occ[idx].empty()) { curAnswers.insert(*(--occ[idx].end()) - *(occ[idx].begin())); }

	if (curAnswers.empty()) { curAns = 0; }
	else { curAns = *(--curAnswers.end()); }
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, t; cin >> n >> t;
	nums.resize(n);
	for (auto &x : nums) { cin >> x; }
	for (int i = 1; i < n; i++) { nums[i] += nums[i - 1]; }

	vector<query> queries;
	for (int i = 0; i < t; i++) {
		int l, r; cin >> l >> r; l--; r--;
		queries.push_back(query(l, r, i));
	}
	sort(queries.begin(), queries.end());

	vector<int> ans(t);
	int L = 0, R = -1;
	for (auto &q : queries) {
		while (R < q.R) { add(++R); }
		while (L > q.L) { add(--L); }
		while (L < q.L) { remove(L++); }
		while (R > q.R) { remove(R--); }

		int firstSum = (L ? nums[L - 1] + shift : shift);
		if (!occ[firstSum].empty()) curAns = max(curAns, *(--occ[firstSum].end()) - (L - 1));
		ans[q.idx] = curAns;
	}

	for (auto &x : ans) { cout << x << '\n'; }
}
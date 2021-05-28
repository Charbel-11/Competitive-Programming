//https://codeforces.com/contest/617/problem/E

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

const int block = 320;			//Set it to sqrt(n)
int freq[(int)2e6 + 2];		//Set to the range of numbers
vector<int> nums, pref;
int k; ll curAns;
int L, R;

struct query {
	int L, R, idx;
	query(int l, int r, int i) : L(l), R(r), idx(i) {}

	bool operator<(const query& q2) {
		int b1 = L / block, b2 = q2.L / block;
		if (b1 != b2) { return b1 < b2; }
		return (b1 & 1) ? (R > q2.R) : (R < q2.R);
	}
};

//i is only an index in the array!
void addL(int i) {
	int target = (i ? pref[i - 1] : 0) ^ k;
	curAns += freq[target];
	freq[(i ? pref[i - 1] : 0)]++;
}
void addR(int i) {
	int target = k ^ pref[i];
	curAns += freq[target];
	freq[pref[i]]++;
}

void removeL(int i) {
	freq[(i ? pref[i - 1] : 0)]--;
	int target = (i ? pref[i - 1] : 0) ^ k;
	curAns -= freq[target];
}
void removeR(int i) {
	freq[pref[i]]--;
	int target = k ^ pref[i];
	curAns -= freq[target];
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, t; cin >> n >> t >> k;
	nums.resize(n); pref.resize(n);
	for (auto &x : nums) { cin >> x; }
	pref[0] = nums[0];
	for (int i = 1; i < n; i++) { pref[i] = pref[i - 1] ^ nums[i]; }

	vector<query> queries;
	for (int i = 0; i < t; i++) {
		int l, r; cin >> l >> r; l--; r--;
		queries.push_back(query(l, r, i));
	}
	sort(queries.begin(), queries.end());

	freq[0]++;	//[L-1,R]
	vector<ll> ans(t);	
	L = 0; R = -1;
	for (auto &q : queries) {
		while (R < q.R) { addR(++R); }
		while (L > q.L) { addL(--L); }
		while (L < q.L) { removeL(L++); }
		while (R > q.R) { removeR(R--); }
		ans[q.idx] = curAns;
	}

	for (auto &x : ans) { cout << x << '\n'; }
}
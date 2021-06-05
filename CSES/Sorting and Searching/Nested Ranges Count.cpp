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

vector<int> A;

struct waveletTree {
	int lVal, rVal;
	waveletTree* lC, * rC;
	vector<int> left; 		//left[i] = number of elements from the first i elements that go to left child
							//Used to map the indices of range queries (we can deduce from it how much goes to the right child)

	//Numbers are in the range [lVal, rVal]
	//Array indices are in [lo, hi]
	waveletTree(int lo, int hi, int x, int y) {
		lVal = x; rVal = y;
		if (lVal == rVal || hi < lo) { return; }

		int mid = (lVal + rVal) / 2;
		auto f = [mid](int x) {	return x <= mid; };

		int curL = 0;
		for (auto i = lo; i <= hi; i++) {
			curL += f(A[i]); left.push_back(curL);
		}

		int pivot = stable_partition(A.begin() + lo, A.begin() + hi + 1, f) - A.begin();
		lC = new waveletTree(lo, pivot - 1, lVal, mid);
		rC = new waveletTree(pivot, hi, mid + 1, rVal);
	}

	//#numbers <= k in [l, r]  (k in compressed form)
	int LTE(int l, int r, int k) {
		if (l > r || k < lVal) { return 0; }
		if (rVal <= k) { return r - l + 1; }

		int befL = (l ? left[l - 1] : 0);
		return lC->LTE(befL, left[r] - 1, k) + rC->LTE(l - befL, r - left[r], k);
	}
};

struct range {
	int l, r, id;
	range(int _l, int _r, int _id) :l(_l), r(_r), id(_id) {}

	bool operator<(range& rhs) {
		if (l == rhs.l) { return r > rhs.r; }
		return l < rhs.l;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n; A.resize(n);
	vector<range> ranges;
	for (int i = 0; i < n; i++) {
		int l, r; cin >> l >> r;
		ranges.push_back(range(l, r, i));
	}
	sort(ranges.begin(), ranges.end());
	for (int i = 0; i < n; i++) { A[i] = ranges[i].r; }
	
	waveletTree wT(0, n - 1, 1, 1e9);
	vector<int> ans1(n, 0), ans2(n, 0);
	for (int i = 0; i < n; i++) {
		ans1[ranges[i].id] = wT.LTE(i + 1, n - 1, ranges[i].r);
		ans2[ranges[i].id] = i - wT.LTE(0, i - 1, ranges[i].r - 1);
	}

	for (auto& x : ans1) { cout << x << ' '; } cout << '\n';
	for (auto& x : ans2) { cout << x << ' '; }cout << '\n';
}
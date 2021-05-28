//https://www.spoj.com/problems/ILKQUERY/

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

const int MIN = 0, MAX = 1e5+2;		//Min and max possible values in the array
vector<int> A;

//Wavelet Tree supports:
//Queries:  Kth element in a range // Number of elements = k in a range // Number of elements <= k in a range
//Updates:  Swap two consecutive elements // Toggle elements (on elements are counted in queries; off elements aren't)
struct waveletTree {
	int lVal, rVal;
	waveletTree *lC, *rC;
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

	//kth smallest element in [l, r] (1<=k<=n)
	int kth(int l, int r, int k) {
		if (l > r) { return MAX + 2; }
		if (lVal == rVal) { return lVal; }

		int befL = (l ? left[l - 1] : 0);
		int inLeft = left[r] - befL;		//#numbers <= mid

		if (k <= inLeft) { return lC->kth(befL, left[r] - 1, k); }
		return rC->kth(l - befL, r - left[r], k - inLeft);
	}

	//#numbers <= k in [l, r]
	int LTE(int l, int r, int k) {
		if (l > r || k < lVal) { return 0; }
		if (rVal <= k) { return r - l + 1; }

		int befL = (l ? left[l - 1] : 0);
		return lC->LTE(befL, left[r] - 1, k) + rC->LTE(l - befL, r - left[r], k);
	}

	//#numbers = k in [l, r]
	int count(int l, int r, int k) {
		if (l > r || k < lVal || k > rVal) { return 0; }
		if (lVal == rVal) { return r - l + 1; }

		int mid = (lVal + rVal) / 2, befL = (l ? left[l - 1] : 0);
		if (k <= mid) { return lC->count(befL, left[r] - 1, k); }
		return rC->count(l - befL, r - left[r], k);
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	vector<int> comp;
	int n, q; cin >> n >> q;
	vector<vector<int>> occ(n);
	A.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> A[i]; comp.push_back(A[i]);
	}
	sort(comp.begin(), comp.end());
	comp.erase(unique(comp.begin(), comp.end()), comp.end());
	for (int i = 0; i < n; i++) {
		A[i] = lower_bound(comp.begin(), comp.end(), A[i]) - comp.begin();
		occ[A[i]].push_back(i);
	}

	waveletTree T(0, n - 1, MIN, MAX);

	while (q--) {
		int k, i, l; cin >> k >> i >> l;
		int d = T.kth(0, i, k);
		if (occ[d].size() < l) { cout << -1 << '\n'; }
		else { cout << occ[d][l - 1] << '\n'; }
	}
}
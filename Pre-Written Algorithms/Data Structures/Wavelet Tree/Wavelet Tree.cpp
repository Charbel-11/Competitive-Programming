//Queries are done in O(log(MAX))

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MIN = 0, MAX = 1e6 + 2;		//Min and max possible values in the array; [-1e9,1e9] might be too much, better compress
vector<int> A, B;						//We will partition A and keep B as a copy

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

	//#numbers <= k in [l, r]  (k in compressed form)
	int LTE(int l, int r, int k) {
		if (l > r || k < lVal) { return 0; }
		if (rVal <= k) { return r - l + 1; }

		int befL = (l ? left[l - 1] : 0);
		return lC->LTE(befL, left[r] - 1, k) + rC->LTE(l - befL, r - left[r], k);
	}

	//#numbers = k in [l, r]  (k in compressed form)
	int count(int l, int r, int k) {
		if (l > r || k < lVal || k > rVal) { return 0; }
		if (lVal == rVal) { return r - l + 1; }

		int mid = (lVal + rVal) / 2, befL = (l ? left[l - 1] : 0);
		if (k <= mid) { return lC->count(befL, left[r] - 1, k); }
		return rC->count(l - befL, r - left[r], k);
	}

	void swapAdjacent(int i) {
		int f = B[i], s = B[i + 1];
		if (f != s) { return swapAdjRec(i, f, s); }
	}

	void swapAdjRec(int i, const int &f, const int &s) {
		int mid = (lVal + rVal) >> 1;
		if (f <= mid && s <= mid) { return lC->swapAdjRec(left[i] - 1, f, s); }
		if (f > mid && s > mid) { return rC->swapAdjRec(i - left[i], f, s); }
		(f <= mid ? left[i]-- : left[i]++);
	}
};
//https://www.spoj.com/problems/ILKQUERYIII/

#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <cassert>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

const int MIN = 0, MAX = 2e6 + 2;		//Min and max possible values in the array; [-1e9,1e9] might me too much, better compress
vector<int> A, cA;						//We will partition cA and keep A as is

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
		for (int i = lo; i <= hi; i++) {
			curL += f(cA[i]); left.push_back(curL);
		}

		int pivot = stable_partition(cA.begin() + lo, cA.begin() + hi + 1, f) - cA.begin();
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

	//Swaps numbers at index i and i+1
	//Need to modify indices outside the structure too
	void swapCons(int i, int f, int s) {
		if (i >= A.size() - 1) { return; }

		int mid = (lVal + rVal) / 2;
		if (f <= mid && s > mid) { left[i]--; }
		else if (f > mid && s <= mid) { left[i]++; }
		else if (f <= mid && s <= mid) { lC->swapCons(left[i] - 1, f, s); }
		else if (f > mid && s > mid) { rC->swapCons(i - left[i], f, s); }
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
	cA = A;	

	waveletTree T(0, n - 1, MIN, MAX);

	while (q--) {
		int type; cin >> type;
		if (type == 0) {
			int i, l, k; cin >> i >> l >> k;
			int d = T.kth(0, i, k);
			if (occ[d].size() < l) { cout << -1 << '\n'; }
			else { cout << occ[d][l - 1] << '\n'; }
		}
		else {
			int i; cin >> i;
			if (i >= 0 && i < n - 1 && A[i] != A[i+1]) { 
				T.swapCons(i, A[i], A[i+1]);

				int idx = lower_bound(occ[A[i]].begin(), occ[A[i]].end(), i) - occ[A[i]].begin();
				occ[A[i]][idx]++;

				idx = lower_bound(occ[A[i+1]].begin(), occ[A[i+1]].end(), i+1) - occ[A[i+1]].begin();
				occ[A[i+1]][idx]--;
				swap(A[i], A[i + 1]); 
			}
		}
	}
}
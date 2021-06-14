#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <map>
using namespace std;
typedef long long ll;

struct FT {
	int n; vector<int> vals; FT() {};
	FT(int n) : n(n) { vals.resize(n + 1, 0); }

	void update(int i, int x) {
		for (++i; i <= n; i += i & -i) { vals[i] += x; }
	}

	int query(int i) const { 
		int sum = 0;
		for (++i; i; i -= i & -i) { sum += vals[i]; }
		return sum;
	}
	int query(int l, int r) { return query(r) - query(l - 1); }
};

const int MIN = 0, MAX = 100002;
vector<int> A, B; 

struct WaveletTree {
	int lVal, rVal; int n;
	WaveletTree *lC, *rC;
	vector<int> left; 		
	FT aLeft, aLeaf; 

	WaveletTree(int _n) : WaveletTree(0, _n - 1, MIN, MAX) { }

	WaveletTree(int lo, int hi, int x, int y) {
		lVal = x; rVal = y; n = hi - lo + 1;
		if (lVal == rVal || hi < lo) { 
			aLeaf = FT(n);
			for (int i = 0; i < n; i++) { aLeaf.update(i, 1); }
			return;
		}
		aLeft = FT(n); int mid = (lVal + rVal) >> 1, back = 0;
		for (int i = lo; i <= hi; i++) {
			left.push_back(back += (A[i] <= mid));
			if (A[i] <= mid) aLeft.update(i, 1);
		}

		auto comp = [&](const int &x) {return x <= mid; };
		int pivot = stable_partition(A.begin() + lo, A.begin() + hi + 1, comp) - A.begin();
		lC = new WaveletTree(lo, pivot - 1, lVal, mid);
		rC = new WaveletTree(pivot, hi, mid + 1, rVal);
	}

	inline int activeLeft(int i) { return (i >= 0 && i < n) ? aLeft.query(i) : 0; }
	inline int activeLeaf(int i) { return (i >= 0 && i < n) ? aLeaf.query(i) : 0; }
	inline int mapLeft(int i) { return (i >= 0 && i < n) ? left[i] - 1 : 0; }
	inline int mapRight(int i) { return (i >= 0 && i < n) ? i - left[i] : 0; }

	int countK(int l, int r, int k) {
		if (l > r || k < lVal || k > rVal) { return 0; }
		if (lVal == rVal) { return activeLeaf(r) - activeLeaf(l - 1); }

		int mid = (lVal + rVal) >> 1, befL = (l ? left[l - 1] : 0);
		if (k <= mid) { return lC->countK(befL, left[r] - 1, k); }
		return rC->countK(l - befL, r - left[r], k);
	}

	void toggle(int i) { if (i >= 0 && i < n) return toggle(i, B[i]); }
	void toggle(int i, const int &x) {
		if (lVal == rVal) { aLeaf.update(i, aLeaf.query(i, i) ? -1 : 1); return; }
		int mid = (lVal + rVal) >> 1; 
		if (x > mid) { return rC->toggle(mapRight(i), x); }
		aLeft.update(i, aLeft.query(i, i) ? -1 : 1);
		return lC->toggle(mapLeft(i), x);
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, q; cin >> n >> q; A.resize(n);
	vector<vector<int>> occ(n); map<int, int> comp;
	for (auto &x : A) { cin >> x; comp[x]++; }
	int id = 0; for (auto &x : comp) { x.second = id++; }
	for (int i = 0; i < n; i++) { A[i] = comp[A[i]]; occ[A[i]].push_back(i); }
	B = A; WaveletTree T(n);

	while (q--) {
		int t; cin >> t;
		if (t) { int i; cin >> i; T.toggle(i); continue; }
		int i, l, k; cin >> i >> l >> k;
		if (comp.count(k) == 0) { cout << 0 << '\n'; }
		else { cout << T.countK(i, l, comp[k]) << '\n'; }
	}

	cin.ignore(2); return 0;
}
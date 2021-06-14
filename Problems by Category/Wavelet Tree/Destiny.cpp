//https://codeforces.com/contest/840/problem/D
//Works since k is small; at each level of the tree we have at most k active calls and k<=5

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

const int MIN = 0, MAX = 4e5;		//Min and max possible values in the array; [-1e9,1e9] might me too much, better compress
vector<int> A;

//Wavelet Tree supports:
//Queries:  Kth element in a range // Number of elements = k in a range // Number of elements <= k in a range
//Updates:  Swap two consecutive elements // Toggle elements (on elements are counted in queries; off elements aren't)
//Updates not implemented yet
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

	//Finds the smallest number that occurs at least freq times
	int find(int l, int r, int freq) {
		if (r - l + 1 < freq) { return -1; }
		if (lVal == rVal) { return lVal; }

		int befL = (l ? left[l - 1] : 0);

		int c1 = lC->find(befL, left[r] - 1, freq);
		if (c1 != -1) { return c1; }
		return rC->find(l - befL, r - left[r], freq);
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, q; cin >> n >> q;
	A.resize(n);
	for (auto &x : A) { cin >> x; }

	waveletTree T(0, n - 1, MIN, MAX);

	while (q--) {
		int l, r, k; cin >> l >> r >> k; l--; r--;
		cout << T.find(l, r, (r - l + 1) / k + 1) << '\n';
	}
}
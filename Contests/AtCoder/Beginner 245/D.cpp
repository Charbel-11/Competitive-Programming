#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
	vector<int> A(n + 1), B(m + 1, 0), C(n + m + 1);
	for (auto& x : A) { cin >> x; }
	for (auto& x : C) { cin >> x; }

	for (int i = n + m; i >= n; i--) {
		int cur = C[i];
		int Aidx = n;
		int Bidx = i - Aidx;
		while (Bidx <= m && Aidx >= 0) {
			cur -= B[Bidx] * A[Aidx];
			Aidx--; Bidx++;
		}
		B[i - n] = cur / A[n];
	}

	for (auto& x : B) { cout << x << ' '; }
	cout << '\n';
}

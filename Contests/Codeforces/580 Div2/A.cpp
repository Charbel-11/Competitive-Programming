#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	int n; cin >> n;
	vector<int> A(n); for (int i = 0; i < n; i++) { cin >> A[i]; }
	int m; cin >> m;
	vector<int> B(m); for (int i = 0; i < m; i++) { cin >> B[i]; }

	sort(A.begin(), A.end());
	sort(B.begin(), B.end());

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int cur = A[i] + B[j];
			if (!binary_search(A.begin(), A.end(), cur) && !binary_search(B.begin(), B.end(), cur)) {
				cout << A[i] << " " << B[j] << endl; return 0;
			}
		}
	}
}
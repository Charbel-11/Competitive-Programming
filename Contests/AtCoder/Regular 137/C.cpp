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

	int n; cin >> n;
	vector<int> A(n); for (auto& x : A) { cin >> x; }

	if (A[n - 1] > A[n - 2] + 1) { cout << "Alice" << '\n'; }
	else if (((A[n - 1] + 1 - n) % 2) == 1) { cout << "Alice" << '\n'; }
	else { cout << "Bob" << '\n'; }
}
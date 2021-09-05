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

	vector<int> partialXor(3e5 + 5, 0);
	for (int i = 1; i < partialXor.size(); i++) {
		partialXor[i] = partialXor[i - 1] ^ i;
	}

	int t; cin >> t;
	while (t--) {
		int a, b; cin >> a >> b;
		int ans = a;

		int curXor = partialXor[a - 1];
		int neededXor = curXor ^ b;
		if (neededXor == a) { ans += 2; }
		else if (neededXor != 0) { ans++; }

		cout << ans << '\n';
	}
}
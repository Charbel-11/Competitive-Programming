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

	int n, k; cin >> n >> k;
	vector<int> moves(k);
	for (auto& x : moves) { cin >> x; }

	string ans(n + 1, 'L'); 
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < k; j++) {
			if (i - moves[j] >= 0 && ans[i - moves[j]] == 'L') {
				ans[i] = 'W'; break;
			}
		}
	}

	cout << ans.substr(1, n) << '\n';
}
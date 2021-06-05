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

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, x; cin >> n >> x;
	vector<int> weight(n);
	for (auto &x : weight) { cin >> x; }
	sort(weight.begin(), weight.end());

	int i = 0, j = n - 1, res = 0;
	while (i < j) {
		res++;
		if (weight[i] + weight[j] <= x) { i++; j--; }
		else { j--; }
	}
	res += (i == j);

	cout << res << '\n';
}
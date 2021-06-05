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

	int n; cin >> n;
	set<int> nums;
	for (int i = 0; i < n; i++) {
		int cur; cin >> cur;
		nums.insert(cur);
	}

	cout << (int)nums.size() << '\n';
}
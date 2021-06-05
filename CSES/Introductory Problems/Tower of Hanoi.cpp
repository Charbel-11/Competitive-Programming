#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

vector<pair<int, int>> ans;

void Hanoi(int n, int start, int inter, int end) {
	if (n == 0) { return; }
	Hanoi(n - 1, start, end, inter);
	ans.push_back({ start, end });
	Hanoi(n - 1, inter, start, end);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	Hanoi(n, 1, 2, 3);
	cout << ans.size() << '\n';
	for (auto& p : ans) { cout << p.first << " " << p.second << '\n'; }
}
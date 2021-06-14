#include <iostream>
#include <string>
#include <map>
#include <stack>
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

	int n, m; cin >> n >> m;
	vector<int> want(n, 0), av(n);
	vector<vector<int>> whoWant(n);
	vector<bool> done(m, 0), inStack(n, 0);
	vector<pair<int, int>> friends(m);

	for (auto &x : av) { cin >> x; }

	int idx = 0;
	for (auto &p : friends) {
		cin >> p.first >> p.second;
		p.first--; p.second--;
		want[p.first]++; want[p.second]++;
		whoWant[p.first].push_back(idx);
		whoWant[p.second].push_back(idx);
		idx++;
	}

	stack<int> doable;
	for (int i = 0; i < n; i++) {
		if (av[i] >= want[i] && av[i]) { doable.push(i); inStack[i] = 1; }
	}

	vector<int> ans;

	while (!doable.empty()) {
		int cur = doable.top(); doable.pop();
		for (auto &x : whoWant[cur]) {
			if (done[x]) { continue; }
			done[x] = 1; ans.push_back(x);
			int f = friends[x].first, s = friends[x].second;
			want[f]--; want[s]--; av[cur]--;
			if (av[f] >= want[f] && !inStack[f]) { doable.push(f); inStack[f] = 1; }
			if (av[s] >= want[s] && !inStack[s]) { doable.push(s); inStack[s] = 1; }
		}
	}

	if (ans.size() != m) { cout << "DEAD\n"; return 0; }
	cout << "ALIVE\n";
	reverse(ans.begin(), ans.end());
	for (auto &x : ans) { cout << x + 1 << ' '; }
	cout << '\n';
}
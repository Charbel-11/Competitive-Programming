//https://codeforces.com/contest/1183/problem/E
// 1 <= n, k <= 100 for bigger numbers, use DP
#include <string>
#include <iostream>
#include <queue>
#include <set>

using namespace std;

int main() {
	int n, k; cin >> n >> k;

	string s; cin >> s;

	set<string> visited;
	queue<string> Q;
	int curV = 1;
	int res = 0;

	Q.push(s);
	visited.insert(s);
	while (!Q.empty() && curV < k) {
		string cur = Q.front();
		Q.pop();

		for (int i = 0; i < cur.size(); i++) {
			if (curV == k) { break; }

			string temp = cur;
			temp.erase(i, 1);

			if (visited.count(temp) == 0) {
				visited.insert(temp);
				Q.push(temp);
				res += n - temp.size();
				curV++;
			}
		}
	}

	if (curV < k) {
		cout << -1 << endl;
	}
	else {
		cout << res << endl;
	}
}
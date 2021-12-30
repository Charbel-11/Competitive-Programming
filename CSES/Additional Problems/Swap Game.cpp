#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	string start = "", target = "";
	for (int i = 1; i <= 9; i++) {
		int cur; cin >> cur;
		start.push_back('0' + cur);
		target.push_back('0' + i);
	}

	unordered_map<string, int> dist; queue<string> Q;
	dist.reserve(362880); dist[start] = 0; Q.push(start);
	while (!Q.empty()) {
		string curState = Q.front(); Q.pop();
		int curDist = dist[curState];

		for (int curIdx = 0; curIdx < 9; curIdx++) {
			int i = curIdx / 3, j = curIdx % 3;
			if (j < 2) {
				swap(curState[curIdx + 1], curState[curIdx]);
				if (!dist.count(curState)) {
					dist[curState] = curDist + 1;
					if (curState == target) { break; }
					Q.push(curState);
				}
				swap(curState[curIdx + 1], curState[curIdx]);
			}
			if (i < 2) {
				swap(curState[curIdx + 3], curState[curIdx]);
				if (!dist.count(curState)) {
					dist[curState] = curDist + 1;
					if (curState == target) { break; }
					Q.push(curState);
				}
				swap(curState[curIdx + 3], curState[curIdx]);
			}
		}
	}

	cout << dist[target] << '\n';
}
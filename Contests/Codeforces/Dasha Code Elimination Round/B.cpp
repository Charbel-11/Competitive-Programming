#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>

using namespace std;

int main() {
	int n; cin >> n;
	string s; cin >> s;

	vector<int> next(n);
	vector<int> curNext(n);
	for (int i = 0; i < n; i++) {
		int a, b; cin >> a >> b;
		next[i] = a;
		curNext[i] = b;
	}

	int curOn = 0;
	vector<bool> on(n, 0);
	for (int i = 0; i < n; i++) {
		if (s[i] == '1') { on[i] = 1; curOn++; }
	}
	int res = curOn;

	int curTime = 1;
	for (int i = 0; i < 10001; i++) {
		for (int j = 0; j < n; j++) {
			if (curNext[j] <= curTime){
				curNext[j] += next[j];
				if (on[j]) {
					curOn--; on[j] = 0;
				}
				else {
					curOn++; on[j] = 1;
				}
			}
		}
		res = max(res, curOn);

		curTime++;
	}

	cout << res << endl;
}
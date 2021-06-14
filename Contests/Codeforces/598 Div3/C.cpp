#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m, d; cin >> n >> m >> d;

	vector<int> c(m); int totalC = 0;
	for (auto &x : c) { cin >> x; totalC += x; }
	
	vector<int> res(n, 0);
	
	d--;
	int curC = 0, curD = d;
	for (int i = 0; i < n; i++) {
		if (((n-i)-totalC) <= curD) {
	//		cout << totalC << " " << n-i-1 << " " << d << endl;
			for (int j = i; j < n; j++) {
				if (curC == c.size()) { break; }
				res[j] = curC+1;
				c[curC]--; 
				if (c[curC] == 0) { curC++; }
			}

			break;
		}

		if (curD == 0) {
			curD = d;
			if (curC == c.size()) { cout << "NO" << endl; return 0; }
			for (int j = i; j < i + c[curC]; j++) {
				res[j] = curC + 1; totalC--;
			}
			i = i + c[curC] - 1;
			curC++;
		}
		else { curD--; }
	}

	cout << "YES" << endl;
	for (auto &x : res) { cout << x << " "; } cout << endl;
}
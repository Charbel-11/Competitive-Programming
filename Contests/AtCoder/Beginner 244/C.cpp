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
	int n; cin >> n;
	vector<bool> used(2 * n + 2, false);
	int idx = 1;

	while (idx < 2 * n + 2) {
		if (used[idx]) { idx++; continue; }
		cout << idx << endl;
		used[idx] = true;

		int response; cin >> response;
		if (response == 0) { break; }
		else { used[response] = true; }
	}
}
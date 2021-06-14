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

int getMin(int l, int r) {
	cout << "M " << l << " " << r << endl;
	int ans; cin >> ans;
	return ans;
}

void swap(int l, int r) {
	cout << "S " << l << " " << r << endl;
	int res; cin >> res;
}

int main() {	
	int t, n; cin >> t >> n;
	for (int qq = 1; qq <= t; qq++) {
		int l = 1;
		for (int i = 1; i <= n && l < n; i++) {
			int curM = getMin(l, n);
			if (curM == i) { l++; continue; }
			swap(i, curM); l++;
		}

		cout << "D" << endl;
		int res; cin >> res;
		if (res == -1) { break; }
	}
}

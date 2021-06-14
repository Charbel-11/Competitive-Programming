#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	int t; cin >> t;

	while (t--) {
		int n; cin >> n;
		if (n == 1) { cout << -1 << endl; continue; }
		
		string s(n - 1, '3');
		cout << '2' << s << endl;
	}
}
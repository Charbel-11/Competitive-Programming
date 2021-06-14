#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	int t; cin >> t;

	while (t--) {
		int a, b; cin >> a >> b;
		cout << (a%b == 0 ? "YES" : "NO") << endl;
	}
}
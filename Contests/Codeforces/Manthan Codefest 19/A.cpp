#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	int T; cin >> T;

	for (int z = 0; z < T; z++) {
		int a, b, n; cin >> a >> b >> n;

		vector<int> answ(3); answ[0] = a; answ[1] = b; answ[2] = a ^ b;
		cout << answ[n % 3] << endl;
	}
}
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	int t; cin >> t;

	while (t--) {
		long long n, k; cin >> n >> k;
		long long sum = k * k;
		if (n % 2 != k % 2 || sum > n) { cout << "NO" << endl; continue; }
		cout << "YES" << endl;
	}
}
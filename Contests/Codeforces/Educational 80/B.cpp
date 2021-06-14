#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

int main() {
	int t; cin >> t;

	while (t--) {
		ll A, B; cin >> A >> B;

		ll cur = 9, count1 = 0;
		while (cur <= B) {
			count1++;
			cur *= 10; cur += 9;
		}
		ll res = A * count1;

		cout << res << endl;
	}
}
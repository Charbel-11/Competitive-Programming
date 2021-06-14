#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	int X; cin >> X;

	int ans = 1000 * (X / 500);
	X %= 500;
	ans += 5 * (X / 5);

	cout << ans << endl;
}
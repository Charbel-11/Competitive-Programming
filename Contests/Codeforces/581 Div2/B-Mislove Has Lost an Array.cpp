#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	int n, l, r; cin >> n >> l >> r;

	int min = 0; int max = 0;
	min = n - l + 1; l--;
	int cur = 2;
	while(l!=0){
		min += cur;
		cur *= 2; l--;
	}

	max++; r--; n--; cur = 2;
	while (r != 0) {
		max += cur;
		cur *= 2; r--; n--;
	}
	cur /= 2;
	max += cur * n;

	cout << min << " " << max << endl;
}
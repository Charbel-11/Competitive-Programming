#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int k; cin >> k;
	if (k == 0) {
		cout << 1 << " " << 1 << endl << 10 << endl;
		return 0;
	}
	cout << 2 << " " << 4 << endl;
	int shifted = 1;
	while (shifted <= k) { shifted <<= 1; }
	int shiftedK = shifted | k;
	
	cout << shiftedK << " " << k << " " << k << " " << 0 << endl;
	cout << shifted << " " << shiftedK << " " << shiftedK << " " << k << endl;
}
 
// k|1<   k		k   0 
//  1<  k|1<  k|1<  k
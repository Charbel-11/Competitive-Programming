#include <iostream>
#include <string>
#include <cmath>

using namespace std;

//Find the kth move towards moving all n disks from start to end (as fast as possible)
void findMove(int n, long long k, int start = 1, int end = 3, int inter = 2) {
	long long nthPower = pow(2, n);

	if (k < 0 || k > nthPower - 1) { return; }

	if (k <= nthPower / 2 - 1) { findMove(n - 1, k, start, inter, end); }
	else if (k == nthPower / 2) { cout << "Disk " << n << " moved from " << start << " to " << end << endl; }
	else { findMove(n - 1, k - nthPower / 2, inter, end, start); }
}

//n disk need (2^n)-1 moves;
//If k<= 2^n-1 - 1, recur on n-1 with inter as end
//If k==2^n-1, return moving n to end
//If k>2^n-1, recur on n-1 with inter as start

int main() {
	findMove(1000, 1846500000000);
}
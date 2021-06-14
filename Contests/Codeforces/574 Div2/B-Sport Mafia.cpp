#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

long long n, k;

long long findSum(long long n) {
	return n * (n + 1) / 2;			//badda long long
}

int bSearch(long long a, long long b) {
	if (a == b) { return a; }		

	long long mid = (a + b) / 2;

	long long curS = findSum(n - mid);
	if (curS == k + mid) {
		return mid;
	}
	else if (curS > k + mid) {
		return bSearch(mid + 1, b);
	}
	return bSearch(a, mid - 1);
}

int main() {
	cin >> n >> k;

	cout << bSearch(0, n) << endl;
}
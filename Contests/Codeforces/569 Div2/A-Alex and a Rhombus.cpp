#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
	int n;
	cin >> n;

	long long res = 1;
	long long cur = 4;

	for (int i = 1; i < n; i++) {
		res += cur;
		cur +=4;
	}

	cout << res << endl;
}
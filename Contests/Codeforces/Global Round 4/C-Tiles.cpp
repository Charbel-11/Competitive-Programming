#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const long long mod = 998244353;

int main() {
	long long w,h;
	cin >> w >> h;
	
	vector<long long> answ(2002);
	answ[0] = 1;
	for (int i = 1; i < 2002; i++) {
		answ[i] = (answ[i - 1] * 2) % mod;
	}

	cout << answ[w+h] << endl;
}
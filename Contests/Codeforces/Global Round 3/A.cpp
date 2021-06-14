#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
	long long a,b,c;
	cin >> a >> b >> c;

	long long add = a > b ? b : a;
	a -= add;
	b -= add;
	c += add;

	long long res = c * 2;
	if (a != 0) { res++; }
	if (b != 0) { res++; }

	cout << res << endl;
}
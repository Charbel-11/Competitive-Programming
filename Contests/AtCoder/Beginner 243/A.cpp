#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int v, a, b, c; cin >> v >> a >> b >> c;
	v %= (a + b + c);

	if (a > v) { cout << "F" << '\n'; }
	else if (a + b > v) { cout << "M" << '\n'; }
	else if (a + b + c > v) { cout << "T" << '\n'; }
}
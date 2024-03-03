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

	int a, b, c, d; cin >> a >> b >> c >> d;
	int c1 = b + a * 60, c2 = d + 1 + c * 60;
	if (c1 < c2) { cout << "Takahashi" << '\n'; }
	else { cout << "Aoki" << '\n'; }
}

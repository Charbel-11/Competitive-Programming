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

	int k; cin >> k;
	ll ans = 0;
	for (int i = 1; i <= k; i++)
		for (int j = 1; j * i <= k; j++)
			for (int l = 1; l * j * i <= k; l++)
				ans++;

	cout << ans << '\n';
}
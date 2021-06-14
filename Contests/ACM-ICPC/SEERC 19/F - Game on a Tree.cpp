#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	for (int i = 0; i < n-1; i++) {
		int u, v; cin >> u >> v;
	}

	cout << (n % 2 ? "Alice" : "Bob") << endl;
}
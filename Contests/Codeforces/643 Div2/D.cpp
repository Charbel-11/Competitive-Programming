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

	int N, S; cin >> N >> S;
	if (S < N * 2) { cout << "NO" << endl; return 0; }
	cout << "YES" << endl;
	for (int i = 0; i < N - 1; i++) {
		cout << "2 "; S -= 2;
	}
	cout << S << endl;
	cout << 1 << endl;
}
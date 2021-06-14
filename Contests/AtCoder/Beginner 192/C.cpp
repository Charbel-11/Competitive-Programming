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

	int N, K; cin >> N >> K;
	int cur = N;
	while (K--) {
		string sD = to_string(cur);
		string sI = sD;
		sort(sD.rbegin(), sD.rend());
		sort(sI.begin(), sI.end());

		int gD = stoi(sD), gI = stoi(sI);
		cur = gD - gI;
	}
	cout << cur << '\n';
}
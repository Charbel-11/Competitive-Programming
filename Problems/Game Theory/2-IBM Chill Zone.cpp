#include <string>
#include <iostream>
#include <set>

using namespace std;

int DP[52];
int n, k;

int mex(int i) {
	if (DP[i] != -1) { return DP[i]; }
	if (i <= k) { return i == k; }

	int x = i - k; set<int> ms;
	for (int j = 0; j <= x / 2; j++) {
		ms.insert(mex(j) ^ mex(x - j));
	}

	int count = 0;
	for(auto y : ms){ 
		if (y == count) { count++; }
		else { break; }
	}

	DP[i] = count; return count;
}	

int main() {
	int T; cin >> T;
	for (int z = 0; z < T; z++) {
		for (int i = 0; i < 52; i++) { DP[i] = -1; }
		cin >> n >> k;

		bool res = mex(n) == 0; string s = res ? "Losing" : "Winning";
		cout << "Case " << z+1 << ": " << s << endl;
	}
}
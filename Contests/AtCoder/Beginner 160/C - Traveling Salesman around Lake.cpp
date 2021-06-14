#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	int N, K; cin >> K >> N;
	vector<int> CW(N);
	for (int i = 0; i < N; i++) {
		int temp; cin >> temp;
		CW[i] = temp;
	}

	int ans = CW[N-1]-CW[0];
	ans = min(ans, K - (CW[1] - CW[0]));
	for (int i = 1; i < N; i++) {
		ans = min(ans, K - (CW[i] - CW[i - 1]));
		ans = min(ans, K - ((i == N - 1 ? CW[0] : CW[i + 1]) - CW[i]));
	}

	cout << ans << endl;
}
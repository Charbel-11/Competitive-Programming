#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 998244353;

ll choose[70][70];
void fillComb() {
    int limit = 70;
    for (int i = 0; i < limit; i++) { choose[i][i] = 1; choose[i][0] = 1; }
    for (int i = 1; i < limit; i++)
        for (int j = 1; j < i; j++)
            choose[i][j] = (choose[i - 1][j - 1] + choose[i - 1][j]) % mod;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

    fillComb();
    vector<ll> ansA(61, 0), ansB(61, 0);
    ansA[2] = 1; ansB[2] = 0;
    for(int n = 4; n <= 60; n += 2){
        ansA[n] = (choose[n-1][n/2-1] + ansB[n-2]) % mod;
        ansB[n] = (choose[n][n/2] - ansA[n] - 1) % mod;
        if (ansB[n] < 0){ ansB[n] += mod; }
    }

	int t; cin >> t;
	while(t--){
        int n; cin >> n;
        cout << ansA[n] << ' ' << ansB[n] << ' ' << 1 << '\n';
	}
}
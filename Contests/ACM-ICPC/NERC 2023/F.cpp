#include <bits/stdc++.h>
using namespace std;
typedef long double ld;

struct contract{
    ld x, w, c;
    contract(ld _x, ld _w, ld _c): x(_x), w(_w), c(_c){}

    bool operator<(const contract& rhs) const{
        if (x != rhs.x){ return x < rhs.x; }
        return c < rhs.c;
    }
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; ld k; cin >> n >> k;
    vector<contract> contracts;
    for(int i = 0; i < n; i++){
        ld x, w, c; cin >> x >> w >> c; x /= (ld)100.0;
        contracts.emplace_back(x, w, c);
    }
    sort(contracts.begin(), contracts.end());

    vector<ld> dp(n, 0);
    for(int i = 0; i < n; i++){ dp[i] = -contracts[i].w; }

    for(int r = 1; r < n; r++){
        for(int l = 0; l < r; l++){
            ld dx = contracts[r].x - contracts[l].x;
            ld dy = contracts[r].c - contracts[l].c;

            ld area = dx * contracts[l].c + dx * dy / 2.0;
            ld curVal = k * area - contracts[r].w;

            dp[r] = max(dp[r], dp[l] + curVal);
        }
    }

    cout << setprecision(7) << fixed << max(*max_element(dp.begin(), dp.end()), (ld)0.0) << '\n';
}


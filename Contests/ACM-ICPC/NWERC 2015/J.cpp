#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
    for(int i = 0; i < n; i++){
        int x; cin >> x;
        int ans = 0, curBit = 0, curPow2 = 1;

        while(x || (curBit && ans + curPow2 <= 255)){
            if ((x ^ curBit) & 1) { ans += curPow2; curBit = 1; }
            else{ curBit = 0; }
            curPow2 *= 2; x /= 2;
        }

        cout << ans << ' ';
    }
}


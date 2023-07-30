#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while(t--){
		int b, c, h; cin >> b >> c >> h; b-=2;
        int x = c+h; x--;
        int ans = 3;
        while (b > 0 && x > 0){
            ans += 2;
            b--; x--;
        }
        cout << ans << '\n';
	}
}
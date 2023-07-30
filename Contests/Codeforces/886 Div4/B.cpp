#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while(t--){
		int n; cin >> n;
        int ans = 1, maxB = 0;
        for(int i = 0; i < n; i++){
            int a, b; cin >> a >> b;
            if (a > 10){ continue; }
            if (b > maxB){
                maxB = b;
                ans = i+1;
            }
        }

        cout << ans << '\n';
	}
}
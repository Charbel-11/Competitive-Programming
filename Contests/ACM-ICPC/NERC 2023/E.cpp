#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while(t--){
		int n, a, b; cin >> n >> a >> b;
        if (a > b){ cout << 1 << '\n'; }
        else{ cout << (n+a-1)/a << '\n'; }
	}
}
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
    string s; cin >> s;

    int ans = 0, curR = 0;
    for(int i = 0; i < n; i++){
        curR += (s[i] == 'W');
    }

    ans = curR;
    for(int i = n; i < s.size(); i++){
        curR += (s[i] == 'W');
        curR -= (s[i-n] == 'W');
        ans = max(ans, curR);
    }

    cout << ans << '\n';
}
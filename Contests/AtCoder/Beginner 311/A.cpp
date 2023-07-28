#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
    string s; cin >> s;
    set<char> seen; int ans = 0;
    for(auto &c : s){
        seen.insert(c); ans++;
        if (seen.size() == 3){ break; }
    }

    cout << ans << '\n';
}
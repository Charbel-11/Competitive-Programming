#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, p, q; cin >> n >> p >> q;
    vector<int> D(n); for(auto &x : D){ cin >> x; }
    sort(D.begin(), D.end());

    int ans = min(p, q + D[0]);
    cout << ans << '\n';
}
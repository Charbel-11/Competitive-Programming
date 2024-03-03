#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int n; cin >> n;
    vector<ll> curDP(n+1, 0), nextDP(n+1, 0);
    string s; cin >> s; curDP[0] = 1;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            if (s[i - 1] == '>') { nextDP[j] += (curDP[i - 1] - (j ? curDP[j - 1] : 0)); nextDP[j] %= mod; }
            else { nextDP[j] += (j ? curDP[j - 1] : 0); nextDP[j] %= mod; }
            if (j) { nextDP[j] += nextDP[j - 1]; nextDP[j] %= mod; }
        }
        swap(curDP, nextDP);
        for(int j = 0; j < n; j++){ nextDP[j] = 0; }
    }

    if (curDP[n - 1] < 0) { curDP[n - 1] += mod; }
    cout << curDP[n - 1] << '\n';
}

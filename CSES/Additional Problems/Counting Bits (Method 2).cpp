#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n; cin >> n; n++;
    ll ans = 0;

    for (int i = 1; i <= 50; i++) {
        ll curPow = 1ll << i;
        ans += (n / curPow) * (curPow / 2);
        ll rem = n % curPow;
        if (rem > curPow / 2) { ans += rem - (curPow / 2); }
    }

    cout << ans << '\n';
}
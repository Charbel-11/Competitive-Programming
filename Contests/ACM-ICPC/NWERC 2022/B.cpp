#include <bits/stdc++.h>
using namespace std;
typedef double ld;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int h, r, da, dw; cin >> h >> r >> da >> dw;
    ld sq = sqrt(da * dw);
    cout << fixed << setprecision(9) << ((sq - da) / (dw - da)) * h << '\n';
}
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <complex>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;
using cd = complex<double>;
const double PI = acos(-1);

void FFT(vector<cd>& a, bool inverse) {
    int n = a.size();       // Assumes n is a power of 2

    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) { j ^= bit; }
        j ^= bit;

        if (i < j) { swap(a[i], a[j]); }
    }

    for (int len = 2; len <= n; len <<= 1) {
        double angle = 2 * PI / len * (inverse ? -1 : 1);
        cd Wn(cos(angle), sin(angle));
        for (int i = 0; i < n; i += len) {
            cd W(1);
            for (int j = 0; j < (len >> 1); j++, W *= Wn) {
                cd even = a[i + j], odd = W * a[i + j + (len >> 1)];
                a[i + j] = even + odd;
                a[i + j + (len >> 1)] = even - odd;
            }
        }
    }

    if (inverse) {
        for (cd& x : a) { x /= n; }
    }
}

//Polynomial multiplication in O(nlogn)
vector<ll> multiply(const vector<ll>& a, const vector<ll>& b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());

    int s = (int)a.size() + (int)b.size() - 1, n = 1;
    while (n < s) { n <<= 1; }
    fa.resize(n);  fb.resize(n);

    FFT(fa, false); FFT(fb, false);
    for (int i = 0; i < n; i++) { fa[i] *= fb[i]; }
    FFT(fa, true);

    vector<ll> result(s);
    for (int i = 0; i < s; i++) { result[i] = round(fa[i].real()); }
    return move(result);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int n, m; cin >> n >> m;
    vector<ll> a(n), b(m);
    for (auto& x : a) { cin >> x; }
    for (auto& x : b) { cin >> x; }
    reverse(b.begin(), b.end());

    auto c = multiply(a, b);
    for (auto& x : c) { cout << x << ' '; }
}
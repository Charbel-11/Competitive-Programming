#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

const ld PI = acos(-1);
void FFT(vector<complex<ld>>& a, bool inverse) {
    int n = (int)a.size(); //Assumes n is a power of 2
    for (int i = 1, j = 0; i < n; i++) { //Sorting by reverse bits
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        if (i < (j ^= bit)) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        ld O = 2 * PI / len * (inverse ? -1 : 1);
        complex<ld> Wn(cos(O), sin(O));
        for (int i = 0; i < n; i += len) {
            complex<ld> W(1);
            for (int j = 0; j < (len >> 1); j++, W *= Wn) {
                complex<ld>even=a[i+j], odd = W * a[i + j + (len >> 1)];
                a[i+j] = even + odd; a[i + j + (len >> 1)] = even - odd;
            }
        }
    }
    if (inverse) for (auto& x : a) x /= n;
}
vector<ll> polyMult(const vector<ll>& a) {
    vector<complex<ld>> A(a.begin(), a.end()), B(a.begin(), a.end());
    int N = (int)a.size(); int M = N;
    int n = 1; while (n < (N + M)) { n <<= 1; }
    A.resize(n, 0); B.resize(n, 0);
    FFT(A, false);
    for (int i = 0; i < n; i++) A[i] *= A[i];
    FFT(A, true); vector<ll> res(n);
    for (int i = 0; i < n; i++) res[i] = (ll)round(A[i].real());
    return res;
}

const int N = 500005;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	vector<ll> numDiv(N, 0);
    for(int i = 1; i < N; i++){
        for(int j = i; j < N; j += i){
            numDiv[j]++;
        }
    }

    auto cnt = polyMult(numDiv);
    int t; cin >> t;
    while(t--){
        int l, r; cin >> l >> r;
        int curAns = l; ll curCnt = cnt[l];
        for(int i = l+1; i <= r; i++){
            if (cnt[i] > curCnt){ curCnt = cnt[i]; curAns = i; }
        }
        cout << curAns << " " << curCnt << '\n';
    }
}


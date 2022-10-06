#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> ZAlgo(const vector<int>& s) {
    int n = s.size();
    vector<int> z(n, 0);
    int L = 0, R = 0;
    for (int i = 1; i < n; i++) {
        if (i > R) {
            L = R = i;
            while (R < n && s[R - L] == s[R]) { R++; }
            z[i] = R - L; R--;
        }
        else {
            int k = i - L;
            if (z[k] < R - i + 1) { z[i] = z[k]; continue; }
            L = i;
            while (R < n && s[R - L] == s[R]) { R++; }
            z[i] = R - L; R--;
        }
    }
    return move(z);
}

bool check(int i, int k, int n){
    if (k == 0) { return i == 0; }
    if (k == 1) { return i > 0; }
    if (n == 2) { return i == (k % 2); }
    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ifstream cin("in.txt");
    ofstream cout("out.txt");

    int t; cin >> t;
    for (int qq = 1; qq <= t; qq++) {
        int n, k; cin >> n >> k;
        vector<int> A(n), B(n);
        for(auto &x : A) { cin >> x; }
        for(auto &x : B) { cin >> x; }

        vector<int> conc = B;
        conc.push_back(-1);
        for(auto &x : A){ conc.push_back(x); }
        for(auto &x : A){ conc.push_back(x); }
        vector<int> ZFunc = ZAlgo(conc);

        bool OK = false;
        for(int i = n + 1; i <= 2 * n; i++) {
            if (ZFunc[i] == n && check(i - n - 1, k, n)) {
                OK = true;
                break;
            }
        }

        cout << "Case #" << qq << ": " << (OK ? "YES" : "NO") << '\n';
    }
}
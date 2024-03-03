#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ifstream cin("in.txt");
    ofstream cout("out.txt");

    int t; cin >> t;
    for (int qq = 1; qq <= t; qq++) {
        int n; cin >> n;
        vector<int> X(n); for(auto &x : X){ cin >> x; }
        sort(X.begin(), X.end());

        double ans = 0;
        if (n == 5){
            double c1 = ((X[4] + X[2] + 0.0) - (X[1] + X[0] + 0.0))/2.0;
            double c2 = ((X[4] + X[3] + 0.0) - (X[2] + X[0] + 0.0))/2.0;
            ans = max(c1, c2);
        }
        else{
            ans = (X[n-1] + X[n-2] + 0.0 - (X[1] + X[0] + 0.0))/2.0;
        }

        cout << "Case #" << qq << ": " << fixed << setprecision(8) << ans << '\n';
    }
}

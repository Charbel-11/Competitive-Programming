#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

//Finds {prime, multiplicity} in O(sqrt(x))
vector<pair<int, int>> getPrimeFactorsSlow(int x) {
    vector<pair<int, int>> ans; ll num = 2;
    while (x != 1 && num*num <= x) {
        if (x % num == 0) {
            int k = 0;
            while (x % num == 0) { x /= num; k++; }
            ans.push_back({ num,k });
        }
        num++;
    }
    if (x != 1) { ans.push_back({ x,1 }); }
    return ans;
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ifstream cin("in.txt");
    ofstream cout("out.txt");

    int t; cin >> t;
    for (int qq = 1; qq <= t; qq++) {
        int P; cin >> P;
        auto fact = getPrimeFactorsSlow(P);

        vector<int> ans; int minSum = 0;
        for(auto &p : fact){
            minSum += p.first * p.second;
            for(int j = 0; j < p.second; j++){ ans.push_back(p.first); }
        }
        if (minSum > 41){
            cout << "Case #" << qq << ": " << -1 << '\n';
            continue;
        }

        for(int j = 0; j < 41 - minSum; j++){
            ans.push_back(1);
        }

        cout << "Case #" << qq << ": " << ans.size();
        for(auto &x : ans){ cout << ' ' << x; }
        cout << '\n';
    }
}
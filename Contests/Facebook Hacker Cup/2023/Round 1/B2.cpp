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

set<vector<int>> seen;
vector<int> bestAns;

void tryAllAns(vector<int> factors, int rem){
    if (seen.count(factors)){ return; }
    seen.insert(factors);

    if (factors.size() + rem < bestAns.size()){
        bestAns = factors;
        for(int x = 0; x < rem; x++){ bestAns.push_back(1); }
    }

    for(int i = 0; i < factors.size(); i++){
        for(int j = i + 1; j < factors.size(); j++){
            int diff = factors[i] * factors[j] - factors[i] - factors[j];
            if (diff > rem){ continue; }
            vector<int> newFactors = factors;
            newFactors[i] *= newFactors[j];
            newFactors.erase(newFactors.begin() + j, newFactors.begin() + j+1);
            sort(newFactors.begin(), newFactors.end());
            tryAllAns(newFactors, rem - diff);
        }
    }
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

        vector<int> divs; int minSum = 0;
        for(auto &p : fact){
            minSum += p.first * p.second;
            for(int j = 0; j < p.second; j++){ divs.push_back(p.first); }
        }
        if (minSum > 41){
            cout << "Case #" << qq << ": " << -1 << '\n';
            continue;
        }

        vector<int> ans = divs;
        int rem = 41-minSum;
        for(int j = 0; j < rem; j++){
            ans.push_back(1);
        }
        bestAns = ans;

        sort(divs.begin(), divs.end());
        tryAllAns(divs, rem);

        cout << "Case #" << qq << ": " << bestAns.size();
        for(auto &x : bestAns){ cout << ' ' << x; }
        cout << '\n';
    }
}
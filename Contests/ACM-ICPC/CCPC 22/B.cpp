#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> getHalfDivisors(int x) {
    int d = 2;
    vector<int> ans;
    while(d*d <= x){
        if (x % d == 0){
            ans.push_back(d);
        }
        d++;
    }
    return ans;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
    vector<int> s(n); for(auto &x : s){ cin >> x; }
    vector<int> ans(n, 1), order(n-1, -1);

    int numOnes = 0;
    for(int i = 1; i < n; i++){
        if (s[i] == s[i-1]-1){
            order[i-1] = ++numOnes;
        }
    }

    if (numOnes == n-1){
        ans[n-1] = s[n-1];
        for(int i = 0; i < n-1; i++){ order[i] = i+1; }

        for(auto &x : ans){ cout << x << ' '; }
        cout << '\n';
        for(auto &x : order){ cout << x << '\n'; }
        return 0;
    }

    bool OK = (n - numOnes) < 30;
    if(!OK){
        cout << -1 << '\n';
        return 0;
    }

    set<pair<vector<int>, vector<int>>> candidates;
    candidates.insert({{s[n-1]},{}});
    for(int i = n-1; i > 0; i--){
        if (s[i] == s[i-1]-1){
            continue;
        }

        set<pair<vector<int>, vector<int>>> newCandidates;
        for(auto &[v, ord] : candidates){
            unordered_set<int> seen;
            for(int j = 0; j < v.size(); j++){
                if (seen.count(v[j])){ continue; }
                seen.insert(v[j]);

                auto divs = getHalfDivisors(v[j]);
                for(auto &d : divs){
                    if (s[i-1] - s[i] == d + v[j]/d - v[j]){
                        vector<int> newV = v, newOrd = ord;

                        for(auto &o : newOrd){ if (o >= j+1) o++; }
                        newOrd.push_back(j + 1);

                        newV[j] = d;
                        newV.insert(newV.begin() + j,v[j]/d);
                        newCandidates.insert({newV, newOrd});
                    }
                }
            }
        }
        swap(candidates, newCandidates);
        if (candidates.empty()){ break; }
    }

    if (candidates.empty()){ OK = false; }
    else{
        auto [remV, ordV] = *candidates.begin();
        reverse(ordV.begin(), ordV.end());
        for(int i = numOnes; i < n; i++){
            ans[i] = remV[i-numOnes];
        }

        int idx = 0;
        for(int i = 0; i < n - 1; i++){
            if (order[i] == -1){
                order[i] = numOnes + ordV[idx++];
            }
        }
    }

    if (!OK){ cout << -1 << '\n'; }
    else {
        for(auto &x : ans){ cout << x << ' '; }
        cout << '\n';
        for(auto &x : order){ cout << x << '\n'; }
    }
}
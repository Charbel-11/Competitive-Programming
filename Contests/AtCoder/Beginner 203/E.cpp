

#include <iostream>
#include <unordered_set>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int n, m; cin >> n >> m;
    vector<pair<int, int>> blackP(m);
    for (auto& p : blackP) { cin >> p.first >> p.second; }
    sort(blackP.begin(), blackP.end());

    unordered_set<int> candidates; candidates.insert(n);

    for (int i = 0; i < blackP.size();) {
        int curRow = blackP[i].first;
        vector<int> toRem, toAdd;
        while (i < m && blackP[i].first == curRow) {
            if (candidates.count(blackP[i].second)) { toRem.push_back(blackP[i].second); }
            if (candidates.count(blackP[i].second - 1)) { toAdd.push_back(blackP[i].second); }
            if (candidates.count(blackP[i].second + 1)) { toAdd.push_back(blackP[i].second); }
            i++;
        }

        for (auto& x : toRem) { candidates.erase(x); }
        for (auto& x : toAdd) { candidates.insert(x); }
    }

    cout << candidates.size() << '\n';
}
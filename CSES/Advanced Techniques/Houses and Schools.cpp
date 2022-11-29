// For dp of the form dp[i][k] = min_j<i (dp[j][k-1] + C(j+1,i))
// Requires the best j (i.e., splitting point) to satisfy optSplit(l, r) <= optSplit(l, r+1)
// or sufficiently, that C(a,c) + C(b,d) <= C(a,d) + C(b,c) for a<=b<=c<=d

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, m;
vector<ll> dpPrev, dpCur;
vector<vector<ll>> C;

// compute dpCur[l], ..., dpCur[r] (inclusive) for an optimal split point in [optSplitL, optSplitR]
// O(mn logn) time
void computeDP(int l, int r, int optSplitL, int optSplitR) {
    if (l > r) { return; }

    int mid = (l + r) >> 1;
    pair<ll, int> best = {LLONG_MAX, -1};

    for (int k = optSplitL; k <= min(mid, optSplitR); k++) {
        ll curCost = (k ? dpPrev[k - 1] : 0) + C[k][mid];
        best = min(best, {curCost, k});
    }

    dpCur[mid] = best.first;
    int optSplit = best.second;

    computeDP(l, mid - 1, optSplitL, optSplit);
    computeDP(mid + 1, r, optSplit, optSplitR);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    vector<ll> c(n); for(auto &x : c){ cin >> x; }

    C = vector<vector<ll>>(n, vector<ll>(n));
    dpPrev.resize(n); dpCur.resize(n);

    for(int i = 0; i < n; i++){
        ll curSum = 0, prefSum = c[i], cost = 0;
        int median = i;

        for(int j = i; j < n; j++){
            curSum += c[j];
            cost += (j-median) * c[j];
            while (prefSum < curSum/2){
                cost += prefSum - (curSum - prefSum);
                prefSum += c[++median];
            }

            C[i][j] = cost;
        }
    }

    for (int i = 0; i < n; i++) {
        dpPrev[i] = C[0][i];
    }
    for (int k = 1; k < m; k++) {
        computeDP(0, n - 1, 0, n - 1);
        swap(dpPrev, dpCur);
    }
    cout << dpPrev[n - 1] << '\n';
}
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
using namespace std;

int numBit(int n) {
    int ans = 0;
    while (n) { ans++; n &= (n - 1); }
    return ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int n, m, p; cin >> n >> m >> p;
    vector<string> friends(n);
    for (auto& s : friends) { cin >> s; }

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0, n + 10);


    string ans(m, '0'); int best = 0;
    for (int tt = 0; tt < 50; tt++) {
        int idx = dis(gen) % n;

        vector<int> maskIdx;
        for (int i = 0; i < m; i++) {
            if (friends[idx][i] == '1') { maskIdx.push_back(i); }
        }

        vector<int> cnt(1 << p, 0);
        for (int i = 0; i < n; i++) {
            int curMask = 0;
            for (int j = 0; j < maskIdx.size(); j++) {
                if (friends[i][maskIdx[j]] == '1') { curMask |= (1 << j); }
            }
            cnt[curMask]++;
        }


        for (int mask = 0; mask < (1 << p); mask++) {
            for (int curM = (mask - 1) & mask; curM > 0; curM = (curM - 1) & mask) {
                cnt[curM] += cnt[mask];
            }
        }

        for (int mask = 0; mask < (1 << p); mask++) {
            if (cnt[mask] >= (n + 1) / 2 && numBit(mask) > best) {
                best = numBit(mask);
                ans = string(m, '0');
                for (int j = 0; j < maskIdx.size(); j++) {
                    if (mask & (1 << j)) { ans[maskIdx[j]] = '1'; }
                }
            }
        }
    }

    //50(np+3^p)

    cout << ans << '\n';
}
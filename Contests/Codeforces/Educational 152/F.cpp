#include <bits/stdc++.h>
using namespace std;

map<int, int> ans;

void getPartitions(const vector<int>& a, int k){
    int n = a.size();
    if (n <= 4){
        int bestMin = -1;
        for(int m = 0; m < (1<<n); m++){
            int curMin = (1 << 30);
            for(int i = 0; i < n; i++){
                for(int j = i + 1; j < n; j++){
                    if (((m >> i) & 1) ^ ((m >> j) & 1)){
                        continue;
                    }
                    curMin = min(curMin, a[i] ^ a[j]);
                }
            }
            if (curMin > bestMin){
                bestMin = curMin;
                for(int i = 0; i < n; i++){
                    if (m & (1 << i)){ ans[a[i]] = 1; }
                    else{ ans[a[i]] = 0; }
                }
            }
        }

        return;
    }

    vector<int> a1, a2;
    for(auto &x : a){
        if (x & (1<<k)){ a1.push_back(x); }
        else{ a2.push_back(x); }
    }
    getPartitions(a1, k-1);
    getPartitions(a2, k-1);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
    vector<int> a(n); for(auto &x : a){ cin >> x; }

    getPartitions(a, 29);
    for(auto &x : a) { cout << ans[x]; }
    cout << '\n';
}
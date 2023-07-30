#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int n; cin >> n;
    vector<int> p(n); for(auto &x : p){ cin >> x; }

    vector<int> leftLarger(n, -1), rightLarger(n, n);
    vector<int> leftSmaller(n, -1), rightSmaller(n, n);

    stack<int> s;
    for(int i = 0; i < n; i++){
        while(!s.empty() && p[i] > p[s.top()]){
            rightLarger[s.top()] = i; s.pop();
        }
        if (!s.empty()){ leftLarger[i] = s.top(); }
        s.push(i);
    }

    while(!s.empty()){ s.pop(); }
    for(int i = 0; i < n; i++){
        while(!s.empty() && p[i] < p[s.top()]){
            rightSmaller[s.top()] = i; s.pop();
        }
        if (!s.empty()){ leftSmaller[i] = s.top(); }
        s.push(i);
    }

    ll ans = 0;
    for(int i = 0; i < n; i++){
        int l = leftLarger[i], r = rightLarger[i];
        if (i - l <= r - i){
            int j = i - 1;
            while(j > l){
                int ml = leftSmaller[j], mr = rightSmaller[j];
                ans += 1ll * (j - max(ml, l)) * (min(mr, r) - i);
                j = ml;
            }
        }
        else{
            ans += 1ll * (i - l) * (r - i) - 1;
            int j = i + 1;
            while(j < r){
                int ml = leftSmaller[j], mr = rightSmaller[j];
                ans -= 1ll * (min(mr, r) - j) * (i - max(ml, l));
                j = mr;
            }
        }
    }

    cout << ans << '\n';
}
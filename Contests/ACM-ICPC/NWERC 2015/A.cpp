#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> v;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m; cin >> n >> m; v.resize(n);
    for(auto &[a, s] : v) cin >> a >> s;

    sort(v.begin(), v.end()); int res = 0;
    priority_queue<int, vector<int>, greater<int>> pq;
    for (auto &[a, s] : v) {
        // If a computer has been inactive for >= m minutes
        // treat is as a new computer.
        while (!pq.empty() && pq.top() < a - m) pq.pop();
        // If all computers are inactive or the earliest available
        // computer is still being used, unlock a new one. Otherwise
        // use the earliest available one.
        if (pq.empty() || pq.top() > a) ++res; else pq.pop();
        pq.push(a + s);
    }
    cout << n - res << '\n';
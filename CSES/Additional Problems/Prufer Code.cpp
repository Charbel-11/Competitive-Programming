#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
    vector<int> code(n-2), freq(n, 0);
    for(auto &x : code){
        cin >> x; x--;
        freq[x]++;
    }

    set<int> leaves;
    vector<pair<int, int>> edges;
    for(int i = 0; i < n; i++){
        if (freq[i] == 0){ leaves.insert(i); }
    }

    for(int i = 0; i < n-2; i++){
        int cur = *leaves.begin();
        leaves.erase(leaves.begin());

        edges.emplace_back(cur, code[i]);

        freq[code[i]]--;
        if (freq[code[i]] == 0){ leaves.insert(code[i]); }
    }

    edges.emplace_back(*leaves.begin(), *leaves.rbegin());

    for(auto &p : edges){
        cout << p.first + 1 << " " << p.second + 1 << '\n';
    }
}
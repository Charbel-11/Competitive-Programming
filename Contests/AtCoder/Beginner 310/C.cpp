#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int N; cin >> N;
    unordered_set<string> S;
    for(int i = 0; i < N; i++){
        string cur; cin >> cur;
        string curRev = cur;
        reverse(curRev.begin(), curRev.end());

        if (S.count(cur) || S.count(curRev)){ continue; }
        S.insert(cur);
    }

    cout << S.size() << '\n';
}
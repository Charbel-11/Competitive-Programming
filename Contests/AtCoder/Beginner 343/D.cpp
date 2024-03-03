#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, t; cin >> n >> t;
    vector<ll> scores(n, 0);
    map<ll, int> freq; freq[0] = n;

    for(int i = 0; i < t; i++){
        int a, b; cin >> a >> b; a--;
        freq[scores[a]]--;
        if (freq[scores[a]] == 0){ freq.erase(scores[a]); }

        scores[a] += b;
        freq[scores[a]]++;
        cout << freq.size() << '\n';
    }
}


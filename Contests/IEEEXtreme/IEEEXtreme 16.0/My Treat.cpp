#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while(t--){
		int m; cin >> m;
        set<string> people;
        map<string, int> inDeg, outDeg;
        for(int i = 0; i < m; i++){
            string sender; cin >> sender;
            people.insert(sender);

            int n; cin >> n;
            outDeg[sender] += n;
            for(int j = 0; j < n; j++){
                string rec; cin >> rec;
                people.insert(rec);
                inDeg[rec] += 1;
            }
        }

        int numDeals = 0, maxDays = 0;
        for(auto &p : people){
            int out = outDeg[p], in = inDeg[p];
            if (out > in){
                int curDif = out - in;
                numDeals += curDif;
                maxDays = max(maxDays, curDif);
            }
        }

        cout << numDeals << ' ' << maxDays << '\n';
	}
}
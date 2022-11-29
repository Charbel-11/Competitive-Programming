#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, q; cin >> n >> q;
    map<int, set<int>> m;

    for(int i = 0; i < q; i++){
        int t,a,b; cin >> t >> a >> b;
        if (t==1){
            m[a].insert(b);
        }
        else if (t==2){
            m[a].erase(b);
        }
        else{
            if (m[a].count(b) && m[b].count(a)){
                cout << "Yes\n";
            }
            else{
                cout << "No\n";
            }
        }
    }
}
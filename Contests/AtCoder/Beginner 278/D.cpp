#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
    vector<ll> A(n); for(auto &x : A){ cin >> x; }

    vector<int> non0;
    for(int i = 0; i < n; i++){
        if (A[i] > 0){
            non0.push_back(i);
        }
    }

    ll allVal = 0;
    int q; cin >> q;
    while(q--){
        int t; cin >> t;
        if (t==1){
            cin >> allVal;
            for(auto &i : non0){
                A[i] = 0;
            }
            non0.clear();
        }
        else if (t==2){
            int i; ll x; cin >> i >> x; i--;
            if (A[i] == 0){ non0.push_back(i); }
            A[i] += x;
        }
        else{
            int i; cin >> i; i--;
            cout << allVal + A[i] << '\n';
        }
    }
}
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
    vector<vector<int>> A(n, vector<int>(n));
    for(auto &v : A){
        string cur; cin >> cur;
        for(int i = 0; i < n; i++){
            v[i] = (cur[i] == '1');
        }
    }

    vector<vector<int>> ans = A;
    vector<int> bdry;
    for(int j = 0; j < n; j++){ bdry.push_back(A[0][j]); }
    for(int i = 1; i < n; i++){ bdry.push_back(A[i][n-1]); }
    for(int j = n-2; j >=0; j--){ bdry.push_back(A[n-1][j]); }
    for(int i = n-2; i > 0; i--){ bdry.push_back(A[i][0]); }

    int idx = bdry.size() - 1;
    for(int j = 0; j < n; j++){
        ans[0][j] = bdry[idx++];
        if (idx == bdry.size()){idx=0;}
    }
    for(int i = 1; i < n; i++){ ans[i][n-1] = bdry[idx++]; }
    for(int j = n-2; j >= 0; j--){ ans[n-1][j] = bdry[idx++]; }
    for(int i = n-2; i > 0; i--){ ans[i][0] = bdry[idx++]; }

    for(auto &v : ans){
        for(auto &x : v){
            cout << x;
        }
        cout << '\n';
    }
}
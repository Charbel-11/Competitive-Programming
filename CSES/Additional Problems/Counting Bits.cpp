#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
 
ll numBits(string& s){
    int n = s.size();
    vector<vector<ll>> dpNum(n, vector<ll>(2, 0)), dpOnes(n, vector<ll>(2, 0));
    
    dpNum[0][1] = dpNum[0][0] = 1;
    dpOnes[0][1] = 1; 
    for(int i = 1; i < n; i++){
        dpNum[i][1] = dpNum[i-1][1];
        dpNum[i][0] = 2 * dpNum[i-1][0];
        if (s[i] == '1'){ 
            dpNum[i][0] += dpNum[i-1][1];
            
            dpOnes[i][0] = 2 * dpOnes[i-1][0] + dpNum[i-1][0] + dpOnes[i-1][1];
            dpOnes[i][1] = dpOnes[i-1][1] + 1;
        }
        else{
            dpOnes[i][0] = 2 * dpOnes[i-1][0]+ dpNum[i-1][0];
            dpOnes[i][1] = dpOnes[i-1][1];
        }
    }
    
    return dpOnes[n-1][0] + dpOnes[n-1][1];
}
 
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	ll n; cin >> n;
	string s = "";
	while(n){
	    if (n%2){ s.push_back('1'); }
	    else{ s.push_back('0'); }
	    n/=2; 
	}
	reverse(s.begin(), s.end());
	
	cout << numBits(s) << '\n';
}
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;
typedef long long ll;
const int SZ = 200002;
int fact2[SZ];
 
void fillFact2(){
    fact2[0] = 0;
    for(int i = 1; i < SZ; i++){
        int twos = 0, cur = i;
        while(cur % 2 == 0){ cur /= 2; twos++; }
        fact2[i] = fact2[i-1] + twos;
    }
}
 
bool nCkisEven(int n, int k){
    int num2 = fact2[n];
    int den2 = fact2[k] + fact2[n-k];
    
    return num2 > den2;
}
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
 
    fillFact2();
    int n; cin >> n;
    vector<int> nums(n); for(auto &x : nums){ cin >> x; }
    
    int ans = 0; n--;
    for(int i = 0; i <= n; i++){
        if (!nCkisEven(n, i)){ ans ^= nums[i]; }
    }
    
    cout << ans << '\n';
}
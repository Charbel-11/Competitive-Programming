#include <iostream>
#include <vector>
#include <stack>
using namespace std;
 
vector<int> preorder, postorder;
vector<int> inOrderIdx;
 
void getPostorder(int& iP, int lI, int rI){
    if (lI > rI){ return; }
    int cur = preorder[iP++];
    
    getPostorder(iP, lI, inOrderIdx[cur]-1);
    getPostorder(iP, inOrderIdx[cur]+1, rI);
   
    postorder.push_back(cur);
}
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    
    int n; cin >> n;
    preorder.resize(n);
    for(auto &x : preorder){ cin >> x; }
 
    inOrderIdx.resize(n + 1);
    for(int i = 0; i < n; i++){
        int cur; cin >> cur;
        inOrderIdx[cur] = i;
    }
    
    int i = 0;
    getPostorder(i, 0, n-1);
    for(auto &x : postorder){ cout << x << " "; }
}
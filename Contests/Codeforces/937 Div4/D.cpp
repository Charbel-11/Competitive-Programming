#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

    vector<int> binaryDecimals; binaryDecimals.push_back(100000);
    for(int i = 1; i < (1<<5); i++){
        string s = "00000";
        for(int j = 0; j < 5; j++){
            if (i & (1 << j)){ s[j] = '1'; }
        }
        if (stoi(s)==1){ continue; }
        binaryDecimals.push_back(stoi(s));
    }

    vector<int> smallerBinaryDecimals;
    unordered_set<int> canGenerate; canGenerate.insert(1);
    for(auto x : binaryDecimals){
        canGenerate.insert(x);
        if (x < 1e4){ smallerBinaryDecimals.push_back(x); }
        if (x < 1000) { smallerBinaryDecimals.push_back(x); }
        if (x < 100) { smallerBinaryDecimals.push_back(x); smallerBinaryDecimals.push_back(x); }
    }

    for(int i = 1; i < (1 << smallerBinaryDecimals.size()); i++){
        int curNum = 1;
        for(int j = 0; j < smallerBinaryDecimals.size(); j++){
            if (i & (1 << j)){
                curNum *= smallerBinaryDecimals[j];
            }
            if (curNum > 1e5){ break; }
        }
        canGenerate.insert(curNum);
    }

	int t; cin >> t;
	while(t--){
		int n; cin >> n;
        if (canGenerate.count(n)){ cout << "YES\n"; }
        else { cout << "NO\n"; }
	}
}


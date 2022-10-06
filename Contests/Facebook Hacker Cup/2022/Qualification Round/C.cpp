#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<string> generateAllCodewordsOfLength(int n){
    int numCodewords = 1 << n;
    vector<string> ans;
    for(int i = 0; i < numCodewords; i++){
        string curCode;
        for(int j = 0; j < n; j++){
            if ((i >> j) & 1){ curCode.push_back('.'); }
            else{ curCode.push_back('-'); }
        }
        ans.push_back(curCode);
    }
    return std::move(ans);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ifstream ifs("in.txt");
    ofstream ofs("out.txt");

    int t; ifs >> t;
    for (int qq = 1; qq <= t; qq++) {
        int n; ifs >> n;
        string c1; ifs >> c1;

        int neededExtraDigits = 0, numOfGeneratableCodes = 1;
        while(numOfGeneratableCodes < n - 1){
            neededExtraDigits++; numOfGeneratableCodes *= 2;
        }
        auto codeSuffixes = generateAllCodewordsOfLength(neededExtraDigits);
        while (codeSuffixes.size() > n - 1) { codeSuffixes.pop_back(); }

        char startChar = (c1[0] == '.' ? '-' : '.');
        ofs << "Case #" << qq << ": \n";
        for(auto &s : codeSuffixes){
            ofs << startChar << s << '\n';
        }
    }
}
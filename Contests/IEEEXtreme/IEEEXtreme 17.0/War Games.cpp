#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void getVecFromString(deque<int>& p1, string& p1S){
    for(int i = 0; i < p1S.size(); i+=2){
        if (p1S[i] == 'T') { p1.push_back(10); }
        else if (p1S[i] == 'J') { p1.push_back(11); }
        else if (p1S[i] == 'Q') { p1.push_back(12); }
        else if (p1S[i] == 'K') { p1.push_back(13); }
        else if (p1S[i] == 'A') { p1.push_back(14); }
        else{ p1.push_back(p1S[i] - '1'); }
    }
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
    string tmp; getline(cin, tmp);
    for(int i = 0; i < n; i++){
        deque<int> p1, p2;
        string p1S; getline(cin, p1S);
        string p2S; getline(cin, p2S);

        getVecFromString(p1, p1S);
        getVecFromString(p2, p2S);

        int cntAfterChange = 0, ans = -1;
        while(true){
            if (p1.empty()){ ans = 2; break; }
            if (p2.empty()){ ans = 1; break; }

            int p1F = p1.front(), p2F = p2.front();
            p1.pop_front(); p2.pop_front();
            if (p1F > p2F){ p1.push_back(p2F); cntAfterChange = 0; }
            else if (p2F > p1F){ p2.push_back(p1F); cntAfterChange = 0; }
            else{ p1.push_back(p1F); p2.push_back(p2F); cntAfterChange++; }

            if (cntAfterChange == max(p1.size(), p2.size()) + 1){ break; }
        }

        if (ans == -1) { cout << "draw\n"; }
        else if (ans == 1){ cout << "player 1\n"; }
        else { cout << "player 2\n"; }
    }
}


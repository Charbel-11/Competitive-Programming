#include <bits/stdc++.h>
using namespace std;

vector<set<string>> sequences;

bool CheckPasswords(const string &P1, const string &P2){
    int N1 = P1.size(), N2 = P2.size();
    if(P1 == P2) { return false; }
    int L = 0, R1 = N1 - 1, R2 = N2 - 1;
    while(P1[L] == P2[L]) ++L;
    while(P1[R1] == P2[R2]) {--R1, --R2;}
    int R = max(R1, R2);

    int minLen1 = R1 - L + 1, minLen2 = R2 - L + 1;
    if(max(minLen1, minLen2) > 10) { return true; }

    for(int len1 = minLen1; len1 <= 10; ++len1)
        for(int len2 = minLen2; len2 <= 10; ++len2) {
            int len = max(len1, len2);
            int start = max(0, R - len + 1);
            int finish = min(L, min(N1, N2) - len + 1);
            for(int j = start; j <= finish; ++j) {
                string S1 = P1.substr(j, len1), S2 = P2.substr(j, len2);
                for(auto &sequence : sequences)
                    if(sequence.contains(S1) && sequence.contains(S2))
                        return false;
            }
        }
    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n; sequences.resize(n);
    for (int i = 0; i < n; i++) {
        int m; cin >> m; while (m--) {
            string s; cin >> s;
            sequences[i].insert(s);
        }
    }

    int p; cin >> p; while(p--){
        string P1, P2; cin >> P1 >> P2; int N = P1.size();
        if(P1 == P2) { cout << "REJECT\n"; continue; }
        cout << (CheckPasswords(P1, P2) ? "OK" : "REJECT") << endl;
    }
}

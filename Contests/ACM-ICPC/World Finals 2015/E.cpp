#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool isSubsequence(const string &t, const string& s){
    int idx = 0;
    for (char c : t){
        if (c == s[idx]){
            idx++;
            if (idx == s.size()){ return true; }
        }
    }
    return false;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
    string target; cin >> target;
    vector<string> words(n); for(auto &x : words){ cin >> x; }
    words.push_back(target); words.push_back(target);
    sort(words.rbegin(), words.rend(), [](string& w1, string& w2){return w1.size() < w2.size();});

    if (words[0] != target || words[1] != target){ cout << "impossible\n"; return 0; }

    bool OK = true;
    vector<vector<int>> parent(words.size() + 1);
    vector<pair<int, int>> candidates;
    candidates.emplace_back(0, 1);
    for(int i = 2; i < words.size(); i++){
        vector<pair<int, int>> newCandidates;
        if (candidates.size() == 1){
            auto& [s1, s2] = candidates[0];
            if (words[s1].size() > words[s2].size()){ swap(s1, s2); }
            if (isSubsequence(words[s2], words[s1])){
                if (isSubsequence(words[s1], words[i])){
                    newCandidates.emplace_back(i, s2);
                    parent[i].push_back(s1);
                }
                else if (isSubsequence(words[s2], words[i])){
                    newCandidates.emplace_back(i, s1);
                    parent[i].push_back(s2);
                }
            }
            else {
                if (isSubsequence(words[s1], words[i])) {
                    newCandidates.emplace_back(i, s2);
                    parent[i].push_back(s1);
                }
                if (isSubsequence(words[s2], words[i])) {
                    newCandidates.emplace_back(i, s1);
                    parent[i].push_back(s2);
                }
            }
        }
        else{
            auto& [s1, s2] = candidates[0];
            auto& [s3, s4] = candidates[1];

            if (isSubsequence(words[s1], words[i])){
                newCandidates.emplace_back(i, s2);
                newCandidates.emplace_back(i, s4);
                parent[i].push_back(s1);
            }
            else{
                if (isSubsequence(words[s2], words[i])){
                    newCandidates.emplace_back(s1, i);
                    parent[i].push_back(s2);
                }
                else if (isSubsequence(words[s4], words[i])){
                    newCandidates.emplace_back(s3, i);
                    parent[i].push_back(s4);
                }
            }
        }

        if (newCandidates.empty()){ OK = false; break; }
        swap(candidates, newCandidates);
    }

    if (!OK){ cout << "impossible\n"; return 0; }

    vector<int> fseq1, fseq2;
    auto getSeq = [&](int start) {
        vector<bool> vis(words.size(), false);
        vector<int> seq1, seq2;
        int cur = words.size() - 1;
        while (cur > 1) {
            vis[cur] = true;
            seq1.push_back(cur);
            if (start){
                if (parent[cur].size() > 1 && !vis[parent[cur][1]]) { cur = parent[cur][1]; }
                else { cur = parent[cur][0]; }
            }
            else {
                if (!vis[parent[cur][0]]) { cur = parent[cur][0]; }
                else if (parent[cur].size() > 1) { cur = parent[cur][1]; }
                else{ return; }
            }
        }

        cur = words.size() - 2;
        while (vis[cur] && cur > 1) { cur--; }
        while (cur > 1) {
            vis[cur] = true;
            seq2.push_back(cur);
            if (!vis[parent[cur][0]]) { cur = parent[cur][0]; }
            else { cur = parent[cur][1]; }
        }
        if (seq1.size() + seq2.size() == n){
            fseq1 = seq1; fseq2 = seq2;
        }
    };

    getSeq(0);
    if (fseq1.size() + fseq2.size() != n){ getSeq(1); }

    cout << fseq1.size() << ' ' << fseq2.size() << '\n';
    for(auto x : fseq1){ cout << words[x] << '\n'; }
    for(auto x : fseq2){ cout << words[x] << '\n'; }
}


#include <bits/stdc++.h>
using namespace std;

struct node {
    int cnt = 0; int wIdx;
    map<char, node*> child;
    node() { }
};

struct Trie {
    node* root;
    Trie() { root = new node(); }

    void addStr(string const& s, int idx) {
        node* cur = root;
        for(auto &c : s){
            if (!cur->child.count(c)){
                cur->child[c] = new node();
            }
            cur = cur->child[c]; cur->cnt++;
            cur->wIdx = idx;
        }
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int n, m; cin >> n >> m;
    vector<string> strings;
    Trie t1, t2;
    for(int i = 0; i < n; i++){
        string s; cin >> s;
        strings.push_back(s);
        t1.addStr(s, i);
        reverse(s.begin(), s.end());
        t2.addStr(s, i);
    }

    while(m--){
        string s; cin >> s;
        if (s.size() < 5){ cout << "none\n"; continue; }

        vector<int> prefCnt(s.size(), 0), sufCnt(s.size(), 0);
        vector<int> prefIdx(s.size(), -1), sufIdx(s.size(), -1);
        node* cur1 = t1.root;

        for(int i = 0; i < s.size(); i++){
            if (!cur1->child.count(s[i])) { break; }
            cur1 = cur1->child[s[i]];
            prefCnt[i] = cur1->cnt;
            prefIdx[i] = cur1->wIdx;
        }

        node* cur2 = t2.root;
        reverse(s.begin(), s.end());
        for(int i = 0; i < s.size(); i++){
            if (!cur2->child.count(s[i])) { break; }
            cur2 = cur2->child[s[i]];
            sufCnt[s.size() - i - 1] = cur2->cnt;
            sufIdx[s.size() - i - 1] = cur2->wIdx;
        }

        int ans = -1; pair<int, int> p;
        for(int i = 2; i < s.size() - 2; i++){
            if (prefCnt[i] == 0){ break; }
            if (sufCnt[i] == 0 && sufCnt[i+1] == 0){ continue; }
            int numComb1 = prefCnt[i] * sufCnt[i];
            int numComb2 = prefCnt[i] * sufCnt[i + 1];
            if (i == s.size() - 3){ numComb2 = 0; }

            if (numComb1 > 1){ ans = 2; break; }
            if (numComb2 > 1){ ans = 2; break; }

            if (numComb1 == 1){
                if (ans == 1){
                    pair<int, int> curP =  {prefIdx[i], sufIdx[i]};
                    if (p != curP) { ans = 2; break; }
                }
                if (ans == -1){
                    ans = 1;
                    p = {prefIdx[i], sufIdx[i]};
                }
            }
            if (numComb2 == 1){
                if (ans == 1){
                    pair<int, int> curP = {prefIdx[i], sufIdx[i+1]};
                    if (p != curP) { ans = 2; break; }
                }
                if (ans == -1){
                    ans = 1;
                    p = {prefIdx[i], sufIdx[i+1]};
                }
            }
        }

        if (ans == -1){ cout << "none\n"; }
        else if (ans == 2){ cout << "ambiguous\n"; }
        else { cout << strings[p.first] << " " << strings[p.second] << '\n'; }
    }
}

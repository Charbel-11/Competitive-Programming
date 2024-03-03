#include <bits/stdc++.h>

using namespace std;

struct node {
    int ID;
    bool isLeaf = false;
    string lang = "";
    string c;
    int left, right;

    node(){}
    node(int _id, bool _isLeaf, string _lang, string _c, int _l, int _r):
            ID(_id), isLeaf(_isLeaf), lang(_lang), c(_c), left(_l), right(_r){}
};

vector<node> nodes;

void dfs(int cur, const set<string>& elements, vector<string>& ans){
    if (nodes[cur].isLeaf){ ans.push_back(nodes[cur].lang); return; }

    dfs(nodes[cur].left, elements, ans);
    if (!elements.count(nodes[cur].c)){
        dfs(nodes[cur].right, elements, ans);
    }
}

vector<string> getLanguages(int root, const set<string>& elements){
    vector<string> ans;

    dfs(root, elements, ans);

    sort(ans.begin(), ans.end());
    return ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int n, p; cin >> n >> p;
    nodes.resize(n);

    vector<node> arbitraryNodes;

    vector<int> cmp;
    for(int i = 0; i < n; i++){
        char type; cin >> type;
        int id; cin >> id; id--;
        cmp.push_back(id);
        if (type == 'I'){
            string c; cin >> c;
            int l, r; cin >> l >> r; l--; r--;
            arbitraryNodes.push_back(node(id, false, "", c, l, r));
        }
        else{
            string lang; cin >> lang;
            arbitraryNodes.push_back(node(id, true, lang, "", -1, -1));
        }
    }

    set<int> notRoot;
    sort(cmp.begin(), cmp.end());
    cmp.erase(unique(cmp.begin(), cmp.end()), cmp.end());
    for(auto &u : arbitraryNodes){
        int betterID = lower_bound(cmp.begin(), cmp.end(), u.ID) - cmp.begin();
        int betterL = lower_bound(cmp.begin(), cmp.end(), u.left) - cmp.begin();
        int betterR = lower_bound(cmp.begin(), cmp.end(), u.right) - cmp.begin();
        u.ID = betterID;
        u.left = betterL;
        u.right = betterR;
        if(!u.isLeaf){ notRoot.insert(u.left); notRoot.insert(u.right); }
        nodes[betterID] = move(u);
    }

    int root = 0;
    while(notRoot.count(root)){ root++; }

    string s; getline(cin,s);
    for(int i = 0; i < p; i++){
        getline(cin,s);
        set<string> elements;
        for(int j = 0; j < s.size(); j++){
            elements.insert(s.substr(j, 1));
        }

        auto ans = getLanguages(root, elements);
        for(auto &x : ans){ cout << x << ' '; }
        cout << '\n';
    }
}
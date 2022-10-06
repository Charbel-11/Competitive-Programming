#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ifstream ifs("in.txt");
    ofstream ofs("out.txt");

    int t; ifs >> t;
    for (int qq = 1; qq <= t; qq++) {
        int r, c; ifs >> r >> c;
        vector<string> initialTreeGrid(r); for(auto &s : initialTreeGrid) { ifs >> s; }
        auto maxTreeGrid = initialTreeGrid;

        queue<pair<int, int>> trees;
        for(int i = 0; i < r; i++){
            for(int j = 0; j < c; j++){
                if (maxTreeGrid[i][j] != '#'){
                    trees.push({i, j});
                    maxTreeGrid[i][j] = '^';
                }
            }
        }

        while(!trees.empty()){
            auto curTree = trees.front(); trees.pop();

            vector<pair<int, int>> adjTrees;
            for(int k = 0; k < 4; k++){
                int adjI = curTree.first + dx[k];
                int adjJ = curTree.second + dy[k];

                if (adjI >= 0 && adjJ >= 0 && adjI < r && adjJ < c){
                    if (maxTreeGrid[adjI][adjJ] == '^'){
                        adjTrees.emplace_back(adjI, adjJ);
                    }
                }
            }

            if (adjTrees.size() < 2){
                maxTreeGrid[curTree.first][curTree.second] = '.';
                for(auto &p : adjTrees){ trees.push(p); }
            }
        }

        bool OK = true;
        for(int i = 0; i < r; i++){
            for(int j = 0; j < c; j++){
                if (initialTreeGrid[i][j] == '^' && maxTreeGrid[i][j] != '^'){
                    OK=false; break;
                }
            }
        }

        if (OK){
            ofs << "Case #" << qq << ": Possible" << '\n';
            for(auto &s : maxTreeGrid){ ofs << s << '\n'; }
        }
        else{
            ofs << "Case #" << qq << ": Impossible" << '\n';
        }
    }
}
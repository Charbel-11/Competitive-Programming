#include <iostream>
#include <tuple>
#include <vector>
#include <string>
using namespace std;
typedef long long ll;

int main() {
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<int> a(n); for (auto& x : a) { cin >> x; }

        vector<vector<int>> ans(n);
        ans[0] = { 1 };

        int curDepth = 0;
        for (int i = 1; i < n; i++) {
            if (a[i] == 1) {
                curDepth++;
                ans[i] = ans[i - 1];
                ans[i].push_back(1);
                continue;
            }

            for (; curDepth >= 0; curDepth--) {
                if (ans[i - 1][curDepth] == a[i] - 1) {
                    ans[i].resize(curDepth + 1);

                    for (int j = 0; j < curDepth; j++) {
                        ans[i][j] = ans[i - 1][j];
                    }
                    ans[i][curDepth] = a[i];

                    break;
                }
            }
        }

        for (auto& v : ans) {
            string s = "";
            for (auto& c : v) { s += to_string(c) + "."; }
            s.pop_back();
            cout << s << '\n';
        }
    }
}
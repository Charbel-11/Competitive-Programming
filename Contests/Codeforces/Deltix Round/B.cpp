#include <iostream>
#include <tuple>
#include <vector>
using namespace std;
typedef long long ll;

int main() {
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<ll> a(n); for (auto& x : a) { cin >> x; }

        vector<tuple<int, int, int>> ans;

        for (int i = 0; i < n; i += 2) {
            ans.push_back({ 1, i + 1, i + 2 });       //a+b, b
            ans.push_back({ 2, i + 1, i + 2 });       //a+b, -a
            ans.push_back({ 1, i + 1, i + 2 });       //b, -a
            ans.push_back({ 1, i + 1, i + 2 });       //-a+b, -a
            ans.push_back({ 2, i + 1, i + 2 });       //-a+b, -b
            ans.push_back({ 1, i + 1, i + 2 });       //-a, -b
        }

        cout << ans.size() << '\n';
        for (auto& t : ans) {
            cout << get<0>(t) << " " << get<1>(t) << " " << get<2>(t) << '\n';
        }
    }
}
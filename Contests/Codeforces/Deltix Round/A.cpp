#include <iostream>

using namespace std;

int main() {
    int t; cin >> t;
    while (t--) {
        int n, m; cin >> n >> m;
        string s; cin >> s;

        bool changed = true;
        while (true) {
            changed = false; m--;
            string curS = s;
            for (int i = 0; i < n; i++) {
                if (s[i] == '1') { continue; }
                if ((i != 0 && s[i - 1] == '1') ^ (i < n && s[i + 1] == '1')) {
                    curS[i] = '1'; changed = true;
                }
            }
            s = curS;
            if (!m || !changed) { break; }
        }

        cout << s << '\n';
    }
}
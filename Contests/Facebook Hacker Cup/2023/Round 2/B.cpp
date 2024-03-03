#include <bits/stdc++.h>
using namespace std;

int n;
bool allChecks(const vector<int>& A, const vector<int>& B){
    for(int i = 0; i < n/2; i++){
        if (A[i] >= B[i]){ return false; }
    }
    for(int i = (n+1)/2; i<n; i++){
        if (A[i] <= B[i]){ return false; }
    }
    for(int i = 0; i < n; i++){
        if (A[i] != B[n-i-1]){ return false; }
    }

    return true;
}

bool tryMoves(int steps, vector<int>& A, vector<int>& B){
    while (steps > n){ swap(A, B); steps -= n;}
    vector<int> nA, nB;
    for (int i = steps; i < n; i++) {
        nA.push_back(A[i]);
        nB.push_back(B[i]);
    }
    for (int i = 0; i < steps; i++) {
        nA.push_back(B[i]);
        nB.push_back(A[i]);
    }
    if (allChecks(nA, nB)) { return true; }
    return false;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ifstream cin("in.txt");
    ofstream cout("out.txt");

    int t; cin >> t;
    for (int qq = 1; qq <= t; qq++) {
        cin >> n;
        vector<int> A(n), B(n);
        for(auto &x : A){ cin >> x; }
        for(auto &x : B){ cin >> x; }

        int ans = -1;
        if (tryMoves(0, A, B)){ ans = 0; }
        else{
            int cntEq = 0, idx = -1;
            for (int i = 0; i < n; i++) {
                if (A[i] == B[i]) {
                    cntEq++;
                    idx = i;
                }
            }
            if (n % 2 == 1){
                if (cntEq == 1) {
                    int neededSteps;
                    if (idx >= n / 2) { neededSteps = idx - n / 2; }
                    else { neededSteps = n / 2 + idx + 1; }

                    if (tryMoves(neededSteps, A, B)) {
                        ans = neededSteps;
                    } else if (tryMoves(n + neededSteps, A, B)) {
                        ans = neededSteps + n;
                    }
                }
            }
            else{
                if (cntEq == 0) {
                    for (int i = 0; i < n - 1; i++) {
                        if (A[i] < B[i] && A[i + 1] > B[i + 1]) {
                            if (i < n / 2 && tryMoves(n + n / 2 + i + 1, A, B)) {
                                ans = n + n / 2 + i + 1;
                            } else if (i >= n / 2 && tryMoves(i - n / 2 + 1, A, B)) {
                                ans = i - n / 2 + 1;
                            }
                            break;
                        }
                        if (A[i] > B[i] && A[i+1] < B[i+1]){
                            if (i < n / 2 && tryMoves(n / 2 + i + 1, A, B)) {
                                ans = n / 2 + i + 1;
                            } else if (i >= n / 2 && tryMoves(n + i - n / 2 + 1, A, B)) {
                                ans = n + i - n / 2 + 1;
                            }
                            break;
                        }
                    }
                    if (tryMoves(n / 2, A, B)) {
                        if (ans == -1) { ans = n / 2; }
                        else { ans = min(ans, n / 2); }
                    }
                    if (tryMoves(n + n / 2, A, B)) {
                        if (ans == -1) { ans = n + n / 2; }
                        else { ans = min(ans, n + n / 2); }
                    }
                }
            }
        }

        cout << "Case #" << qq << ": " << ans << '\n';
    }
}
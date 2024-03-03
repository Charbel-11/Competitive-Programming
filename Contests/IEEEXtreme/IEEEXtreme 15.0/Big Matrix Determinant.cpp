#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;
const double EPS = 1E-9;

int n;
double getDet(vector<vector<double>> a) {
    double det = 1;
    for (int i = 0; i < n; ++i) {
        int k = i;
        for (int j = i + 1; j < n; ++j)
            if (abs(a[j][i]) > abs(a[k][i]))
                k = j;
        if (abs(a[k][i]) < EPS) {
            det = 0;
            break;
        }
        swap(a[i], a[k]);
        if (i != k)
            det = -det;
        det *= a[i][i];
        for (int j = i + 1; j < n; ++j)
            a[i][j] /= a[i][i];
        for (int j = 0; j < n; ++j)
            if (j != i && abs(a[j][i]) > EPS)
                for (int k = i + 1; k < n; ++k)
                    a[j][k] -= a[i][k] * a[j][i];
    }

    return det;
}

vector<int> A;

vector<vector<double>> generateMatrix() {
    vector<vector<double>> a(n, vector<double>(n, 0));
    for (int i = 0; i < n; i++) {
        if (A[i] < n / 2) {
            int done = 0;
            while (done != A[i]) {
                int nxt = rand() % n;
                if (abs(a[i][nxt] - 1) < EPS) { continue; }
                a[i][nxt] = 1; done++;
            }
        }
        else {
            int done = n; 
            for (int j = 0; j < n; j++) { a[i][j] = 1; }
            while (done != A[i]) {
                int nxt = rand() % n;
                if (abs(a[i][nxt]) < EPS) { continue; }
                a[i][nxt] = 0; done--;
            }
        }
    }
    return move(a);
}

int getRandOddNum(int K) {
    int ans = (rand() % K) + 1;
    while(ans % 2 == 0){ ans = (rand() % K) + 1; }
    return ans;
}

int getRandEvenNum(int K) {
    int ans = rand() % K;
    while (ans % 2 == 1) { ans = rand() % K; }
    return ans;
}

vector<vector<double>> generateMatrix2() {
    int K = 3;

    vector<vector<int>> a(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        if (A[i] < n / 2) {
            for (int j = 0; j < n; j++) { a[i][j] = getRandEvenNum(K); }
            int done = 0;
            while (done != A[i]) {
                int nxt = rand() % n;
                if (a[i][nxt] % 2 == 1) { continue; }
                a[i][nxt] = getRandOddNum(K); done++;
            }
        }
        else {
            int done = n;
            for (int j = 0; j < n; j++) { a[i][j] = getRandOddNum(K); }
            while (done != A[i]) {
                int nxt = rand() % n;
                if (a[i][nxt] % 2 == 0) { continue; }
                a[i][nxt] = 0; done--;
            }
        }
    }

    vector<vector<double>> aD(n, vector<double>(n, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            aD[i][j] = (double)a[i][j];
    return move(aD);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

    cin >> n;
    A.resize(n); for (auto& x : A) { cin >> x; }

    vector<vector<double>> ans;
    for (int i = 0; i < 1000; i++) {
        auto cur = generateMatrix();
        if (abs(getDet(cur) - 1) < EPS) { ans = cur; break; }
    }
    
    if (ans.empty()) {
        for (int i = 0; i < 1000; i++) {
            auto cur = generateMatrix2();
            if (abs(getDet(cur) - 1) < EPS) { ans = cur; break; }
        }
    }

    if (ans.empty()) { cout << -1 << '\n'; }
    for (auto& row : ans) {
        for (auto& x : row) { cout << (int)x << ' '; }
        cout << '\n';
    }
}
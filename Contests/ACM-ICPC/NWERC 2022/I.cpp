#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int c, d; cin >> c >> d;
    vector<int> mults1, mults2;
    for(int i = c; i <= d; i++){
        string s; cin >> s;
        if (s == "Fizz" || s == "FizzBuzz"){
            mults1.push_back(i);
        }
        if (s == "Buzz" || s == "FizzBuzz"){
            mults2.push_back(i);
        }
    }

    int a = d + 1, b = d + 1;
    if (!mults1.empty()){
        a = mults1[0];
        for(auto x : mults1){
            a = gcd(a, x);
        }
    }
    if (!mults2.empty()){
        b = mults2[0];
        for(auto x : mults2){
            b = gcd(b, x);
        }
    }

    cout << a << ' ' << b << '\n';
}


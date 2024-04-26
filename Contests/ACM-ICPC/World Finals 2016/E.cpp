#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;

// for n < 2^32: inline ull mul(ull a, ull b, ull mod) { return (a*b) % mod; }
const int _k = 2; const ull _mask = (1<<_k)-1;
ull mul(ull a, ull b, ull mod) { // assumption: b, mod < 2^(64-_k); _k>0
    ull result = 0;
    while (a) {
        ull temp = (b * (a & _mask)) % mod;
        result = (result + temp) % mod;
        a >>= _k;  b = (b << _k) % mod;
    }
    return result;
}
ull power(ull a, ull w, ull mod) {
    ull res = 1;
    while (w){
        if (w&1) { res = mul(res, a, mod); }
        a = mul(a, a, mod); w /= 2;
    }
    return res;
}
bool primetest(ull n, int a) {
    if (a > n-1) { return 1; }
    ull d = n-1; int s = 0;
    while (!(d&1)) { d /= 2; s++; }
    ull x = power(a, d, n);
    if (x == 1 || x == n-1) { return 1; }
    for(int i = 0; i < s - 1; i++){
        x = mul(x, x, n);
        if (x == 1) { return 0; }
        if (x == n-1) { return 1; }
    }
    return 0;
}
bool isPrime(ull n) {
    if (n < 4) { return n > 1; }
    bool pr = n % 2;
    if (n < (1LL << 32)) {
        for (int a : {2,7,61}) { pr = pr && primetest(n,a); }
    }
    else if (n < (1LL << 48)) {
        for (int a : {2,3,5,7,11,13,17}) { pr = pr && primetest(n,a); }
    }
    else {
        for (int a : {2,325,9375,28178,450775,9780504,1795265022}) { pr = pr &&
                                                                          primetest(n,a); }
    }
    return pr;
}
// if needed, the test can be sped up by first checking divisibility by first several primes


ull gcd(ull a, ull b) { return b ? gcd(b, a % b) : a; }

// Pollard-rho factorization, works in O(n^1/4)
// Leaves result in the map fact; before usage, fact.clear()!
vector<ull> fact; // factorization: {<prime, multiplicity>}
ull find_factor(ull z) {
    if (!(z&1)) { return 2; }
    ull c = rand() % z, x = 2, y = 2, d = 1;
    while (d == 1) {
        ull tp = (mul(y,y,z) + c) % z;
        y = (mul(tp,tp,z) + c) % z;
        x = (mul(x,x,z) + c) % z;
        d = gcd(x>y ? x-y : y-x, z);
    }
    return d;
}
void rhofact(ull z) {
    if (z == 1) return;
    if (isPrime(z)) { fact.push_back(z); return; }
    while (1) {
        ull f = find_factor(z);
        if (f != z) { rhofact(f); rhofact(z/f); break; }
    }
}

void GetDivisors(ull x, int i, ull cur, unordered_set<ull>& div, const vector<ull>& pf){
    if(i == pf.size()) {
        if (cur > 10) div.insert(cur);
        return;
    }
    GetDivisors(x, i + 1, cur, div, pf);
    GetDivisors(x, i + 1, cur * pf[i], div, pf);
}

optional<ull> InBaseB(ull x, ull b) {
    ull res = 0, cur = 1; while(x) {
        if(x % b > 9) { return nullopt; }
        res += cur * (x % b); x /= b; cur *= 10;
    }
    return res;
}

int main() {
    ull y, l; cin >> y >> l;
    if(y == 10) { cout << "10\n"; return 0; }

    unordered_set<ull> candidates;
    for(ull x = y; x > y - 10; --x){
        fact.clear(); rhofact(x); ull cur = 1;
        cout << "Done ";
        GetDivisors(y, 0, cur, candidates, fact);
        cout << "Done2\n";
    }

    cout << candidates.size() << endl;
    ull res = 10;
    for(ull b : candidates)
        if(optional<ull> in_base_b = InBaseB(y, b))
            if(*in_base_b >= l) { res = max(res, b); }

    cout << res << '\n';
}
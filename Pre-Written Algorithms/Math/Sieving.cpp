#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int SVSZ = 100009;
typedef int(*func_ptr) (int&, int&, int&);

int spf[SVSZ]; //Smallest Prime Factor
int hpp[SVSZ]; //Highest Power of spf
int hpc[SVSZ]; //Highest Power Count of spf
int func[SVSZ];//Multiplicative Function
vector<int> primes; int ONE = 1;

int identity(int &HPP, int &HPC, int &SPF) { return HPP; }
int divCount(int &HPP, int &HPC, int &SPF) { return HPC + 1; }
int divSum(int &HPP, int &HPC, int &SPF) { return (HPP * SPF - 1) / (SPF - 1); }
int eulerTot(int &HPP, int &HPC, int &SPF) { return HPP - HPP / SPF; }
int mobius(int &HPP, int &HPC, int &SPF) { return (HPC == 0) - (HPC == 1); }

int f(int HPP, int HPC, int SPF) { return 0; } //Modify accordingly

void buildSieveMult(func_ptr Mult) { //Computes a multiplicative function over a range in O(n)
	spf[0] = spf[1] = hpp[1] = func[1] = 1; //Initial Values
	hpp[0] = hpc[0] = hpc[1] = func[0] = 0; //Initial Values

	for (int i = 2; i < SVSZ; i++) {
		if (spf[i] == 0) { //i is Prime
			primes.push_back(i); spf[i] = i;
			func[i] = Mult(i, ONE, i); hpp[i] = i; hpc[i] = 1;
		}
		for (int j = 0; j < (int)primes.size() && i * primes[j] < SVSZ; j++) {
			spf[i * primes[j]] = primes[j];
			if (i % primes[j]) { //primes[j] < spf[i]
				func[i * primes[j]] = func[i] * func[primes[j]];
				hpp[i * primes[j]] = primes[j]; hpc[i*primes[j]] = 1;
			}
			else { //primes[j] == spf[i]
				hpp[i * primes[j]] = primes[j] * hpp[i]; hpc[i * primes[j]] = 1 + hpc[i];
				func[i * primes[j]] = func[i / hpp[i]] * Mult(hpp[i * primes[j]], hpc[i * primes[j]], primes[j]);
				break;
			}
		}
	}
}

//Finds all spf and primes < n in O(n) time
const int SVSZ = 100009;
vector<int> primes; int spf[SVSZ];
void buildSieve() {
	spf[0] = spf[1] = 1;
	for (int i = 2; i < SVSZ; i++) {
		if (spf[i] == 0) { primes.push_back(i);	spf[i] = i; }
		for (int j = 0; j < int(primes.size()) && primes[j] <= spf[i] && i * primes[j] < SVSZ; j++)
			spf[i * primes[j]] = primes[j];
	}
}

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll lcm(ll a, ll b) { return (a / gcd(a, b)) * b; }

//v is the prime factorization of n
ll euler_phi(int n, const vector<pair<int, int>> &v) {
	ll res = n;
	for (auto &x : v) { res -= res / x.first; }
	return res;
}

//Iterates over all divisors; v is the prime factorization of the relevant number
void getDivisorsHelper(int i, int curr, vector<int>& divisors, const vector<pair<int, int>>& v) {
	if (i == (int)v.size()) { divisors.push_back(curr); return; }
	getDivisorsHelper(i + 1, curr, divisors, v);
	for (int j = 0; j < v[i].second; j++) {
		curr *= v[i].first;
		getDivisorsHelper(i + 1, curr, divisors, v);
	}
}

vector<pair<int, int>> getPrimeFactors(int x){
    vector<pair<int, int>> v;
    while (x > 1) {
        int d = spf[x], cnt = 0;
        while (x % d == 0) { x /= d; cnt++; }
        v.push_back({ d, cnt });
    }
    return v;
}
vector<int> getDivisors(int x) {
    vector<int> divisors;
	v = getPrimeFactors(x);
	getDivisorsHelper(0, 1, divisors, v);
	return divisors;
}


//Finds {prime, multiplicity} in O(sqrt(x))
vector<pair<ll, int>> getPrimeFactorsSlow(ll x) {
    vector<pair<ll, int>> ans; ll num = 2;
    while (x != 1 && num*num <= x) {
        if (x % num == 0) {
            int k = 0;
            while (x % num == 0) { x /= num; k++; }
            ans.push_back({ num,k });
        }
        num++;
    }
    if (x != 1) { ans.push_back({ x,1 }); }
    return ans;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

}
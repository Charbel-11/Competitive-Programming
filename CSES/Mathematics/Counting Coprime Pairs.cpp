#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
const int SVSZ = 1000009;
typedef int(*func_ptr) (int&, int&, int&);

int spf[SVSZ]; //Smallest Prime Factor
int hpp[SVSZ]; //Highest Power of spf
int hpc[SVSZ]; //Highest Power Count of spf
int func[SVSZ];//Multiplicative Function
vector<int> primes; int ONE = 1;


int mobius(int& HPP, int& HPC, int& SPF) { return (HPC == 0) - (HPC == 1); }

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
				hpp[i * primes[j]] = primes[j]; hpc[i * primes[j]] = 1;
			}
			else { //primes[j] == spf[i]
				hpp[i * primes[j]] = primes[j] * hpp[i]; hpc[i * primes[j]] = 1 + hpc[i];
				func[i * primes[j]] = func[i / hpp[i]] * Mult(hpp[i * primes[j]], hpc[i * primes[j]], primes[j]);
				break;
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	buildSieveMult(mobius);

	int n; cin >> n;
	vector<int> freq(SVSZ, 0);
	vector<int> x(n); for (auto& xx : x) { cin >> xx; freq[xx]++; }

	ll ans = 0;
	for (int d = 1; d < SVSZ; d++) {
		if (func[d] == 0) { continue; }

		ll numMult = 0;
		for (int d2 = d; d2 < SVSZ; d2 += d) {
			numMult += freq[d2];
		}

		ans += func[d] * numMult * numMult;
	}

	ans -= freq[1] * freq[1];
	ans /= 2;
	ans += freq[1] * (freq[1] - 1) / 2;

	cout << ans << '\n';
}
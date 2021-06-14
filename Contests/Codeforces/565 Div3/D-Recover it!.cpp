#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

//Generate the prime numbers < n
vector<bool> primes;
vector<int> primeIndex;
int c;

void generatePrimes(int n) {
	primes.resize(n, true);
	if (n < 1) { return; }
	primes[0] = false;
	primes[1] = false;

	for (int i = 2; i < n; i++) {
		if (primes[i] == false) {
			continue;
		}

		primeIndex[c] = i;
		c++;

		for (int j = i * 2; j < n; j += i) {
			primes[j] = false;
		}
	}
}


int getBiggestDivisor(int num) {

	for (int i = 2; i <= sqrt(num); i++) {
		if (num%i == 0) {
			return num / i;
		}
	}
}

int main() {
	int n;
	cin >> n;
	primeIndex.resize(200000, 0);
	c = 1;
	generatePrimes(2750132);

	map<int, int> primeInp;
	map<int, int> nonPrimeInp;

	for (int i = 0; i < 2*n; i++) {
		int t;
		cin >> t;
		if (primes[t]) {
			if (primeInp.count(t) == 0) {
				primeInp.insert({ t, 1 });
			}
			else {
				primeInp[t]++;
			}
		}
		else {
			if (nonPrimeInp.count(t) == 0) {
				nonPrimeInp.insert({ t, 1 });
			}
			else {
				nonPrimeInp[t]++;
			}
		}
	}

	vector<int> answ;
	while (!nonPrimeInp.empty()) {
		map<int, int>::iterator itr = prev(nonPrimeInp.end());

		int gDiv = getBiggestDivisor(itr->first);
		map<int, int>::iterator itr2 = nonPrimeInp.find(gDiv);
		if (itr2 != nonPrimeInp.end()) {
			if (itr2->second >= itr->second) {
				itr2->second -= itr->second;
				for (int i = 0; i < itr->second; i++) {
					answ.push_back(itr->first);
				}
				nonPrimeInp.erase(itr);
				if (itr2->second == 0) {
					nonPrimeInp.erase(itr2);
				}
			}
		}
		else {
			map<int, int>::iterator itr2 = primeInp.find(gDiv);
			if (itr2->second >= itr->second) {
				itr2->second -= itr->second;
				for (int i = 0; i < itr->second; i++) {
					answ.push_back(itr->first);
				}
				
				nonPrimeInp.erase(itr);
				if (itr2->second == 0) {
					primeInp.erase(itr2);
				}
			}
		}
	}
	
	while (!primeInp.empty()) {
		map<int, int>::iterator itrP = primeInp.begin();
		map<int, int>::iterator itrP2 = primeInp.find(primeIndex[itrP->first]);

		if (itrP2 != primeInp.end()) {
			answ.push_back(itrP->first);
			if (itrP->second > 1) {
				itrP->second--;
			}
			else {
				primeInp.erase(itrP);
			}
			if (itrP2->second > 1) {
				itrP2->second--;
			}
			else {
				primeInp.erase(itrP2);
			}
		}
	}
	
		for (int i = 0; i < answ.size(); i++) {
			cout << answ[i] << " ";
		}
		cout << endl;
}

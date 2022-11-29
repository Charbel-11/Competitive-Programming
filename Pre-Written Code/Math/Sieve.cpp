#include <bits/stdc++.h>
using namespace std;

//Generate the prime numbers < n
vector<bool> prime;
void generatePrimes(int n) {
	if (n < 1) { return; }
	prime.resize(n, true);
	prime[0] = prime[1] = false;

	for (int i = 2; i < n; i++) {
		if (prime[i] == false) { continue;	}
		for (int j = i * i; j < n; j += i)
			prime[j] = false;
	}
}

//Generate for each number its smallest prime factor
//If primes[i]==i, i is prime
const int SVSZ = 10000001;
int spf[SVSZ];

void buildSieve() {
	vector<int> primes; spf[0] = spf[1] = 1;
	for (int i = 2; i < SVSZ; i++) {
		if (spf[i] == 0) { primes.push_back(i);	spf[i] = i; }
		for (int j = 0; j < int(primes.size()) && primes[j] <= spf[i] && i * primes[j] < SVSZ; j++)
			spf[i * primes[j]] = primes[j];
	}
}

//Call buildSieve() before
//res[i] contains the number of prime factors in i counting duplicates
//It is the sum of the multiplicity of the prime factors basically
//Runs in O(n)
vector<int> powerSum(int n) {
	vector<int> res(n + 1, 0);
	for (int i = 2; i <= n; i++) {
		res[i] = res[i / spf[i]] + 1;
	}
	return move(res);
}

//Gets all the prime factors with multiplicity for all numbers up to n
//O(nlogn) in total for all prime factors/multiplicty
vector<vector<pair<int,int>>> primes;
void primeFactors(int n) {
	if (n < 1) { return; }
	primes.resize(n);
	primes[0].push_back({ 0,1 }); primes[1].push_back({ 1,1 });

	for (int i = 2; i < n; i++) {
		if (primes[i].size() > 0) { continue; }
		primes[i].push_back({ i,1 });
		for (int j = 2 * i; j < n; j += i) {
			int temp = j, k = 0;
			while (temp % i == 0) { temp /= i; k++; }
			primes[j].push_back({ i,k });
		}
	}
}


//Standalone
//We can find the divisors of all numbers up to n with a 2d vector and push_back(j) instead of ++
//Returns the actual number of divisors for each number <= n in O(nlogn)
//This functions converges quickly to 1 or 2 (~6 steps for 1e6)
vector<int> numDivisors(int n) {
	vector<int> res(n + 1, 0);
	for (int i = 1; i <= n; i++)
		for (int j = i; j <= n; j += i)
			res[j]++;

	return res;
}
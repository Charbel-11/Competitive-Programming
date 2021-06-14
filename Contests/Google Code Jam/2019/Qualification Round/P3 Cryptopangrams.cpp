//Find gcd between number > 1; it is a prime  find 26 then sort get a map and find products

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int* prod;
int lim;
int numOfProd;
int primeP[105];
int sortedP[105];

int gcd(int x, int y) {
	if (y == 0) { return x; }

	while (x != y) {
		if (x > y) { x -= y; }
		else { y -= x; }
	}

	return x;
}

void findPrime(int i) {
	if (i == numOfProd - 1) { return; }

	int secPrime = gcd(prod[i], prod[i + 1]);
	primeP[i + 1] = secPrime;

	if (i == 0) {
		primeP[0] = prod[0] / secPrime;
	}
	if (i == numOfProd - 2) {
		primeP[numOfProd] = prod[numOfProd-1] / secPrime;
	}

	findPrime(i + 1);
}

void generateMap() {
	memcpy(sortedP, primeP, numOfProd+1);

	for (int i = 0; i < numOfProd + 1; i++) {
		cout << sortedP[i] << " ";
	}
	cout << endl;
	sort(sortedP, sortedP + numOfProd + 1);

	for (int i = 0; i < numOfProd + 1; i++) {
		cout << sortedP[i] << " ";
	}
}

string decode() {
	return "";
}

int main() {
	int T = 0;
	cin >> T;

	int caseN = 1;
	for (int z = 0; z < T; z++) {
		lim = 0;
		cin >> lim;
		numOfProd = 0;
		cin >> numOfProd;

		prod = new int[numOfProd];
		for (int i = 0; i < numOfProd; i++) {
			cin >> prod[i];
		}

		findPrime(0);
		generateMap();

	//	string res = decode(0);

		cout << "Case #" << caseN << ": "  << endl;
	}
}
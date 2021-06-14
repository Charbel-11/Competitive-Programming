#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//divisors up to 10^6, so num up to 10^12; integers cover 10^10 -> use long long
//for both the number and the divisors
int main() {
	int t;
	cin >> t;

	for (int z = 0; z < t; z++) {
		int n;
		cin >> n;
		vector<long long> divisors;
		long long temp;
		for (int i = 0; i < n; i++) {
			cin >> temp;
			divisors.push_back(temp);
		}
		
		bool possible = true;
		sort(divisors.begin(), divisors.end());

		long long number = divisors[0] * divisors[n - 1];
		int a = 1;
		int b = n - 2;

		while (a <= b) {
			if (number != divisors[a] * divisors[b]) { possible = false; break; }
			a++;
			b--;
		}

		if (!possible) { cout << -1 << endl; continue; }
	
		//No guarantees that the list has ALL the divisors

		double limit = sqrt(number);
		int divNum = 0;
		for (long long i = 2; i <= limit; i++) {		//Even here need long long since i am using i*i==number
			if (i*i == number) { divNum++; break; }
			if (number%i == 0) { divNum += 2; }
		}

		if (divNum == divisors.size()) { cout << number << endl; }
		else { cout << -1 << endl; }
	}
}

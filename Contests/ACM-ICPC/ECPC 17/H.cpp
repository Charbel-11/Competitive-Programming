#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;
typedef long long ll;

int spf[1000009];

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

void buildSieve() {
	vector<int> primes; spf[0] = spf[1] = 1;
	for (int i = 2; i < 1000009; i++) {
		if (spf[i] == 0) { primes.push_back(i);	spf[i] = i; }
		for (int j = 0; j < int(primes.size()) && primes[j] <= spf[i] && i * primes[j] < 1000009; j++)
			spf[i * primes[j]] = primes[j];
	}
}


vector<ll> getDivisors(ll &num) {
	vector<ll> answ;

	for (ll i = 2ll; i*i < num; i++) {
		if (num%i == 0) { answ.push_back(i); }
	}

	return move(answ);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	buildSieve();
	fstream ifs("halfnice.in");

	int T; ifs >> T;

	for (int z = 0; z < T; z++) {
		ll A, B; ifs >> A >> B;
		cout << "Case " << z + 1 << ": ";
	   
		string s = to_string(B);
		string n1 = s.substr(0, s.size() / 2);
		string n2 = s.substr(s.size() / 2, (s.size() + 1) / 2);

		ll curN1 = stoll(n1);
		if (spf[curN1] == curN1) {
			ll tempRight = curN1;
			bool found = false;
			string conc = "";
			ll rightL = stoll(n2);
			while (tempRight <= rightL) {
				string curConc = to_string(tempRight);
				curConc = n1 + curConc;
				ll curB = stoll(curConc);
				if (curB <= B) { conc = curConc; found = true; }
				tempRight += curN1;
			}
			if (found) { cout << conc << endl; continue; }

			
			curN1--;
			if (curN1 < stoll(to_string(A).substr(0, s.size() / 2))) { cout << "impossible" << endl; continue; }
			
			string temp = to_string(curN1);
			s = temp + n2;
			if (n1.size() != temp.size()) {
				n1 = s.substr(0, s.size() / 2);
				n2 = s.substr(s.size() / 2, (s.size() + 1) / 2);
			}
			else { n1 = temp; }

			string temp2 = "";
			for (int i = 0; i < (s.size() + 1) / 2; i++) {
				temp2.push_back('9');
			}
			n2 = temp2; s = temp + temp2;
			B = stoll(s);
		}

		ll finalRight = -1, finalLeft = -1;
		ll curLeft = stoll(n1);
		for (int a = 0; a < 2; a++) {
			vector<ll> divs = getDivisors(curLeft);
			ll right = stoll(n2);
			for (ll &d : divs) {
				ll curRight = (right / d) * d;
				if (curRight <= stoll(n2)) {
					if (curLeft < finalLeft) { continue; }
					if (curLeft == finalLeft && curRight < finalRight) { continue; }
					finalRight = curRight;	finalLeft = curLeft;
				}
			}

			curLeft--;
			string temp = to_string(curLeft);
			s = temp + n2;
			if (n1.size() != temp.size()) {
				n1 = s.substr(0, s.size() / 2);
				n2 = s.substr(s.size() / 2, (s.size() + 1) / 2);
			}
			else { n1 = temp; }

			string temp2 = "";
			for (int i = 0; i < (s.size() + 1) / 2; i++) {
				temp2.push_back('9');
			}
			n2 = temp2; s = temp + temp2;
		}

		if (finalRight == -1) { cout << "impossible" << endl; continue; }
	
		string realRight = "";
		for (int i = 0; i < (s.size() + 1) / 2 - to_string(finalRight).size(); i++) {
			realRight.push_back('0');
		}
		realRight += to_string(finalRight);

		string ttt = to_string(finalLeft) + realRight;
		cout << ttt << endl;
	}
}
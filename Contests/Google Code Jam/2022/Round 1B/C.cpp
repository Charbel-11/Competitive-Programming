#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
using namespace std;
typedef long long ll;

int main() {
	int t; cin >> t;
	for (int qq = 1; qq <= t; qq++) {
		cout << "00000000" << endl;
		int numBits; cin >> numBits;

		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<> dis(0, 7);

		while (numBits) {
			string s(8, '0');

			if (numBits == 8) { s = string(8, '1'); }
			else {
				int curOnes = numBits;
				if (curOnes > 4) { curOnes -= 4; }

				while (curOnes) {
					int randIdx = dis(gen);
					if (s[randIdx] == '1') { continue; }
					s[randIdx] = '1'; curOnes--;
				}
			}

			cout << s << endl;
			cin >> numBits;
			if (numBits == -1) { return 0; }
		}
	}
}

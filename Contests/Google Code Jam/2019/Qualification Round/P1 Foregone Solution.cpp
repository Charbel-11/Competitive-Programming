#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int N4[101];

int* sumWithout4(int N, int digits) {
	int* res = new int[2];

	int toRemove = 0;
	for (int i = 0; i < digits; i++) {
		if (N4[i] == 1) {
			toRemove += pow(10, i);
		}
	}
	res[0] = toRemove;
	res[1] = N - toRemove;

	return res;
}

void resetN4() {
	for (int i = 0; i < 101; i++) {
		N4[i] = 0;
	}
}

int main() {
	int T = 0;
	cin >> T;

	for (int i = 0; i < T; i++) {
		resetN4();
		int N = 0;
		cin >> N;

		int temp = N;
		int counter = 0;
		while (temp >= 1) {
			if (temp % 10 == 4) {
				N4[counter] = 1;
			}
			temp = temp / 10;
			counter++;
		}

		int* res = sumWithout4(N, counter);

		cout << "Case #" << i + 1 << ": " << res[0] << " " << res[1] << endl;
	}
}
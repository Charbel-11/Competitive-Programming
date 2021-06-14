#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>

using namespace std;

double p[302][302][302];	//p[a][b][c] = prob to get to a,b,c
double ev[302][302][302];	//ev[a][b][c] = expected numbers of move to get to a,b,c

int main() {
	int n; cin >> n;
	vector<int> count(4);
	for (int i = 0; i < n; i++) {
		int cur; cin >> cur;
		count[cur]++;
	}

	p[count[1]][count[2]][count[3]] = 1;
	//We start from the end since our start state is with big numbers
	//Better to start with c since c never increases whereas a and b do increase in the next state
	//When eating from a 3-plate or 2-plate
	for (int c = n; c >= 0; c--) {
		for (int b = n; b >= 0; b--) {
			for (int a = n; a >= 0; a--) {
				if (a + b + c > n) { continue; }
				if (a == 0 && b == 0 && c == 0) { continue; }

				double pWaste = (double) (n - (a + b + c)) / n;	
				//eWaste = pWaste + pWaste^2 + ... = 1/(1-pWaste)-1
				double evWaste = 1 / (1 - pWaste) - 1.0;
				ev[a][b][c] += evWaste * p[a][b][c];

				//We get the probabilities assuming we don't waste the move
				//For the ev, we can't say (ev[a][b][c]+1)*curP because it is like saying the weight for an additional
				//move is 1 whereas it is actually p[a][b][c]
				if (a) {
					double curP = (double)a / (a + b + c);
					p[a - 1][b][c] += p[a][b][c] * curP;
					ev[a - 1][b][c] += (ev[a][b][c] + p[a][b][c]) * curP;
				}
				if (b) {
					double curP = (double)b / (a + b + c);
					p[a+1][b-1][c] += p[a][b][c] * curP;
					ev[a + 1][b - 1][c] += (ev[a][b][c] + p[a][b][c]) * curP;
				}
				if (c) {
					double curP = (double)c / (a + b + c);
					p[a][b+1][c-1] += p[a][b][c] * curP;
					ev[a][b+1][c-1] += (ev[a][b][c] + p[a][b][c]) * curP;
				}
			}
		}
	}

	cout << setprecision(9) << fixed << ev[0][0][0] << endl;
}
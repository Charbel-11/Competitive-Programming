#include <iostream>
#include <vector>
using namespace std;

int DP[103][103];
vector<int> T1, T2;
int N1, N2;

//Finds the max height of the twin towers
int findTwin(int i, int j) {
	if (i >= N1 || j >= N2) { return 0; }
	if (DP[i][j] != -1) { return DP[i][j]; }

	if (T1[i] == T2[j]) {
		DP[i][j] = 1 + findTwin(i + 1, j + 1);
		return DP[i][j];
	}

	int a = findTwin(i + 1, j);
	int b = findTwin(i, j + 1);

	DP[i][j] = (a > b) ? a : b;
	return DP[i][j];
}

void resetDP() {
	for (int i = 0; i < 103; i++)
		for (int j = 0; j < 103; j++)
			DP[i][j] = -1;
}

int main() {
	cin >> N1 >> N2;
	int count = 1;

	while (N1 != 0 && N2 != 0) {
		resetDP();
		T1.resize(N1); for (auto &x : T1) { cin >> x; }
		T2.resize(N2); for (auto &x : T2) { cin >> x; }

		cout << "Twin Towers #" << count << endl;
		cout << "Number of Tiles : " << findTwin(0, 0) << endl << endl;

		count++;
		cin >> N1; cin >> N2;
	}
}
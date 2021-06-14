#include <iostream>
#include <string>

using namespace std;

int dimension;
string DP[1005][1005];
int** maze;

void resetMaze() {
	for (int i = 0; i < dimension; i++) {
		for (int j = 0; j < dimension; j++) {
			maze[i][j] = -2;
		}
	}
}

void populateMaze(string& takenPath) {
	int i = 0;
	int j = 0;
	maze[0][0] = 0;
	int counter = 1;
	for (unsigned int c = 0; c < takenPath.length(); c++) {
		if (takenPath[c] == 'S') { i++; }
		else { j++; }

		maze[i][j] = counter;
		counter++;
	}
}

string uniquePath(int i, int j) {
	if (DP[i][j] != "a") {
		return DP[i][j];
	}

	string tryS = "";
	string tryE = "";

	if (i < dimension - 1 && maze[i][j] + 1 != maze[i + 1][j]) {
		tryS += "S" + uniquePath(i + 1, j);
	}
	if (j < dimension - 1 && maze[i][j] + 1 != maze[i][j + 1]) {
		tryE += "E" + uniquePath(i, j + 1);
	}

	DP[i][j] = (tryE.length() > tryS.length()) ? tryE : tryS;
	return DP[i][j];
}

void resetDP(int lim) {
	for (int i = 0; i < lim+1; i++) {
		for (int j = 0; j < lim+1; j++) {
			DP[i][j] = "a";
		}
	}
}

int main() {
	int T = 0;
	cin >> T;

	for (int z = 0; z < T; z++) {
		cin >> dimension;

		resetDP(dimension);

		string takenPath;
		cin >> takenPath;
/*
		maze = new int*[dimension];
		for (int i = 0; i < dimension; i++) {
			maze[i] = new int[dimension];
		}

		resetMaze();
		populateMaze(takenPath);

		string res = uniquePath(0, 0);

		cout << "Case #" << z + 1 << ": " << res << endl;

		for (int i = 0; i < dimension; i++) {
			delete[] maze[i];
		}
		delete[] maze;
	}
	*/

		string res;
		for (int i = 0; i < takenPath.length(); i++) {
			if (takenPath[i] == 'S') {
				res += "E";
			}
			else {
				res += "S";
			}
		}

		cout << "Case #" << z + 1 << ": " << res << endl;
		}
}
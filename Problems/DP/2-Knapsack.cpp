#include <iostream>
using namespace std;

int DP[1000][1000];

//Assumes cap is sorted
int knapsack(int* value, int* cap, int n, int maxCapacity, int start=0){
	if (DP[maxCapacity][start] != -1) { return DP[maxCapacity][start]; }

	if (start == n) { return 0; }

	int a = knapsack(value, cap, n, maxCapacity, start + 1);
	if (maxCapacity < cap[start]) { return a; }
	int b = value[start] + knapsack(value, cap, n, maxCapacity - cap[start], start + 1);
	
	DP[maxCapacity][start] = (a < b) ? b : a;
	return DP[maxCapacity][start];
}

int main() {
	for (int i = 0; i < 1000; i++) {
		for (int j = 0; j < 1000; j++) {
			DP[i][j] = -1;
		}
	}
}
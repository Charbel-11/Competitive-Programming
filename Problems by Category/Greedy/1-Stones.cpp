#include <iostream>
#include <string>
using namespace std;

//Swaps two element in the array
void swap(int* arr, int index1, int index2) {
	int temp = arr[index1];	
	arr[index1] = arr[index2];
	arr[index2] = temp;
}

int minIndex (int* arr, int start, int end){
	int minStoneIndex = start;
	for (int j = start+1; j < end+1; j++) {
		if (arr[minStoneIndex] > arr[j])
			minStoneIndex = j;
	}
	return minStoneIndex;
}

int moveFromTo(int*arr, int from, int to){
	int swaps=0;
	if (to > from){
		while (from != to) { swap(arr, from, from + 1); from++; swaps++; }
	}
	else{
		while (from != to) { swap(arr, from, from - 1); from--; swaps++; }
	}
	return swaps;
}

//Find the minimum height and either put it at the start or at the end
int minSwap(int* arr, int start, int end) {
	if (start >= end) { return 0; }

	int swaps = 0; int minStoneIndex = minIndex(arr, start, end);

	if (end - minStoneIndex < minStoneIndex - start) {
		//Swap the stone to the end
		swaps += moveFromTo(arr, minStoneIndex, end);
		swaps += minSwap(arr, start, end - 1);
	}
	else{
		//Swap the stone to the start
		swaps += moveFromTo(arr, minStoneIndex, start);
		swaps += minSwap(arr, start+1, end);
	}
	return swaps;
}


int main() {
	int testCases;
	cin >> testCases;

	for (int z= 0; z < testCases; z++) {
		int numOfStones;
		cin >> numOfStones;
		
		int* stones = new int[numOfStones];
		for (int j = 0; j < numOfStones; j++) {
			cin >> stones[j];
		}

		cout << minSwap(stones, 0, numOfStones - 1) << endl;
	}
}

//1 2 3 4 8 30 19 18 9 17 16 13 12          13
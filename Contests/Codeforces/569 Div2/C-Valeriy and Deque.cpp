#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

vector<pair<int, int>> answers;	
vector<int> numWithMaxFirst;

pair<int, int> findQuery(int n, long long q) {
	if (q < n) {
		return answers[q];
	}

	int n1 = numWithMaxFirst[0];
	int index = q % (n - 1);
	if (index == 0) {
		index = n - 1;
	}
	int n2 = numWithMaxFirst[index];

	return { n1, n2 };
}

int main() {
	int n, q;
	cin >> n >> q;

	if (q == 0) {
		for (int i = 0; i < n; i++) {
			cin >> q;
		}
		return 0;
	}

	queue<int> numbers;
	for (int i = 0; i < n; i++) {
		int t;
		cin >> t;
		numbers.push(t);			
	}

	answers.push_back({ 0,0 });
	for (int i = 0; i < n-1; i++) {
		int firstNum = numbers.front();
		numbers.pop();
		int secondNum = numbers.front();

		answers.push_back({ firstNum, secondNum });

		if (firstNum > numbers.front()) {
			secondNum = numbers.front();
			numbers.front() = firstNum;
			numbers.push(secondNum);
		}
		else {
			numbers.push(firstNum);			
		}
	}

	for (int i = 0; i < n; i++) {
		numWithMaxFirst.push_back(numbers.front());
		numbers.pop();
	}

	for (int i = 0; i < q; i++) {
		long long t;
		cin >> t;
		pair<int, int> a = findQuery(n, t);
		cout << a.first << " " << a.second << endl;
	}
}
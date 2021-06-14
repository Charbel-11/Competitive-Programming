#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

int main() {
	int n, range;
	cin >> n >> range;

	map<int, int> levels;
	map<int, int> levelsByIndex;
	for (int i = 0; i < n; i++) {
		int temp;
		cin >> temp;
		levels[temp] = i;
		levelsByIndex[i] = temp;
	}

	vector<int> answers(n);
	for (int i = 0; i < n; i++) {
		answers[i] = -1;
	}

	bool first = true;
	while (!levels.empty()) {
		map<int, int>::iterator itr1 = prev(levels.end());				//Gets the last element
		int index = itr1->second;

		answers[index] = first ? 1 : 2;

		map<int, int>::iterator itr2 = levelsByIndex.find(index);

		map<int, int>::iterator pr;
		map<int, int>::iterator nxt;

		int leftDone = 0;
		int rightDone = 0;
		while (itr2 != levelsByIndex.begin() && leftDone != range) {
			pr = prev(itr2);
			answers[pr->first] = first ? 1 : 2;
			leftDone++;

			levels.erase(levels.find(pr->second));
			levelsByIndex.erase(pr);
		}	
		while (itr2 != prev(levelsByIndex.end()) && rightDone != range) {		//end means the one AFTER last, contrary to begin
			nxt = next(itr2);
			answers[nxt->first] = first ? 1 : 2;
			rightDone++;

			levels.erase(levels.find(nxt->second));
			levelsByIndex.erase(nxt);
		}

		first = !first;
		levels.erase(itr1);
		levelsByIndex.erase(itr2);
	}

	for (int i = 0; i < n; i++) {
		cout << answers[i];
	}
	cout << endl;
}
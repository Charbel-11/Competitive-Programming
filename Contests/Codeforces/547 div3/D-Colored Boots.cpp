#include <string>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main() {
	int n;
	cin >> n;

	string l, r;
	cin >> l >> r;

	multimap<char, int> left;
	multimap<char, int> right;

	for (int i = 0; i < n; i++) {
		if (r[i] == '?') {
			right.insert({'z'+1, i + 1 });
		}
		else {
			right.insert({ r[i], i + 1 });
		}

		if (l[i] == '?') {
			left.insert({ 'z'+1, i + 1 });
		}
		else {
			left.insert({ l[i], i + 1 });
		}
	}

	vector< pair<int, int> > answ;

	multimap<char, int>::iterator itrLeft = left.begin();
	multimap<char, int>::iterator tempR;

	while (itrLeft != left.end()) {
		tempR = right.find(itrLeft->first);				//avoid finding the same thing multiple time in a bst

		if (itrLeft->first == '{') {
			answ.push_back({ itrLeft->second, right.begin()->second });
			right.erase(right.begin());
		}
		else if (tempR != right.end()){ 
			answ.push_back({ itrLeft->second, tempR->second });
			right.erase(tempR);
		}
		else{
			tempR = prev(right.end());
			if (tempR->first == '{') {
				answ.push_back({ itrLeft->second, tempR->second });
				right.erase(tempR);
			}
		}

		itrLeft++;
	}

	cout << answ.size() << endl;
	for (int i = 0; i < answ.size(); i++) {
		cout << answ[i].first << " " << answ[i].second << endl;
	}
}
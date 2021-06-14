#include <string>
#include <iostream>
#include <stack>

using namespace std;

int main() {
	int n;
	cin >> n;
	string par;
	cin >> par;

	int color = 0;
	stack<int> S;

	//Just alternating was a risky and incorrect bet  for  (()()())
	for (int i = 0; i < n; i++) {
		if (par[i] == '(') {
			if (S.empty()) {
				cout << color;
				S.push(color);
			}
			else {
				color = (S.top() == 1) ? 0 : 1;	 //S not empty, so we are in nested territory, take the opposite color of the nesting (
				cout << color;					
				S.push(color);
			}
		}
		else {
			cout << S.top();
			S.pop();
		}
	}
	cout << endl;
}
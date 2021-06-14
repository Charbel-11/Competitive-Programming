#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main() {
	int b, n, e; cin >> b >> n >> e;
	int numberOfBoats = (b + n + e) / 2;
	int sb, sn, se; cin >> sb >> sn >> se;

	multimap<int, int> speeds;
	vector<int> capacity(numberOfBoats, 0);
	vector<int> originalSpeed(numberOfBoats, 0);
	for (int i = 0; i < numberOfBoats; i++) {
		int temp; cin >> temp;
		speeds.insert({ temp, i });
		originalSpeed[i] = temp;
	}

	multimap<int, int>::iterator itr = speeds.begin();
	int index = itr->second;
	while (capacity[index] != 2) {
//		cout << itr->second << " " << itr->first << " " << originalSpeed[itr->second] << " " << capacity[itr->second] << endl;

		int curSpeed = itr->first;
		int previousGuy = 0;
		if (capacity[index] == 1) {
			previousGuy = curSpeed / originalSpeed[index];
		}

		if (e){
			speeds.erase(itr);
			speeds.insert({ originalSpeed[index]*(se+previousGuy), index });
			e--;
		}
		else if (n) {
			speeds.erase(itr);
			speeds.insert({ originalSpeed[index] * (sn + previousGuy), index });
			n--;
		}
		else if (b) {
			speeds.erase(itr);
			speeds.insert({ originalSpeed[index] * (sb + previousGuy), index });
			b--;
		}
		else { break; }

		capacity[index]++;
		itr = speeds.begin(); index = itr->second;
	}

	cout << itr->first << endl;
}
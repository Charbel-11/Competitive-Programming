#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <climits>

using namespace std;

int main() {
	int n;
	cin >> n;

	vector<int> a(n);
	multimap<int, int> b;			//Can have multiple keys so multimap

	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	for (int i = 0; i < n; i++) {
		int temp;
		cin >> temp;
		b.insert({ temp, i });
	}

	vector<int> c(n);

	for (int i = 0; i < n; i++) {
		c[i] = INT_MAX;
	}

	multimap<int, int>::iterator low, pr;		//itr = b.lower_bound(10) gives the smallest number>=10; itr->first to use it
												//upper_bound gives the smallest number >10									

	multimap<int, int>::iterator toErase;
	for (int i = 0; i < n; i++) {
		int searchFor = n - a[i];		//I shouldn't take a smaller element since n-a_i + a_i gives 0 mod n
										//but n-a_i+a_i-1 gives n-1 mod n
		int diff = INT_MAX;
		low = b.lower_bound(searchFor);		//smallest >=

		c[i] = (a[i] + b.begin()->first) % n;			//We search for either the closest to 0 or to n-a[i]

		if (low != b.end()) {
			if (c[i] > (a[i] + low->first) % n) {
				c[i] = (a[i] + low->first) % n;
				b.erase(low);
				continue;
			}
		}
		b.erase(b.begin());		//erasing a key removes all these keys in the multimap so better erase an iterator

/*
		for (int z = 0; z < 2; z++) {
			int searchFor = abs(z*n - a[i]);			
			if (z == 0) { searchFor = 0; }				
			//So either bigger or equal to n-a[i] or as small as possible (close to 0)

			int diff = INT_MAX;
			low = b.lower_bound(searchFor);				
		
			if (low != b.end()) { 
				diff = low->first - searchFor; 
			
				int curR = (low->first + a[i]) % n;
				if (curR < c[i]) {
					toErase = low;
					c[i] = curR;
				}
			}
		}
		b.erase(toErase);		
		*/
	}

	for (int i = 0; i < n; i++) {
		cout << c[i] << " ";
	}
	cout << endl;
}	
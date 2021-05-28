/*you have three pegs, A, B and C and n disks on A numbered 1...n
You have to transfer the disks. Eventually all disks on A will be transferred to C
In order for the transfer to take place, at each step you transfer at least one disk from peg A to peg B 
or one disk from peg B to peg C.
You’re not allowed to do backward transfers ie when a disk is in peg B for example it can never go back to A
When you carry out a transfer, you are only allowed to take a disk from the top of the stack and you are only 
allowed to put on the top of another stack.
You're not allowed to take it from the middle of the stack
So the question is how many distinct ways are there to transfer all disks from peg A to peg C*/

#include <iostream>
using namespace std;

int move(int a, int b) {
	if (a == 0)				//No need to check if b==0 since there is only one way to move all disks from b to c
		return 1;

	int movesT = 0;

	movesT += move(a - 1, b + 1);
	if (b > 0)
		movesT += move(a, b - 1);

	return movesT;
}

int main() {
	for (int i = 0; i < 5; i++) {
		cout << i << " disks: " << move(i, 0) << endl;
	}
}
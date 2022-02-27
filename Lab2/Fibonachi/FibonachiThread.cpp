#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

int main() {
	int n1 = 0, n2 = 1, temp;
	cout << n1 << " f" << endl;
	cout << n2 << " f" << endl;
	while (true) {
		temp = n2;
		n2 = n1 + n2;
		n1 = temp;
		cout << n1 << " f" << endl;
		Sleep(200);
	}
	return 0;
}
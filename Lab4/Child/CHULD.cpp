#include <windows.h>
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

int main() {
	cout << "CHILD Input \"A\" or \"B\": " << endl;
	HANDLE Finish = OpenEvent(SYNCHRONIZE, FALSE, FALSE),
		A = OpenEvent(SYNCHRONIZE, FALSE, FALSE),
		B = OpenEvent(SYNCHRONIZE, FALSE, FALSE),
		C = OpenEvent(SYNCHRONIZE, FALSE, FALSE),
		D = OpenEvent(SYNCHRONIZE, FALSE, FALSE);
	int a;
	cin >> a;
	SetEvent(Finish);
}
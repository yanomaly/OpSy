#include <windows.h>
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

int main(int a = 0) {
	cout << "CHILD Input \"A\" or \"B\": " << endl;
	HANDLE Finish = OpenEvent(SYNCHRONIZE, FALSE, FALSE),
		A = OpenEvent(SYNCHRONIZE, FALSE, FALSE),
		B = OpenEvent(SYNCHRONIZE, FALSE, FALSE),
		C = OpenEvent(SYNCHRONIZE, FALSE, FALSE),
		D = OpenEvent(SYNCHRONIZE, FALSE, FALSE);
	SetEvent(Finish);
}
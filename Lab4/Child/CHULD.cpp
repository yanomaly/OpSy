#include <windows.h>
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

int main() {
	cout << "CHILD Input \"A\" or \"B\": " << endl;
	HANDLE Finish = OpenEvent(SYNCHRONIZE, FALSE, (LPWSTR)"Finish"),
		A = OpenEvent(SYNCHRONIZE, FALSE, (LPWSTR)"A"),
		B = OpenEvent(SYNCHRONIZE, FALSE, (LPWSTR)"B"),
		C = OpenEvent(SYNCHRONIZE, FALSE, (LPWSTR)"C"),
		D = OpenEvent(SYNCHRONIZE, FALSE, (LPWSTR)"D");
	int a;
	cin >> a;
	SetEvent(Finish);
}
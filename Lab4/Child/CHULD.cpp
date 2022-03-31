#include <windows.h>
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

int main(int argc, char* argv[]) {
	char* flag = argv[0];
	HANDLE Finish = OpenEvent(SYNCHRONIZE, FALSE, (LPWSTR)flag),
		C = OpenEvent(SYNCHRONIZE, FALSE, (LPWSTR)"C"),
		D = OpenEvent(SYNCHRONIZE, FALSE, (LPWSTR)"D");
	cout << "CHILD" << flag;
	Sleep(1000);
	SetEvent(Finish);
}
#include <windows.h>
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

int main() {
	int msg, msgs;
	cout << "Input number of messages: " << endl;
	/*cin >> msgs;
	int *ms = new int[msgs];*/
	HANDLE Finish = OpenEvent(SYNCHRONIZE, FALSE, (LPCWSTR)"Finish"),
		A = OpenEvent(SYNCHRONIZE, FALSE, (LPWSTR)"A"),
		B = OpenEvent(SYNCHRONIZE, FALSE, (LPWSTR)"B");
	/*for (int i = 0; i < msgs; i++) {
		cout << "Input \"A\" or \"B\": ";
		cin >> ms[i];
	}*/
	int a;
	cin >> a;
	SetEvent(Finish);
}
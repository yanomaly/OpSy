#include <windows.h>
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

int main(int argc, char* argv[]) {
	int msg, msgs;
	char *flag = argv[0];
	cout << "Input number of messages: " << flag << endl;
	cin >> msgs;
	char *ms = new char[msgs];
	HANDLE Finish = OpenEvent(SYNCHRONIZE, FALSE, (LPCWSTR)flag),
		A = OpenEvent(SYNCHRONIZE, FALSE, (LPWSTR)"A"),
		B = OpenEvent(SYNCHRONIZE, FALSE, (LPWSTR)"B");
	/*for (int i = 0; i < msgs; i++) {
		cout << "Input \"A\" or \"B\": ";
		cin >> ms[i];
	}
	for (int i = 0; i < msgs; i++) {
		if (ms[i] == 'A')
			SetEvent(A);
		if (ms[i] == 'B')
			SetEvent(B);
	}*/
	Sleep(1000);
	SetEvent(Finish);
}
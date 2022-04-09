#include <windows.h>
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

int main(int argc, char* argv[]) {
	int msg, msgs = atoi(argv[0]);
	string zero = "0";
	wstring z(zero.begin(), zero.end());
	LPWSTR zer = &z[0];
	string a = "A";
	wstring aa(a.begin(), a.end());
	LPWSTR aaa = &aa[0];
	string b = "B";
	wstring bb(b.begin(), b.end());
	LPWSTR bbb = &bb[0];
	HANDLE Finish = OpenEvent(EVENT_ALL_ACCESS, FALSE, zer),
		A = OpenEvent(EVENT_ALL_ACCESS, FALSE, aaa),
		B = OpenEvent(EVENT_ALL_ACCESS, FALSE, bbb);
	char *ms = new char[msgs];
	for (int i = 0; i < msgs; i++) {
		cout << "Input \"A\" or \"B\": ";
		cin >> ms[i];
	}
	for (int i = 0; i < msgs; i++) {
		if (ms[i] == 'A') {
			cout << "A from parent" << endl;
			SetEvent(A);
		}
		if (ms[i] == 'B') {
			cout << "B from parent" << endl;
			SetEvent(B);
		}
		Sleep(1000);
	}
	SetEvent(Finish);
	cin >> msg;
}
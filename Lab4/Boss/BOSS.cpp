#include <windows.h>
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

int main() {
	int child, msgs;
	cout << "Input number (<= 4) of child proccesses: ";
	cin >> child;
	HANDLE Finish = CreateEvent(NULL, FALSE, FALSE, NULL),
		A = CreateEvent(NULL, FALSE, FALSE, NULL),
		B = CreateEvent(NULL, FALSE, FALSE, NULL),
		C = CreateEvent(NULL, FALSE, FALSE, NULL),
		D = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (child > 4)
		cout << "Wrong number";
	else {
		string p = "PARENT.exe";
		wstring Par(p.begin(), p.end());
		LPWSTR Pr = &Par[0];
		string c = "СHILD.exe";
		wstring Chl(c.begin(), c.end());
		LPWSTR Ch = &Chl[0];
		STARTUPINFO* st = new STARTUPINFO[child + 1];
		PROCESS_INFORMATION* pi = new PROCESS_INFORMATION[child + 1];
		ZeroMemory(&st[0], sizeof(STARTUPINFO));
		st[0].cb = sizeof(STARTUPINFO);
		CreateProcess(NULL, Pr, NULL, NULL, FALSE, NULL, NULL, NULL, &st[0], &pi[0]);
		for (int i = 1; i <= child; i++) {
			PROCESS_INFORMATION piC;
			ZeroMemory(&st[i], sizeof(STARTUPINFO));
			st[i].cb = sizeof(STARTUPINFO);
			CreateProcess(NULL, Ch, NULL, NULL, FALSE, NULL, NULL, NULL, &st[i], &pi[i]);
		}
		WaitForMultipleObjects(1, &Finish, FALSE, INFINITY);
		cout << "BOOOOOOOOOOOOOOOOOOOOOOSSSSSSSSSSSSSSSSSSSSSSSSSSS";
	}
}
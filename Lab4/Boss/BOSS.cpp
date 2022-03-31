#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

int main() {
	int child, msgs;
	cout << "Input number (<= 4) of child proccesses: ";
	cin >> child;
	HANDLE
		A = CreateEvent(NULL, FALSE, FALSE, (LPWSTR)"A"),
		B = CreateEvent(NULL, FALSE, FALSE, (LPWSTR)"B"),
		C = CreateEvent(NULL, FALSE, FALSE, (LPWSTR)"C"),
		D = CreateEvent(NULL, FALSE, FALSE, (LPWSTR)"D");
	if (child > 4)
		cout << "Wrong number";
	else {

		wstring childName(L"D:/Users/famil/source/repos/OpSy/Lab4/x64/Debug/Child.exe");
		LPWSTR chld = &childName[0];

		wstring parentName(L"D:/Users/famil/source/repos/OpSy/Lab4/x64/Debug/Parent.exe");
		LPWSTR prnt = &parentName[0];

		string commandLine = "0";
		wstring cm(commandLine.begin(), commandLine.end());
		LPWSTR comLine = &cm[0];

		HANDLE events[5]{};
		events[0] = CreateEvent(NULL, FALSE, FALSE, (LPWSTR)"0");
		STARTUPINFO* st = new STARTUPINFO[child + 1];
		PROCESS_INFORMATION* pi = new PROCESS_INFORMATION[child + 1];
		ZeroMemory(&st[0], sizeof(STARTUPINFO));
		st[0].cb = sizeof(STARTUPINFO);
		CreateProcess(prnt, (LPWSTR)"0", NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &st[0], &pi[0]);
		for (int i = 1; i <= child; i++) {
			char fl[2];
			_itoa(i, fl, 10);
			commandLine = to_string(i);
			wstring cm(commandLine.begin(), commandLine.end());
			comLine = &cm[0];
			events[i] = CreateEvent(NULL, FALSE, FALSE, (LPWSTR)fl);
			ZeroMemory(&st[i], sizeof(STARTUPINFO));
			st[i].cb = sizeof(STARTUPINFO);
			CreateProcess(chld, comLine, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &st[i], &pi[i]);

		}
		WaitForMultipleObjects(1 + child, events, FALSE, INFINITE);
		cout << "BOOOOOOOOOOOOOOOOOOOOOOSSSSSSSSSSSSSSSSSSSSSSSSSSS";
	}
}
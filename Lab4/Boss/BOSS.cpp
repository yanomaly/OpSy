#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

int main() {
	int child, parent, msgs;
	cout << "Input number (<= 4) of child proccesses: ";
	cin >> child;
	cout << "Input number of parent proccesses: ";
	cin >> parent;
	string a = "A";
	wstring aa(a.begin(), a.end());
	LPWSTR aaa = &aa[0];
	string b = "B";
	wstring bb(b.begin(), b.end());
	LPWSTR bbb = &bb[0];
	string c = "C";
	wstring cc(c.begin(), c.end());
	LPWSTR ccc = &cc[0];
	string d = "D";
	wstring dd(d.begin(), d.end());
	LPWSTR ddd = &dd[0];
	string mes = "Messages";
	wstring ms(mes.begin(), mes.end());
	LPWSTR mss = &ms[0];
	HANDLE
		A = CreateEvent(NULL, FALSE, FALSE, aaa),
		B = CreateEvent(NULL, FALSE, FALSE, bbb),
		C = CreateEvent(NULL, FALSE, FALSE, ccc),
		D = CreateEvent(NULL, FALSE, FALSE, ddd),
		MESSAGES = CreateEvent(NULL, FALSE, FALSE, mss);
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

		HANDLE* events = new HANDLE[child + parent];
		string msgs;
		cout << "Input number of messages: ";
		cin >> msgs;
		HANDLE semaphore = CreateSemaphore(NULL, 5, 5, (LPWSTR)"sem");
		wstring s(msgs.begin(), msgs.end());
		LPWSTR str = &s[0];
		string zero = "0";
		wstring z(zero.begin(), zero.end());
		LPWSTR zer = &z[0];
		events[0] = CreateEvent(NULL, FALSE, FALSE, zer);
		STARTUPINFO* st = new STARTUPINFO[child + parent];
		PROCESS_INFORMATION* pi = new PROCESS_INFORMATION[child + parent];
		for (int i = 0; i < parent; i++) {
			commandLine = to_string(i);
			wstring cm(commandLine.begin(), commandLine.end());
			comLine = &cm[0];
			events[i] = CreateEvent(NULL, FALSE, FALSE, comLine);
			commandLine += " " + msgs;
			wstring cmm(commandLine.begin(), commandLine.end());
			comLine = &cmm[0];
			ZeroMemory(&st[i], sizeof(STARTUPINFO));
			st[i].cb = sizeof(STARTUPINFO);
			CreateProcess(prnt, comLine, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &st[i], &pi[i]);
		}
		for (int i = parent; i < child + parent; i++) {
			commandLine = to_string(i);
			wstring cm(commandLine.begin(), commandLine.end());
			comLine = &cm[0];
			events[i] = CreateEvent(NULL, FALSE, FALSE, comLine);
			commandLine += " " + msgs;
			wstring cmm(commandLine.begin(), commandLine.end());
			comLine = &cmm[0];
			ZeroMemory(&st[i], sizeof(STARTUPINFO));
			st[i].cb = sizeof(STARTUPINFO);
			CreateProcess(chld, comLine, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &st[i], &pi[i]);
		}
		int count = atoi(msgs.c_str()) * parent;
		for (int i = 0; i < count; i++) {
			WaitForSingleObject(sem, INFINITE);
			WaitForSingleObject(semaphore, INFINITE);
			while (true) {
				if (0 == WaitForSingleObject(A, 100)) {
					cout << "BOSS A -> C" << endl;
					SetEvent(C);
					break;
				}
				if (0 == WaitForSingleObject(B, 100)) {
					cout << "CHILD B -> D" << endl;
					SetEvent(D);
					break;
				}
			}
		}
		SetEvent(MESSAGES);
		WaitForMultipleObjects(parent + child, events, TRUE, INFINITE);
	
	}
}
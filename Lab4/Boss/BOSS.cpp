#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <iostream>
#include <string>
#include <ctime>

int main() {
	int child, parent, msgs;
	std::cout << "Input number (<= 4) of child proccesses: ";
	std::cin >> child;
	std::cout << "Input number of parent proccesses: ";
	std::cin >> parent;
	std::string a = "A";
	std::wstring aa(a.begin(), a.end());
	LPWSTR aaa = &aa[0];
	std::string b = "B";
	std::wstring bb(b.begin(), b.end());
	LPWSTR bbb = &bb[0];
	std::string c = "C";
	std::wstring cc(c.begin(), c.end());
	LPWSTR ccc = &cc[0];
	std::string d = "D";
	std::wstring dd(d.begin(), d.end());
	LPWSTR ddd = &dd[0];
	std::string mes = "Messages";
	std::wstring ms(mes.begin(), mes.end());
	LPWSTR mss = &ms[0];
	HANDLE
		A = CreateEvent(NULL, FALSE, FALSE, aaa),
		B = CreateEvent(NULL, FALSE, FALSE, bbb),
		C = CreateEvent(NULL, FALSE, FALSE, ccc),
		D = CreateEvent(NULL, FALSE, FALSE, ddd),
		MESSAGES = CreateEvent(NULL, FALSE, FALSE, mss);
	if (child > 4)
		std::cout << "Wrong number";
	else {

		std::wstring childName(L"D:/Users/famil/source/repos/OpSy/Lab4/x64/Debug/Child.exe");
		LPWSTR chld = &childName[0];

		std::wstring parentName(L"D:/Users/famil/source/repos/OpSy/Lab4/x64/Debug/Parent.exe");
		LPWSTR prnt = &parentName[0];

		std::string commandLine = "0";
		std::wstring cm(commandLine.begin(), commandLine.end());
		LPWSTR comLine = &cm[0];

		HANDLE* events = new HANDLE[child + parent];
		std::string msgs;
		std::cout << "Input number of messages: ";
		std::cin >> msgs;
		HANDLE semaphore = CreateSemaphore(NULL, 5, 5, (LPWSTR)"sem");
		std::wstring s(msgs.begin(), msgs.end());
		LPWSTR str = &s[0];
		std::string zero = "0";
		std::wstring z(zero.begin(), zero.end());
		LPWSTR zer = &z[0];
		events[0] = CreateEvent(NULL, FALSE, FALSE, zer);
		STARTUPINFO* st = new STARTUPINFO[child + parent];
		PROCESS_INFORMATION* pi = new PROCESS_INFORMATION[child + parent];
		for (int i = 0; i < parent; i++) {
			commandLine = std::to_string(i);
			std::wstring cm(commandLine.begin(), commandLine.end());
			comLine = &cm[0];
			events[i] = CreateEvent(NULL, FALSE, FALSE, comLine);
			commandLine += " " + msgs;
			std::wstring cmm(commandLine.begin(), commandLine.end());
			comLine = &cmm[0];
			ZeroMemory(&st[i], sizeof(STARTUPINFO));
			st[i].cb = sizeof(STARTUPINFO);
			CreateProcess(prnt, comLine, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &st[i], &pi[i]);
		}
		for (int i = parent; i < child + parent; i++) {
			commandLine = std::to_string(i);
			std::wstring cm(commandLine.begin(), commandLine.end());
			comLine = &cm[0];
			events[i] = CreateEvent(NULL, FALSE, FALSE, comLine);
			commandLine += " " + msgs;
			std::wstring cmm(commandLine.begin(), commandLine.end());
			comLine = &cmm[0];
			ZeroMemory(&st[i], sizeof(STARTUPINFO));
			st[i].cb = sizeof(STARTUPINFO);
			CreateProcess(chld, comLine, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &st[i], &pi[i]);
		}
		int count = atoi(msgs.c_str()) * parent;
		for (int i = 0; i < count; i++) {
			WaitForSingleObject(semaphore, INFINITE);
			while (true) {
				if (0 == WaitForSingleObject(A, 100)) {
					std::cout << "BOSS A -> C" << std::endl;
					SetEvent(C);
					break;
				}
				if (0 == WaitForSingleObject(B, 100)) {
					std::cout << "CHILD B -> D" << std::endl;
					SetEvent(D);
					break;
				}
			}
		}
		SetEvent(MESSAGES);
		WaitForMultipleObjects(parent + child, events, TRUE, INFINITE);
	
	}
}
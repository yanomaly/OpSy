#include <windows.h>
#include <iostream>
#include <string>
#include <ctime>

int main(int argc, char* argv[]) {
	int msg, msgs = atoi(argv[1]);
	char* flag = argv[0];
	std::string zero = flag;
	std::wstring z(zero.begin(), zero.end());
	LPWSTR zer = &z[0];
	std::string a = "A";
	std::wstring aa(a.begin(), a.end());
	LPWSTR aaa = &aa[0];
	std::string b = "B";
	std::wstring bb(b.begin(), b.end());
	LPWSTR bbb = &bb[0];
	HANDLE Finish = OpenEvent(EVENT_ALL_ACCESS, FALSE, zer),
		A = OpenEvent(EVENT_ALL_ACCESS, FALSE, aaa),
		B = OpenEvent(EVENT_ALL_ACCESS, FALSE, bbb);
	char *ms = new char[msgs];
	for (int i = 0; i < msgs; i++) {
		std::cout << "Input \"A\" or \"B\": ";
		std::cin >> ms[i];
	}
	for (int i = 0; i < msgs; i++) {
		if (ms[i] == 'A') {
			std::cout << "A from parent" << std::endl;
			SetEvent(A);
		}
		if (ms[i] == 'B') {
			std::cout << "B from parent" << std::endl;
			SetEvent(B);
		}
		Sleep(1000);
	}
	SetEvent(Finish);
	std::cin >> msg;
}
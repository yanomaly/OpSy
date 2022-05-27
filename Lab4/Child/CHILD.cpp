#include <windows.h>
#include <iostream>
#include <windows.h>
#include <iostream>
#include <string>
#include <ctime>

int main(int argc, char* argv[]) {
	Sleep(100);
	int msg;
	HANDLE sem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, TRUE, (LPCWSTR)"semaphore");
	HANDLE semaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, TRUE, (LPCWSTR)"såm");
	char* flag = argv[0];
	int ms = atoi(argv[1]);
	std::string zero = flag;
	std::wstring z(zero.begin(), zero.end());
	LPWSTR zer = &z[0];
	std::string c = "C";
	std::wstring cc(c.begin(), c.end());
	LPWSTR ccc = &cc[0];
	std::string d = "D";
	std::wstring dd(d.begin(), d.end());
	LPWSTR ddd = &dd[0];
	std::string mes = "Messages";
	std::wstring s(mes.begin(), mes.end());
	LPWSTR mss = &s[0];
	HANDLE Finish = OpenEvent(EVENT_ALL_ACCESS, FALSE, zer),
		C = OpenEvent(EVENT_ALL_ACCESS, FALSE, ccc),
		D = OpenEvent(EVENT_ALL_ACCESS, FALSE, ddd),
		MESSAGE = OpenEvent(EVENT_ALL_ACCESS, FALSE, ddd);
	while(0 != WaitForSingleObject(MESSAGE, 100)) {
		while (true) {
			if (0 == WaitForSingleObject(C, 100)) {
				std::cout << "CHILD C" << std::endl;
				break;
			}
			if (0 == WaitForSingleObject(D, 100)) {
				std::cout << "CHILD D" << std::endl;
				break;
			}
		}
	}
	SetEvent(Finish);
	ReleaseSemaphore(semaphore, 1, NULL);
	std::cin >> msg;
}
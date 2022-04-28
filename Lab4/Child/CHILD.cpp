#include <windows.h>
#include <iostream>
#include <windows.h>
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

int main(int argc, char* argv[]) {
	Sleep(100);
	int msg;
	HANDLE sem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, TRUE, (LPCWSTR)"semaphore");
	HANDLE semaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, TRUE, (LPCWSTR)"såm");
	char* flag = argv[0];
	int ms = atoi(argv[1]);
	string zero = flag;
	wstring z(zero.begin(), zero.end());
	LPWSTR zer = &z[0];
	string c = "C";
	wstring cc(c.begin(), c.end());
	LPWSTR ccc = &cc[0];
	string d = "D";
	wstring dd(d.begin(), d.end());
	LPWSTR ddd = &dd[0];
	string mes = "Messages";
	wstring s(mes.begin(), mes.end());
	LPWSTR mss = &s[0];
	HANDLE Finish = OpenEvent(EVENT_ALL_ACCESS, FALSE, zer),
		C = OpenEvent(EVENT_ALL_ACCESS, FALSE, ccc),
		D = OpenEvent(EVENT_ALL_ACCESS, FALSE, ddd),
		MESSAGE = OpenEvent(EVENT_ALL_ACCESS, FALSE, ddd);
	while(0 != WaitForSingleObject(MESSAGE, 100)) {
		while (true) {
			if (0 == WaitForSingleObject(C, 100)) {
				cout << "CHILD C" << endl;
				break;
			}
			if (0 == WaitForSingleObject(D, 100)) {
				cout << "CHILD D" << endl;
				break;
			}
		}
	}
	SetEvent(Finish);
	ReleaseSemaphore(semaphore, 1, NULL);
	cin >> msg;
}
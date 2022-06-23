#include <windows.h>
#include <iostream>
#include <string>
#include <ctime>

int main(int argc, char* argv[]) {
	int msg, msgs = atoi(argv[1]);
	HANDLE Finish = OpenEvent(EVENT_ALL_ACCESS, FALSE, argv[0]),
		A = OpenEvent(EVENT_ALL_ACCESS, FALSE, "A"),
		B = OpenEvent(EVENT_ALL_ACCESS, FALSE, "B");
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
	delete[] ms;
}
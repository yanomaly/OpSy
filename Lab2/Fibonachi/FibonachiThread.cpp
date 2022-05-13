#include <iostream>
#include <conio.h>
#include <windows.h>

int main() {
	int n1 = 0, n2 = 1, temp;
	std::cout << n1 << " f" << std::endl;
	std::cout << n2 << " f" << std::endl;
	while (true) {
		temp = n2;
		n2 = n1 + n2;
		n1 = temp;
		std::cout << n1 << " f" << std::endl;
		Sleep(200);
	}
	return 0;
}
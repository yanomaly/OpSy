#include <iostream>
#include <conio.h>
#include <windows.h>

int main() {
	int number1 = 0, number2 = 1, temp;
	std::cout << number1 << " f" << std::endl;
	std::cout << number2 << " f" << std::endl;
	while (true) {
		temp = number2;
		number2 = number1 + number2;
		number1 = temp;
		std::cout << number1 << " f" << std::endl;
		Sleep(200);
	}
	return 0;
}
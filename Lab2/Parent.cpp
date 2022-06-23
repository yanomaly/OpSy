#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>

int main(int argc, char* argv[]) {
	int size, elem, Y;

	std::cout << "Input (in px) Y: ";
	std::cin >> Y;

	std::string commandLine = "";
	STARTUPINFO sti, stiF;
	PROCESS_INFORMATION pi, piF;

	ZeroMemory(&sti, sizeof(STARTUPINFO));
	sti.cb = sizeof(STARTUPINFO);
	ZeroMemory(&stiF, sizeof(STARTUPINFO));
	stiF.cb = sizeof(STARTUPINFO);
	sti.dwFlags = STARTF_USEPOSITION;
	sti.dwY = Y;
	stiF.dwFlags = STARTF_USEPOSITION;
	stiF.dwY = Y + 100;

	std::cout << "Input size of array: " << std::endl;
	std::cin >> size;
	int* array = new int[size];
	std::cout << "Input " << size << " digits: " << std::endl;
	for (int i = 0; i < size; i++)
		std::cin >> array[i];

	std::cout << "Input element: " << std::endl;
	std::cin >> elem;

	commandLine += std::to_string(elem);
	commandLine += " " + std::to_string(size);
	for (int i = 0; i < size; i++)
		commandLine += " " + std::to_string(array[i]);
	CreateProcess("D:/Users/famil/source/repos/OpSy/Lab2/x64/Debug/Fibonachi.exe", NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &stiF, &piF);
	SetPriorityClass(piF.hProcess, HIGH_PRIORITY_CLASS);
	CreateProcess("D:/Users/famil/source/repos/OpSy/Lab2/x64/Debug/ThreadChild.exe", const_cast<char*>(commandLine.c_str()), NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &sti, &pi);
	WaitForSingleObject(pi.hProcess, INFINITE);
	CloseHandle(pi.hThread);
	TerminateProcess(pi.hProcess, 0);
	CloseHandle(piF.hThread);
	TerminateProcess(piF.hProcess, 0);
	ExitProcess(0);
	delete[] array;
	return 0;
}
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
	int size, elem;

	wstring childName(L"C:/Users/famil/source/repos/OpSy/Lab2/x64/Debug/ThreadChild.exe");
	LPWSTR child = &childName[0];

	wstring fibonachiName(L"C:/Users/famil/source/repos/OpSy/Lab2/x64/Debug/Fibonachi.exe");
	LPWSTR fibonachi = &fibonachiName[0];

	string commandLine = "";
	STARTUPINFO sti, stiF;
	PROCESS_INFORMATION pi, piF;

	ZeroMemory(&sti, sizeof(STARTUPINFO));
	sti.cb = sizeof(STARTUPINFO);
	ZeroMemory(&stiF, sizeof(STARTUPINFO));
	stiF.cb = sizeof(STARTUPINFO);

	cout << "Input size of array: " << endl;
	cin >> size;
	int* array = new int[size];
	cout << "Input " << size << " digits: " << endl;
	for (int i = 0; i < size; i++)
		cin >> array[i];

	cout << "Input element: " << endl;
	cin >> elem;

	commandLine += to_string(elem);
	commandLine += " " + to_string(size);
	for (int i = 0; i < size; i++)
		commandLine += " " + to_string(array[i]);
	wstring cm(commandLine.begin(), commandLine.end());
	LPWSTR comLine = &cm[0];
	CreateProcess(fibonachi, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &stiF, &piF);
	
	CreateProcess(child, comLine, NULL, NULL, NULL, NULL, NULL, NULL, &sti, &pi);
		WaitForSingleObject(pi.hProcess,INFINITE);
		CloseHandle(pi.hThread);
		TerminateProcess(pi.hProcess, 0);
		CloseHandle(piF.hThread);
		TerminateProcess(piF.hProcess, 0);
	ExitProcess(0);
	return 0;
}
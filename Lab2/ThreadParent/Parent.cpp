#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
using namespace std;

int main() {
	int size, elem;
	wstring childName(L"ThreadChild.exe");
	LPWSTR child = &childName[0];
	string commandLine = "";
	STARTUPINFO sti;
	PROCESS_INFORMATION pi;
	ZeroMemory(&sti, sizeof(STARTUPINFO));
	sti.cb = sizeof(STARTUPINFO);
	cout << "Input size of array: " << endl;
	cin >> size;
	int* array = new int[size];
	cout << "Input " << size << " digits: " << endl;
	for (int i = 0; i < size; i++)
		cin >> array[i];
	cout << "Input element: " << endl;
	cin >> elem;
	commandLine += elem;
	commandLine += size;
	for (int i = 0; i < size; i++)
		commandLine += array[i];
	if (CreateProcess(NULL, child, NULL, NULL, NULL, NULL, NULL, NULL, &sti, &pi)) {
		WaitForSingleObject(pi.hProcess,INFINITE);
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
	};
	return 0;
}
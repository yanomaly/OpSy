#include <windows.h>
#include <iostream>
#include <string>
using namespace std;


void main()
{
	int size, elem;
	string data;
	cout << "Input size of array: " << endl;
	cin >> size;
	int* array = new int[size];
	cout << "Input " << size << " digits: " << endl;
	for (int i = 0; i < size; i++)
		cin >> array[i];
	cout << "Input element: " << endl;
	cin >> elem;

	HANDLE hNamedPipeRead, hNamedPipeWrite;

	hNamedPipeRead = CreateNamedPipe((LPCWSTR)"\\\\DESKTOP-H2T0TBN\\pipeR\\demo_pipe1", PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE | PIPE_WAIT, 1, 0, 0, INFINITE, (LPSECURITY_ATTRIBUTES)NULL);
	hNamedPipeWrite = CreateNamedPipe((LPCWSTR)"\\\\DESKTOP-H2T0TBN\\pipeW\\demo_pipe2", PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE | PIPE_WAIT, 1, 0, 0, INFINITE, (LPSECURITY_ATTRIBUTES)NULL);
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	wstring smallName(L"D:/Users/famil/source/repos/OpSy/Lab6/x64/Debug/Client.exe");
	LPWSTR smll = &smallName[0];
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	CreateProcess(smll, NULL, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
	cout << "The server is waiting for connection with a client." << endl;
	if (!ConnectNamedPipe(hNamedPipeWrite, (LPOVERLAPPED)NULL))
		cerr << "The connection failed." << endl;
	for (int i = 0; i < size; i++)
	{
		DWORD dwBytesWritten;
		WriteFile(hNamedPipeWrite, &array[i], sizeof(array[i]), &dwBytesWritten, NULL);
		cout << "Writing into pipe... " << array[i] << endl;
	}

	cout << "The server is waiting for connection with a client." << endl;
	if (!ConnectNamedPipe(hNamedPipeRead, (LPOVERLAPPED)NULL))
		cerr << "The connection failed." << endl;

	int resultSize;
	DWORD dwBytesRead1;
	ReadFile(hNamedPipeRead, &resultSize, sizeof(resultSize), &dwBytesRead1, NULL);
	cout << "Reading from pipe... " << resultSize << endl;
	string result = "";
	for (int i = 0; i < size; i++)
	{
		int nData;
		DWORD dwBytesRead;
		ReadFile(hNamedPipeRead, &nData, sizeof(nData), &dwBytesRead, (LPOVERLAPPED)NULL);
		cout << "The number " << nData << " was read by the server" << endl;
		result += to_string(nData) + " ";
		cout << "Reading from pipe... " << nData << endl;
	}
	cout << "Result: " << result;
	CloseHandle(hNamedPipeWrite);
}
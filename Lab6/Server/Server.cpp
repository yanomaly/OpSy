#include <windows.h>
#include <iostream>
#include <string>
using namespace std;

int main()
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
	hNamedPipeWrite = CreateNamedPipe("\\\\.\\pipe\\demo_pipe2", PIPE_ACCESS_OUTBOUND, PIPE_TYPE_MESSAGE | PIPE_WAIT, 1, 0, 0, INFINITE, (LPSECURITY_ATTRIBUTES)NULL);
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	CreateProcess("D:/Users/famil/source/repos/OpSy/Lab6/x64/Debug/Client.exe", NULL, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
	cout << "The server is waiting for connection with a client." << endl;
	if(!ConnectNamedPipe(hNamedPipeWrite, (LPOVERLAPPED)NULL))
		cerr << "The connection failed." << endl;
	DWORD dwBytesWritten = NULL;
	WriteFile(hNamedPipeWrite, &size, sizeof(size), &dwBytesWritten, NULL);
	cout << "Writing into pipe... " << size << endl;
	dwBytesWritten = NULL;
	WriteFile(hNamedPipeWrite, &elem, sizeof(elem), &dwBytesWritten, NULL);
	cout << "Writing into pipe... " << elem << endl;
	for (int i = 0; i < size; i++)
	{
		dwBytesWritten = NULL;
		WriteFile(hNamedPipeWrite, &array[i], sizeof(array[i]), &dwBytesWritten, NULL);
		cout << "Writing into pipe... " << array[i] << endl;
	}

	hNamedPipeRead = CreateNamedPipe("\\\\.\\pipe\\demo_pipe1", PIPE_ACCESS_INBOUND, PIPE_TYPE_MESSAGE | PIPE_WAIT, 1, 0, 0, INFINITE, (LPSECURITY_ATTRIBUTES)NULL);
	cout << "The server is waiting for connection with a client." << endl;
	if(!ConnectNamedPipe(hNamedPipeRead, (LPOVERLAPPED)NULL)) 
		cerr << "The connection failed." << endl;

	int resultSize;
	DWORD dwBytesRead1;
	ReadFile(hNamedPipeRead, &resultSize, sizeof(resultSize), &dwBytesRead1, NULL);
	cout << "Reading from pipe... " << resultSize << endl;
	string result = "";
	for (int i = 0; i < resultSize; i++)
	{
		int nData;
		DWORD dwBytesRead;
		ReadFile(hNamedPipeRead, &nData, sizeof(nData), &dwBytesRead, (LPOVERLAPPED)NULL);
		cout << "The number " << nData << " was read by the server" << endl;
		result += to_string(nData) + " ";
		cout << "Reading from pipe... " << nData << endl;
	}
	cout << "Result " << result;
	return 0;
}

#include <windows.h>
#include <iostream>
#include <string>

int main()
{
	int size, elem;
	std::string data;
	std::cout << "Input size of array: " << std::endl;
	std::cin >> size;
	int* array = new int[size];
	std::cout << "Input " << size << " digits: " << std::endl;
	for (int i = 0; i < size; i++)
		std::cin >> array[i];
	std::cout << "Input element: " << std::endl;
	std::cin >> elem;

	HANDLE hNamedPipeRead, hNamedPipeWrite;
	hNamedPipeWrite = CreateNamedPipe("\\\\.\\pipe\\demo_pipe2", PIPE_ACCESS_OUTBOUND, PIPE_TYPE_MESSAGE | PIPE_WAIT, 1, 0, 0, INFINITE, (LPSECURITY_ATTRIBUTES)NULL);
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	CreateProcess("D:/Users/famil/source/repos/OpSy/Lab6/x64/Debug/Client.exe", NULL, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
	std::cout << "The server is waiting for connection with a client." << std::endl;
	if(!ConnectNamedPipe(hNamedPipeWrite, (LPOVERLAPPED)NULL))
		std::cerr << "The connection failed." << std::endl;
	DWORD dwBytesWritten = NULL;
	WriteFile(hNamedPipeWrite, &size, sizeof(size), &dwBytesWritten, NULL);
	std::cout << "Writing into pipe... " << size << std::endl;
	dwBytesWritten = NULL;
	WriteFile(hNamedPipeWrite, &elem, sizeof(elem), &dwBytesWritten, NULL);
	std::cout << "Writing into pipe... " << elem << std::endl;
	for (int i = 0; i < size; i++)
	{
		dwBytesWritten = NULL;
		WriteFile(hNamedPipeWrite, &array[i], sizeof(array[i]), &dwBytesWritten, NULL);
		std::cout << "Writing into pipe... " << array[i] << std::endl;
	}

	hNamedPipeRead = CreateNamedPipe("\\\\.\\pipe\\demo_pipe1", PIPE_ACCESS_INBOUND, PIPE_TYPE_MESSAGE | PIPE_WAIT, 1, 0, 0, INFINITE, (LPSECURITY_ATTRIBUTES)NULL);
	std::cout << "The server is waiting for connection with a client." << std::endl;
	if(!ConnectNamedPipe(hNamedPipeRead, (LPOVERLAPPED)NULL)) 
		std::cerr << "The connection failed." << std::endl;

	int resultSize;
	DWORD dwBytesRead1;
	ReadFile(hNamedPipeRead, &resultSize, sizeof(resultSize), &dwBytesRead1, NULL);
	std::cout << "Reading from pipe... " << resultSize << std::endl;
	std::string result = "";
	for (int i = 0; i < resultSize; i++)
	{
		int nData;
		DWORD dwBytesRead;
		ReadFile(hNamedPipeRead, &nData, sizeof(nData), &dwBytesRead, (LPOVERLAPPED)NULL);
		std::cout << "The number " << nData << " was read by the server" << std::endl;
		result += std::to_string(nData) + " ";
		std::cout << "Reading from pipe... " << nData << std::endl;
	}
	std::cout << "Result " << result;
	CloseHandle(hNamedPipeRead);
	CloseHandle(hNamedPipeWrite);
	delete[] array;
	return 0;
}

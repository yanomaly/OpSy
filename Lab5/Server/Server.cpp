#include <windows.h>
#include <conio.h>
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

	HANDLE hEnableRead, hEnableRead1;
	std::string lpszEnableRead = "EnableRead";
	std::wstring ler(lpszEnableRead.begin(), lpszEnableRead.end());
	LPWSTR lpszer = &ler[0];
	std::string lpszEnableRead1 = "EnableRead1";
	std::wstring ler1(lpszEnableRead1.begin(), lpszEnableRead1.end());
	LPWSTR lpszer1 = &ler1[0];
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	HANDLE hWritePipe, hReadPipe;
	SECURITY_ATTRIBUTES sa;
	hEnableRead = CreateEvent(NULL, FALSE, FALSE, lpszer);
	hEnableRead1 = CreateEvent(NULL, FALSE, FALSE, lpszer1);
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;
	CreatePipe(&hReadPipe, &hWritePipe, &sa, 0); 
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	std::wstring smallName(L"C:/Users/famil/source/repos/OpSy/Lab5/x64/Debug/Small.exe");
	LPWSTR smll = &smallName[0];
	std::string lpszComLine = std::to_string((int)hWritePipe) + " " + std::to_string((int)hReadPipe);
	std::wstring lc(lpszComLine.begin(), lpszComLine.end());
	LPWSTR comline = &lc[0];
	CreateProcess(smll, comline, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
	DWORD dwBytesWritten1;
	WriteFile(hWritePipe, &size, sizeof(size), &dwBytesWritten1, NULL);
	std::cout << "Writing into pipe... " << size << std::endl;
	DWORD dwBytesWritten2;
	WriteFile(hWritePipe, &elem, sizeof(elem), &dwBytesWritten2, NULL);
	std::cout << "Writing into pipe... " << elem << std::endl;
	for (int i = 0; i < size; i++)
	{
		DWORD dwBytesWritten;
		WriteFile(hWritePipe, &array[i], sizeof(array[i]), &dwBytesWritten, NULL);
		std::cout << "Writing into pipe... " << array[i] << std::endl;
	}
	SetEvent(hEnableRead);
	std::cout << "Waiting to start reading" << std::endl;
	WaitForSingleObject(hEnableRead1, INFINITE);
	int resultSize;
	DWORD dwBytesRead1;
	ReadFile(hReadPipe, &resultSize, sizeof(resultSize), &dwBytesRead1, NULL);
	std::cout << "Reading from pipe... " << resultSize << std::endl;
	std::string result = "";
	for (int i = 0; i < resultSize; i++)
	{
		int nData;
		DWORD dwBytesRead;
		ReadFile(hReadPipe, &nData, sizeof(nData), &dwBytesRead, NULL);
		result += std::to_string(nData) + " ";
		std::cout << "Reading from pipe... " << nData << std::endl;
	}
	std::cout << "Result: " << result;
	CloseHandle(hReadPipe);
	CloseHandle(hWritePipe);
	CloseHandle(hEnableRead);
	CloseHandle(hEnableRead1);
	return 0;
}

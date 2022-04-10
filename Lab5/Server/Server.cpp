#include <windows.h>
#include <conio.h>
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

	HANDLE hEnableRead, hEnableRead1;
	string lpszEnableRead = "EnableRead";
	wstring ler(lpszEnableRead.begin(), lpszEnableRead.end());
	LPWSTR lpszer = &ler[0];
	string lpszEnableRead1 = "EnableRead1";
	wstring ler1(lpszEnableRead1.begin(), lpszEnableRead1.end());
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
	wstring smallName(L"C:/Users/famil/source/repos/OpSy/Lab5/x64/Debug/Small.exe");
	LPWSTR smll = &smallName[0];
	string lpszComLine = to_string((int)hWritePipe) + " " + to_string((int)hReadPipe);
	wstring lc(lpszComLine.begin(), lpszComLine.end());
	LPWSTR comline = &lc[0];
	CreateProcess(smll, comline, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
	DWORD dwBytesWritten1;
	WriteFile(hWritePipe, &size, sizeof(size), &dwBytesWritten1, NULL);
	cout << "Writing into pipe... " << size << endl;
	DWORD dwBytesWritten2;
	WriteFile(hWritePipe, &elem, sizeof(elem), &dwBytesWritten2, NULL);
	cout << "Writing into pipe... " << elem << endl;
	for (int i = 0; i < size; i++)
	{
		DWORD dwBytesWritten;
		WriteFile(hWritePipe, &array[i], sizeof(array[i]), &dwBytesWritten, NULL);
		cout << "Writing into pipe... " << array[i] <<  endl;
	}
	SetEvent(hEnableRead);
	cout << "Waiting to start reading" << endl;
	WaitForSingleObject(hEnableRead1, INFINITE);
	int resultSize;
	DWORD dwBytesRead1;
	ReadFile(hReadPipe, &resultSize, sizeof(resultSize), &dwBytesRead1, NULL);
	cout << "Reading from pipe... " << resultSize << endl;
	string result = "";
	for (int i = 0; i < resultSize; i++)
	{
		int nData;
		DWORD dwBytesRead;
		ReadFile(hReadPipe, &nData, sizeof(nData), &dwBytesRead, NULL);
		result += to_string(nData) + " ";
		cout << "Reading from pipe... " << nData << endl;
	}
	cout << "Result: " << result;
	CloseHandle(hReadPipe);
	CloseHandle(hWritePipe);
	CloseHandle(hEnableRead);
	return 0;
}

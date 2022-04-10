#include <windows.h>
#include <conio.h>
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char* argv[])
{
	HANDLE hWritePipe, hReadPipe;
	HANDLE hEnableRead, hEnableRead1; 
	string lpszEnableRead = "EnableRead";
	wstring ler(lpszEnableRead.begin(), lpszEnableRead.end());
	LPWSTR lpszer = &ler[0];
	string lpszEnableRead1 = "EnableRead1";
	wstring ler1(lpszEnableRead1.begin(), lpszEnableRead1.end());
	LPWSTR lpszer1 = &ler1[0];
	hEnableRead = OpenEvent(EVENT_ALL_ACCESS, FALSE, lpszer);
	hEnableRead1 = OpenEvent(EVENT_ALL_ACCESS, FALSE, lpszer1);
	hWritePipe = (HANDLE)atoi(argv[0]);
	hReadPipe = (HANDLE)atoi(argv[1]);
	cout << "Waiting to start reading" << endl;
	WaitForSingleObject(hEnableRead, INFINITE);
	int size, elem, new_size = 0;
	DWORD dwBytesRead1;
	ReadFile(hReadPipe, &size, sizeof(size), &dwBytesRead1, NULL);
	cout << "Reading from pipe... " << size << endl;
	DWORD dwBytesRead2;
	ReadFile(hReadPipe, &elem, sizeof(elem), &dwBytesRead2, NULL);
	cout << "Reading from pipe... " << elem << endl;
	int* array = new int[size];
	for (int i = 0; i < size; i++)
	{
		DWORD dwBytesRead;
		int nData;
		ReadFile(hReadPipe, &nData, sizeof(nData), &dwBytesRead, NULL);
		cout << "Reading from pipe... " << nData << endl;
		if (nData > 0 && nData < elem) {
			array[new_size] = nData;
			new_size++;
		}
	}
	DWORD dwBytesWritten;
	WriteFile(hWritePipe, &new_size, sizeof(new_size), &dwBytesWritten, NULL);
	cout << "Writing into pipe... " << new_size << endl;
	string result = "";
	for (int i = 0; i < new_size; i++)
	{
		DWORD dwBytesWritten1;
		WriteFile(hWritePipe, &array[i], sizeof(array[i]), &dwBytesWritten1, NULL);
		cout << "Writing into pipe... " << array[i] << endl;
		result += to_string(array[i]) + " ";
	}
	SetEvent(hEnableRead1);
	cout << "Result: " << result;
	cin >> new_size;
	CloseHandle(hWritePipe);
	CloseHandle(hReadPipe);
	CloseHandle(hEnableRead);
	return 0;
}
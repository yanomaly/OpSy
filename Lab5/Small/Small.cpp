#include <windows.h>
#include <conio.h>
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
	HANDLE hWritePipe, hReadPipe;
	HANDLE hEnableRead, hEnableRead1; 
	std::string lpszEnableRead = "EnableRead";
	std::wstring ler(lpszEnableRead.begin(), lpszEnableRead.end());
	LPWSTR lpszer = &ler[0];
	std::string lpszEnableRead1 = "EnableRead1";
	std::wstring ler1(lpszEnableRead1.begin(), lpszEnableRead1.end());
	LPWSTR lpszer1 = &ler1[0];
	hEnableRead = OpenEvent(EVENT_ALL_ACCESS, FALSE, lpszer);
	hEnableRead1 = OpenEvent(EVENT_ALL_ACCESS, FALSE, lpszer1);
	hWritePipe = (HANDLE)atoi(argv[0]);
	hReadPipe = (HANDLE)atoi(argv[1]);
	std::cout << "Waiting to start reading" << std::endl;
	WaitForSingleObject(hEnableRead, INFINITE);
	int size, elem, new_size = 0;
	DWORD dwBytesRead1;
	ReadFile(hReadPipe, &size, sizeof(size), &dwBytesRead1, NULL);
	std::cout << "Reading from pipe... " << size << std::endl;
	DWORD dwBytesRead2;
	ReadFile(hReadPipe, &elem, sizeof(elem), &dwBytesRead2, NULL);
	std::cout << "Reading from pipe... " << elem << std::endl;
	int* array = new int[size];
	for (int i = 0; i < size; i++)
	{
		DWORD dwBytesRead;
		int nData;
		ReadFile(hReadPipe, &nData, sizeof(nData), &dwBytesRead, NULL);
		std::cout << "Reading from pipe... " << nData << std::endl;
		if (nData > 0 && nData < elem) {
			array[new_size] = nData;
			new_size++;
		}
	}
	DWORD dwBytesWritten;
	WriteFile(hWritePipe, &new_size, sizeof(new_size), &dwBytesWritten, NULL);
	std::cout << "Writing into pipe... " << new_size << std::endl;
	std::string result = "";
	for (int i = 0; i < new_size; i++)
	{
		DWORD dwBytesWritten1;
		WriteFile(hWritePipe, &array[i], sizeof(array[i]), &dwBytesWritten1, NULL);
		std::cout << "Writing into pipe... " << array[i] << std::endl;
		result += std::to_string(array[i]) + " ";
	}
	SetEvent(hEnableRead1);
	std::cout << "Result: " << result;
	std::cin >> new_size;
	CloseHandle(hWritePipe);
	CloseHandle(hReadPipe);
	CloseHandle(hEnableRead);
	CloseHandle(hEnableRead1);
	return 0;
}
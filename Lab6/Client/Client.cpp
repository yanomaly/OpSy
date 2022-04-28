#include <windows.h>
#include <iostream>
using namespace std;

void main()
{
	HANDLE hNamedPipeR, hNamedPipeW;
	char pipeNameRead[] = "\\\\DESKTOP-H2T0TBN\\pipeR\\demo_pipe1";
	char pipeNameWrite[] = "\\\\DESKTOP-H2T0TBN\\pipeW\\demo_pipe2";

	hNamedPipeR = CreateFile((LPCWSTR)pipeNameWrite, GENERIC_WRITE, FILE_SHARE_READ, (LPSECURITY_ATTRIBUTES)NULL, OPEN_EXISTING, 0, (HANDLE)NULL);
	int size, elem, new_size = 0;
	DWORD dwBytesRead1;
	ReadFile(hNamedPipeR, &size, sizeof(size), &dwBytesRead1, NULL);
	cout << "Reading from pipe... " << size << endl;
	DWORD dwBytesRead2;
	ReadFile(hNamedPipeR, &elem, sizeof(elem), &dwBytesRead2, NULL);
	cout << "Reading from pipe... " << elem << endl;
	int* array = new int[size];
	for (int i = 0; i < size; i++)
	{
		DWORD dwBytesRead;
		int nData;
		ReadFile(hNamedPipeR, &nData, sizeof(nData), &dwBytesRead, NULL);
		cout << "Reading from pipe... " << nData << endl;
		if (nData > 0 && nData < elem) {
			array[new_size] = nData;
			new_size++;
		}
	}
	hNamedPipeW = CreateFile((LPCWSTR)pipeNameRead, GENERIC_WRITE, FILE_SHARE_READ, (LPSECURITY_ATTRIBUTES)NULL, OPEN_EXISTING, 0, (HANDLE)NULL);

	DWORD dwBytesWritten;
	WriteFile(hNamedPipeW, &new_size, sizeof(new_size), &dwBytesWritten, NULL);
	cout << "Writing into pipe... " << new_size << endl;
	for (int i = 0; i < new_size; i++)
	{
		DWORD dwBytesWritten1;
		WriteFile(hNamedPipeW, &array[i], sizeof(array[i]), &dwBytesWritten1, NULL);
		cout << "Writing into pipe... " << array[i] << endl;
	}
}
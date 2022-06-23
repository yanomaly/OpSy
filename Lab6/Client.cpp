#include <windows.h>
#include <iostream>

int main()
{
	HANDLE hNamedPipeR, hNamedPipeW;

	hNamedPipeR = CreateFile("\\\\.\\pipe\\demo_pipe2", GENERIC_READ, FILE_SHARE_READ, (LPSECURITY_ATTRIBUTES)NULL, OPEN_EXISTING, 0, (HANDLE)NULL);
	int size, elem, new_size = 0;
	DWORD dwBytesRead1;
	ReadFile(hNamedPipeR, &size, sizeof(size), &dwBytesRead1, NULL);
	std::cout << "Reading from pipe... " << size << std::endl;
	DWORD dwBytesRead2;
	ReadFile(hNamedPipeR, &elem, sizeof(elem), &dwBytesRead2, NULL);
	std::cout << "Reading from pipe... " << elem << std::endl;
	int* array = new int[size];
	for (int i = 0; i < size; i++)
	{
		DWORD dwBytesRead;
		int nData;
		ReadFile(hNamedPipeR, &nData, sizeof(nData), &dwBytesRead, NULL);
		std::cout << "Reading from pipe... " << nData << std::endl;
		if (nData > 0 && nData < elem) {
			array[new_size] = nData;
			new_size++;
		}
	}
	Sleep(500);
	hNamedPipeW = CreateFile("\\\\.\\pipe\\demo_pipe1", GENERIC_WRITE, FILE_SHARE_WRITE, (LPSECURITY_ATTRIBUTES)NULL, OPEN_EXISTING, 0, (HANDLE)NULL);

	DWORD dwBytesWritten;
	WriteFile(hNamedPipeW, &new_size, sizeof(new_size), &dwBytesWritten, NULL);
	std::cout << "Writing into pipe... " << new_size << std::endl;
	for (int i = 0; i < new_size; i++)
	{
		DWORD dwBytesWritten1;
		WriteFile(hNamedPipeW, &array[i], sizeof(array[i]), &dwBytesWritten1, NULL);
		std::cout << "Writing into pipe... " << array[i] << std::endl;
	}
	CloseHandle(hNamedPipeR);
	CloseHandle(hNamedPipeW);
	delete[] array;
	return 0;
}
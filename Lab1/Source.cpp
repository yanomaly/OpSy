#include <windows.h>
#include <iostream>
#include <string>
#include <ctime>

struct arrayS {
private:
	int* arr;
	int size;
public:
	arrayS(int size, int* arr) {
		this->size = size;
		this->arr = arr;
	}

	int* getArr() {
		return arr;
	}

	int getSize() {
		return size;
	}
};

DWORD WINAPI Add(LPVOID temp)
{
	std::cout << std::endl << "Thread is started";
	std::string res = std::string("");
	arrayS* tmp = (arrayS*)temp;
	int* arr = tmp->getArr();
	int size = tmp->getSize();
	for (int i = 0; i < size; i++) {
		if (arr[i] < 0 && arr[i] % 6 == 0) {
			res += std::to_string(arr[i]);
			res += '\n';
		}
		Sleep(5);
	}
	if (!res.compare(""))
		std::cout << "No digits" << std::endl;
	else
		std::cout << res;
	std::cout << "Thread is finished" << std::endl;
	return 0;
}

int main()
{
	int size, stopTime;
	std::cout << "Input size of array: ";
	std::cin >> size;
	std::cout << "Input time to stop thread: ";
	std::cin >> stopTime;
	int* arr = new int[size];
	srand(time(NULL));
	for (int i = 0; i < size; i++)
		arr[i] = rand() % 100 * pow(-1, rand() % 2);
	arrayS* temp = new arrayS(size, arr);
	HANDLE worker;
	DWORD IDworker;
	worker = CreateThread(NULL, 0, Add, (void*)temp, 0, &IDworker);
	if (worker == NULL)
		return GetLastError();
	std::cout << "Suspend worker" << std::endl;
	SuspendThread(worker);
	for (int i = 0; i < size; i++)
		std::cout << arr[i] << " ";
	Sleep(stopTime);
	ResumeThread(worker);
	std::cout << std::endl << "Continue worker" << std::endl;
	WaitForSingleObject(worker, INFINITE);
	delete[] arr;
	CloseHandle(worker);
	return 0;
}

#include <windows.h>
#include <iostream>
#include <string>
#include <ctime>

CRITICAL_SECTION cs;
HANDLE countEvent;
volatile int res;
volatile int elem;

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

DWORD WINAPI work(LPVOID temp)
{
	EnterCriticalSection(&cs);
	arrayS* tmp = (arrayS*)temp;
	int* array = tmp->getArr();
	int size = tmp->getSize();
	int* newArray = new int[size];
	int* tempArray = new int[size];
	int sleep, j = 0, k = 0;
	std::cout << "Input sleep time: ";
	std::cin >> sleep;
	std::cout << "Worker enter CS" << std::endl;
	for (int i = 0; i < size; i++) {
		if (array[i] == elem) {
			newArray[j] = elem;
			j++;
		}
		else {
			tempArray[k] = array[i];
			k++;
		}
	}
	for (int i = j, l = 0; l < k; l++, i++)
		newArray[i] = tempArray[l];
	for (int i = 0; i < size; i++) {
		std::cout << newArray[i] << " ";
		Sleep(sleep);
	}
	std::cout << std::endl << "Worker leave CS" << std::endl;
	LeaveCriticalSection(&cs);
	delete[] newArray;
	delete[] tempArray;
	return 0;
}

DWORD WINAPI count(LPVOID temp) {
	
	arrayS* tmp = (arrayS*)temp;
	int count = 0;
	int* array = tmp->getArr();
	int size = tmp->getSize();
	EnterCriticalSection(&cs);
	std::cout << "Count enter CS" << std::endl;
	for (int i = 0; i < size; i++)
		if (array[i] == elem)
			count++;
	res = count;
	std::cout << "Count leave CS" << std::endl;
	LeaveCriticalSection(&cs);
	std::cout << "Count set event" << std::endl;
	SetEvent(countEvent);
	return 0;
}

int main()
{
	int size, tmp;
	std::cout << "Input size of array: ";
	std::cin >> size;
	int* arr = new int[size];
	std::cout << "Input " << size << " digits: ";
	for (int i = 0; i < size; i++)
		std::cin >> arr[i];
	std::cout << "Array: ";
	for (int i = 0; i < size; i++)
		std::cout << arr[i] << " ";
	std::cout << std::endl << "Array size: " << size << std::endl;
	InitializeCriticalSection(&cs);
	countEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	arrayS* temp = new arrayS(size, arr);
	HANDLE worker, counter;
	DWORD IDworker, IDcounter;
	worker = CreateThread(NULL, 0, work, (void*)temp, CREATE_SUSPENDED, &IDworker);
	counter = CreateThread(NULL, 0, count, (void*)temp, CREATE_SUSPENDED, &IDcounter);
	std::cout << "Input element: ";
	std::cin >> tmp;
	elem = tmp;
	ResumeThread(worker);
	ResumeThread(counter);
	WaitForSingleObject(countEvent, INFINITE);
	std::cout << res << " elements equals " << elem << " in array" << std::endl;
	std::cout << "End of main";
	CloseHandle(counter);
	CloseHandle(worker);
	delete[] arr;
	return 0;
}
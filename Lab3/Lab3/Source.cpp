#include <windows.h>
#include <iostream>
#include <string>
#include <ctime>
using namespace std;
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
	arrayS* tmp = (arrayS*)temp;
	int* array = tmp->getArr();
	int size = tmp->getSize();
	int* newArray = new int[size];
	int* tempArray = new int[size];
	int sleep, j = 0, k = 0;
	EnterCriticalSection(&cs);
	cout << "Input sleep time: ";
	cin >> sleep;
	cout << "Worker enter CS" << endl;
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
		cout << newArray[i] << " ";
		Sleep(sleep);
	}
	cout << endl << "Worker leave CS" << endl;
	LeaveCriticalSection(&cs);
	return 0;
}

DWORD WINAPI count(LPVOID temp) {
	EnterCriticalSection(&cs);
	cout << "Count enter CS" << endl;
	arrayS* tmp = (arrayS*)temp;
	int count = 0;
	int* array = tmp->getArr();
	int size = tmp->getSize();
	for (int i = 0; i < size; i++)
		if (array[i] == elem)
			count++;
	res = count;
	cout << "Count leave CS" << endl;
	LeaveCriticalSection(&cs);
	cout << "Count set event" << endl;
	SetEvent(countEvent);
	return 0;
}

int main()
{
	int size, tmp;
	cout << "Input size of array: ";
	cin >> size;
	int* arr = new int[size];
	cout << "Input " << size << " digits: ";
	for (int i = 0; i < size; i++)
		cin >> arr[i];
	cout << "Array: ";
	for (int i = 0; i < size; i++)
		cout << arr[i] << " ";
	cout << endl << "Array size: " << size << endl;
	InitializeCriticalSection(&cs);
	countEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	arrayS* temp = new arrayS(size, arr);
	HANDLE worker, counter;
	DWORD IDworker, IDcounter;
	worker = CreateThread(NULL, 0, work, (void*)temp, CREATE_SUSPENDED, &IDworker);
	counter = CreateThread(NULL, 0, count, (void*)temp, CREATE_SUSPENDED, &IDcounter);
	cout << "Input element: ";
	cin >> tmp;
	elem = tmp;
	ResumeThread(worker);
	Sleep(25);
	ResumeThread(counter);
	WaitForSingleObject(countEvent, INFINITE);
	cout << res << " elements equals " << elem << " in array" << endl;
	cout << "End of main";
	return 0;
}
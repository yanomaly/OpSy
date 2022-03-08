#include <windows.h>
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

struct arrayS {
private:
	int* arr;
	int size;
	int element;
public:
	arrayS(int size, int* arr, int element) {
		this->size = size;
		this->arr = arr;
		this->element = element;
	}

	int* getArr() {
		return arr;
	}

	int getSize() {
		return size;
	}

	int getElement() {
		return element;
	}
};

DWORD WINAPI work(LPVOID temp)
{
	arrayS* tmp = (arrayS*)temp;
	int* array = tmp->getArr();
	int size = tmp->getSize();
	int* newArray = new int[size];
	int* tempArray = new int[size];
	int elem = tmp->getElement();
	int sleep, j = 0, k = 0;
	cout << "Input sleep time: ";
	cin >> sleep;

	for (int i = 0; i < size; i++) {
		if (array[i] == elem) {
			newArray[j] = elem;
			j++;
		}
		else {
			tempArray[k] = array[i];
			k++;
		}
		Sleep(sleep);
	}
	for (int i = j, l = 0; l < k; l++, i++)
		newArray[i] = tempArray[l];
	//
	for (int i = 0; i < size; i++) 
		cout << newArray[i] << " ";
	return 0;
}

DWORD WINAPI count(LPVOID temp) {
	arrayS* tmp = (arrayS*)temp;
	int count = 0;
	int* array = tmp->getArr();
	int size = tmp->getSize();
	int elem = tmp->getElement();
	for (int i = 0; i < size; i++)
		if (array[i] == elem)
			count++;

}

int main()
{
	int size, element;
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

	cout << "Input element: ";
	cin >> element;

	arrayS* temp = new arrayS(size, arr, element);
	HANDLE worker, counter;
	DWORD IDworker, IDcounter;
	worker = CreateThread(NULL, 0, work, (void*)temp, 0, &IDworker);
	counter = CreateThread(NULL, 0, count, (void*)temp, 0, &IDcounter);
	return 0;
}

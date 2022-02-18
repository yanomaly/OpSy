#include <windows.h>
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

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
	cout << endl << "Thread is started";
	string res = string("");
	arrayS* tmp = (arrayS*)temp;
	int* arr = tmp->getArr();
	int size = tmp->getSize();
	for (int i = 0; i < size; i++) {
		if (arr[i] < 0 && arr[i] % 6 == 0) {
			res += to_string(arr[i]);
			res += '\n';
		}
		Sleep(5);
	}
	if (!res.compare(""))
		cout << "No digits" << endl;
	else
		cout << res;
	cout << "Thread is finished" << endl;
	return 0;
}

int main()
{
	int size, stopTime;
	cout << "Input size of array: ";
	cin >> size;
	cout << "Input time to stop thread: ";
	cin >> stopTime;
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
	cout << "Suspend worker" << endl;
	SuspendThread(worker);
	for (int i = 0; i < size; i++)
		cout << arr[i] << " ";
	Sleep(stopTime);
	ResumeThread(worker);
	cout << endl << "Continue worker" << endl;
	WaitForSingleObject(worker, INFINITE);
	CloseHandle(worker);
	return 0;
}

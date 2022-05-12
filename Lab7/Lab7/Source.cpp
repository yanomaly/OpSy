#include <windows.h>
#include <ctime>
#include <stdlib.h>
#include <iostream>
using namespace std;

unsigned int* queue;
HANDLE SemaphoreAdd;
HANDLE SemaphoreRemove;
CRITICAL_SECTION cs;

class MonitorQueue {
private:
	int maxSize, currentSize;
public:
	MonitorQueue(){
		maxSize = 0;
		currentSize = 0;
	}

	MonitorQueue(int nSize) {
		queue = new unsigned int[nSize];
		maxSize = nSize;
		currentSize = 0;
	};

	void AddTail(unsigned int& nElement) {
		WaitForSingleObject(SemaphoreAdd, INFINITE);
		queue[currentSize] = nElement;
		currentSize++;
		ReleaseSemaphore(SemaphoreRemove, 1, NULL);
	};

	unsigned int RemoveHead() {
		WaitForSingleObject(SemaphoreRemove, INFINITE);
		unsigned int elem = queue[0];
		for (int i = 0; i < currentSize - 1; i++)
			queue[i] = queue[i + 1];
		currentSize--;
		ReleaseSemaphore(SemaphoreAdd, 1, NULL);
		return elem;
	};
};

MonitorQueue monitor;

DWORD WINAPI consume(LPVOID count) {
	int cnt = (int)count;
	for (int i = 0; i < cnt; i++) {
		unsigned int obj = monitor.RemoveHead();
		EnterCriticalSection(&cs);
		cout << "Consumed object " << obj << endl;
		LeaveCriticalSection(&cs);
		Sleep(500);
	}
	return 0;
}

DWORD WINAPI produce(LPVOID count) {
	int cnt = (int)count;
	for (int i = 0; i < cnt; i++) { 
		unsigned int obj = (unsigned int)rand() % 100;
		EnterCriticalSection(&cs);
		cout << "Produced object " << obj << endl;
		LeaveCriticalSection(&cs);
		monitor.AddTail(obj);
		Sleep(500);
	}
	return 0;
}

void main() {
	int consumers, producers, size;
	int* consumed;
	int* produced;
	HANDLE* handles;
	DWORD* consumersID;
	DWORD* producersID;
	cout << "Input number of consumers: " << endl;
	cin >> consumers;
	consumed = new int[consumers];
	cout << "Input number of producers: " << endl;
	cin >> producers;
	produced = new int[producers];
	cout << "Input size of queue: " << endl;
	cin >> size;
	monitor = MonitorQueue(size);
	SemaphoreAdd = CreateSemaphore(NULL, size, size, NULL);
	SemaphoreRemove = CreateSemaphore(NULL, 0, size, NULL);
	InitializeCriticalSection(&cs);
	handles = new HANDLE[consumers + producers];
	consumersID = new DWORD[consumers];
	producersID = new DWORD[producers];
	int pos = 0;
	for (int i = 0; i < consumers; i++) {
		cout << "Input number of consumed objects " << endl;
		cin >> consumed[i];
	}
	for (int i = 0; i < producers; i++) {
		cout << "Input number of produced objects " << endl;
		cin >> produced[i];
	}
	srand(time(0));
	for (int i = 0; i < producers; i++, pos++)
		handles[i] = CreateThread(NULL, 0, produce, (int*)produced[i], 0, &producersID[i]);
	for (int i = 0; i < consumers; i++, pos++)
		handles[pos] = CreateThread(NULL, 0, consume, (int*)consumed[i], 0, &consumersID[i]);
	WaitForMultipleObjects(consumers + producers, handles, TRUE, INFINITE);
	cout << "Main finished" << endl;
};
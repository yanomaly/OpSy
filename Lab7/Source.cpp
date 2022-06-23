#include <windows.h>
#include <ctime>
#include <stdlib.h>
#include <iostream>

unsigned int* queue;
HANDLE SemaphoreAdd;
HANDLE SemaphoreRemove;
CRITICAL_SECTION cs, cs1, cs2;

class MonitorQueue {
private:
	int maxSize, currentSize;
public:
	MonitorQueue(){
		maxSize = 0;
		currentSize = 0;
	}

	MonitorQueue(int nSize) {
		maxSize = nSize;
		currentSize = 0;
	};

	int getSize() {
		return this->maxSize;
	}

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
		EnterCriticalSection(&cs1);
		unsigned int obj = monitor.RemoveHead();
		std::cout << "Consumed object " << obj << std::endl;
		LeaveCriticalSection(&cs1);
		Sleep(500);
	}
	return 0;
}

DWORD WINAPI produce(LPVOID count) {
	int cnt = (int)count;
	for (int i = 0; i < cnt; i++) { 
		unsigned int obj = (unsigned int)rand() % 100;
		obj *= (unsigned int)count;
		EnterCriticalSection(&cs2);
		std::cout << "Produced object " << obj << std::endl;
		monitor.AddTail(obj);
		LeaveCriticalSection(&cs2);
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
	std::cout << "Input number of consumers: " << std::endl;
	std::cin >> consumers;
	consumed = new int[consumers];
	std::cout << "Input number of producers: " << std::endl;
	std::cin >> producers;
	produced = new int[producers];
	std::cout << "Input size of queue: " << std::endl;
	std::cin >> size;
	queue = new unsigned int[size];
	monitor = MonitorQueue(size);
	SemaphoreAdd = CreateSemaphore(NULL, size, size, NULL);
	SemaphoreRemove = CreateSemaphore(NULL, 0, size, NULL);
	InitializeCriticalSection(&cs);
	InitializeCriticalSection(&cs1);
	InitializeCriticalSection(&cs2);
	handles = new HANDLE[consumers + producers];
	consumersID = new DWORD[consumers];
	producersID = new DWORD[producers];
	int pos = 0;
	for (int i = 0; i < consumers; i++) {
		std::cout << "Input number of consumed objects " << std::endl;
		std::cin >> consumed[i];
	}
	for (int i = 0; i < producers; i++) {
		std::cout << "Input number of produced objects " << std::endl;
		std::cin >> produced[i];
	}
	srand(time(0));
	for (int i = 0; i < producers; i++, pos++)
		handles[i] = CreateThread(NULL, 0, produce, (int*)produced[i], 0, &producersID[i]);
	for (int i = 0; i < consumers; i++, pos++)
		handles[pos] = CreateThread(NULL, 0, consume, (int*)consumed[i], 0, &consumersID[i]);
	WaitForMultipleObjects(consumers + producers, handles, TRUE, INFINITE);
	std::cout << "Main finished" << std::endl;
	delete[] consumed;
	delete[] produced;
	delete[] handles;
	delete[] consumersID;
	delete[] producersID;
	CloseHandle(SemaphoreAdd);
	CloseHandle(SemaphoreRemove);
};
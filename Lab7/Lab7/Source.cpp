#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

volatile unsigned int* queue;
volatile MonitorQueue monitor;

class MonitorQueue{
private:
	int maxSize, currentSize;
public:
	MonitorQueue(int nSize) {
		queue = new unsigned int[nSize];
		maxSize = nSize;
		currentSize = 0;
	}; 

	~MonitorQueue() {
		delete queue;
	};

	void AddTail(unsigned int& nElement) {
		if (currentSize < maxSize) {
			queue[currentSize] = nElement;
			currentSize++;
		}
		else {
			cout << 0; //тут
		}
	};
	
	unsigned int RemoveHead() {
		if (currentSize > 0) {
			currentSize--;
			return queue[currentSize];
		}
		else {
			return 0; //тут
		}
	}; 
};

DWORD WINAPI consume(LPVOID count) {
	int cnt = (int)count;
	for (int i = 0; i < cnt; i++) 
		cout << "Consumed object " << monitor->RemoveHead() << endl;
}

DWORD WINAPI produce(LPVOID count) {
	srand(time(NULL));
	int cnt = (int)count;
	for (int i = 0; i < cnt; i++) { 
		unsigned int obj = (unsigned int)rand();
		monitor->AddTail(obj);
		cout << "Produced object: " << obj << endl;
	}
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
	monitor = new MonitorQueue(size);
	handles = new HANDLE[consumers + producers];
	consumersID = new DWORD[consumers];
	producersID = new DWORD[producers];
	int pos;
	for (int i = 0; i < consumers; i++) {
		cout << "Input number of consumed objects " << endl;
		cin >> consumed[i];
		handles[i] = CreateThread(NULL, 0, consume, (int*)consumed[i], 0, &consumersID[i]);
		pos = i;
	}
	for (int i = 0; i < producers; i++) {
		cout << "Input number of produced objects " << endl;
		cin >> produced[i];
		handles[pos] = CreateThread(NULL, 0, produce, (int*)produced[i], 0, &producersID[i]);
		pos++;
	}
	WaitForMultipleObjects(consumers + producers, handles, TRUE, INFINITE);
};
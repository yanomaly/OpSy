#include <windows.h>
#include <iostream>
#include <string>
#include <ctime>
#include <chrono>
#include <thread>

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

void add(arrayS* tmp, int sleep)
{
	std::cout << std::endl << "Thread is started" << std::endl;
	std::string res = std::string("");
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
	std::chrono::milliseconds timespan(sleep);
	std::this_thread::sleep_for(timespan);
	std::cout << "Thread is finished" << std::endl;
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
	std::thread t1(add, temp, stopTime);
	t1.join();
	for (int i = 0; i < size; i++)
		std::cout << arr[i] << " ";
	return 0;
}

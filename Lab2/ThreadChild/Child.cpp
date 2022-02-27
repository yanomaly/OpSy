#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

int main(int argc, char* argv[]) {
		int size = atoi(argv[1]), elem = atoi(argv[0]), j = 0, k = 0;
		int* array = new int[size];
		int* newArray = new int[size];
		int* tempArray = new int[size];
		for (int i = 0; i < size; i++)
			array[i] = atoi(argv[2 + i]);
		for (int i = 0; i < size; i++)
			if (array[i] == elem) {
				newArray[j] = elem;
				j++;
			}
			else {
				tempArray[k] = array[i];
				k++;
			}
		for (int i = j, l = 0; l < k; l++, i++)
			newArray[i] = tempArray[l];
		for (int i = 0; i < size; i++)
			cout << newArray[i] << " ";
		Sleep(5000);
	return 0;
}
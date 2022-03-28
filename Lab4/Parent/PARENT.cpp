#include <windows.h>
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

int main() {
	int msg, msgs;
	cout << "Input number of messages: " << endl;
	/*cin >> msgs;
	int *ms = new int[msgs];*/
	HANDLE Finish = OpenEvent(SYNCHRONIZE, FALSE, FALSE),
		A = OpenEvent(SYNCHRONIZE, FALSE, FALSE),
		B = OpenEvent(SYNCHRONIZE, FALSE, FALSE);
	/*for (int i = 0; i < msgs; i++) {
		cout << "Input \"A\" or \"B\": ";
		cin >> ms[i];
	}*/
	int a;
	cin >> a;
	SetEvent(Finish);
}
#include "windows.h"
#include "iostream"
#include "string"

using namespace std;

HANDLE table;
HANDLE* phylosophers;
DWORD* phylosophersID;
CRITICAL_SECTION cs;

class Phylosopher {
private:
    bool hungry = true;
    string name;
public:
    Phylosopher(string name, bool hungry) {
        this->name = name;
        this->hungry = hungry;
    }

    bool getHungry() {
        return this->hungry;
    }

    string getName() {
        return this->name;
    }
};

DWORD WINAPI eat(LPVOID arg){
    Phylosopher* phylo = (Phylosopher*)arg;
    if (phylo->getHungry()) {
        EnterCriticalSection(&cs);
        cout << "Phylosopher " << phylo->getName() << " is thinking..." << endl;
        LeaveCriticalSection(&cs);
        WaitForSingleObject(table, INFINITE);
        EnterCriticalSection(&cs);
        cout << "Phylosopher " << phylo->getName() << " is eating..." << endl;
        LeaveCriticalSection(&cs);
        Sleep(500);
        EnterCriticalSection(&cs);
        cout << "Phylosopher " << phylo->getName() << " leaves table..." << endl;
        LeaveCriticalSection(&cs);
        ReleaseSemaphore(table, 1, NULL);
    }
    else {
        cout << "Phylosopher " << phylo->getName() << " not hungry..." << endl;
    }
    return 0;
}

void main(){
    int count;
    cout << "Input number of phylosophers: \n";
    cin >> count;
    table = CreateSemaphore(NULL, count / 2, count / 2, NULL);
    phylosophers = new HANDLE[count];
    phylosophersID = new DWORD[count];
    InitializeCriticalSection(&cs);
    for (int i = 0; i < count; i++)
        phylosophers[i] = CreateThread(NULL, 0, eat, (Phylosopher*)new Phylosopher(to_string(i), true), 0, &phylosophersID[i]);
    WaitForMultipleObjects(count, phylosophers, TRUE, INFINITE);
}
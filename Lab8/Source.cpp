#include "windows.h"
#include "iostream"
#include "string"

HANDLE table;
HANDLE* phylosophers;
DWORD* phylosophersID;
CRITICAL_SECTION cs;

class Phylosopher {
private:
    bool hungry = true;
    std::string name;
public:
    Phylosopher(std::string name, bool hungry) {
        this->name = name;
        this->hungry = hungry;
    }

    bool getHungry() {
        return this->hungry;
    }

    std::string getName() {
        return this->name;
    }
};

DWORD WINAPI eat(LPVOID arg){
    Phylosopher* phylo = (Phylosopher*)arg;
    if (phylo->getHungry()) {
        EnterCriticalSection(&cs);
        std::cout << "Phylosopher " << phylo->getName() << " is thinking..." << std::endl;
        LeaveCriticalSection(&cs);
        WaitForSingleObject(table, INFINITE);
        EnterCriticalSection(&cs);
        std::cout << "Phylosopher " << phylo->getName() << " is eating..." << std::endl;
        LeaveCriticalSection(&cs);
        Sleep(500);
        EnterCriticalSection(&cs);
        std::cout << "Phylosopher " << phylo->getName() << " leaves table..." << std::endl;
        LeaveCriticalSection(&cs);
        ReleaseSemaphore(table, 1, NULL);
    }
    else {
        std::cout << "Phylosopher " << phylo->getName() << " not hungry..." << std::endl;
    }
    return 0;
}

void main(){
    int count;
    std::cout << "Input number of phylosophers: \n";
    std::cin >> count;
    table = CreateSemaphore(NULL, count / 2, count / 2, NULL);
    phylosophers = new HANDLE[count];
    phylosophersID = new DWORD[count];
    InitializeCriticalSection(&cs);
    for (int i = 0; i < count; i++)
        phylosophers[i] = CreateThread(NULL, 0, eat, (Phylosopher*)new Phylosopher(std::to_string(i), true), 0, &phylosophersID[i]);
    WaitForMultipleObjects(count, phylosophers, TRUE, INFINITE);
    CloseHandle(table);
    delete[] phylosophers;
    delete[] phylosophersID;
}
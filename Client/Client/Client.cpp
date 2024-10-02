#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

int main(int argc, char* argv[])
{
    int arraySize = atoi(argv[1]);
    HANDLE hWp = (HANDLE)atoi(argv[2]);

    double* array = new double[arraySize];
    srand((unsigned)time(NULL));

    for (int i = 0; i < arraySize; i++)
    {
        array[i] = (double)(rand() % 101);
        string number = to_string(array[i]) + " ";
        DWORD written;
        WriteFile(hWp, number.c_str(), number.size(), &written, NULL);
    }

    CloseHandle(hWp);

    cout << "Array: ";
    for (int i = 0; i < arraySize; i++)
    {
        cout << array[i] << " ";
    }

    cout << "\nPress any key to continue...";
    cin.get();

    return 0;
}
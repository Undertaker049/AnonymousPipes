#include <iostream>
#include <Windows.h>
#include <string>
#include <sstream>
using namespace std;

int main(int argc, char* argv[])
{
    HANDLE hRp = (HANDLE)atoi(argv[1]);
    HANDLE hWp = (HANDLE)atoi(argv[2]);

    char buffer[256];
    DWORD read, written;
    string rArray;

    while (ReadFile(hRp, buffer, sizeof(buffer) - 1, &read, NULL) && read > 0)
    {
        buffer[read] = '\0';
        cout << "Received Array: " << buffer << endl;
        rArray += buffer;
    }

    double N, M;
    cout << "Enter N: ";
    cin >> N;
    cout << "Enter M: ";
    cin >> M;

    stringstream ss(rArray);
    double num;
    cout << endl;

    while (ss >> num)
    {
        if (num >= N && num <= M)
        {
            string number = to_string(num) + " ";
            cout << number << endl;
            WriteFile(hWp, number.c_str(), number.size(), &written, NULL);
        }
    }

    cout << "\nPress any key to continue...";
    cin.ignore();
    cin.get();

    return 0;
}
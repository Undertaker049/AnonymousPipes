#include <iostream>
#include <Windows.h>
#include <string>
using namespace std;

int main()
{
    STARTUPINFO siClient, siPart;
    PROCESS_INFORMATION piClient, piPart;
    SECURITY_ATTRIBUTES sa;
    HANDLE hWpClient, hRpClient, hWpPart, hRpPart;
    HANDLE mutex;
    wchar_t comlineClient[256], comlinePart[256];
    int arraySize;

    cout << "Enter array size: ";
    cin >> arraySize;

    sa.lpSecurityDescriptor = NULL;
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.bInheritHandle = TRUE;

    CreatePipe(&hRpClient, &hWpClient, &sa, 0);
    CreatePipe(&hRpPart, &hWpPart, &sa, 0);

    mutex = CreateMutex(NULL, FALSE, NULL);
    ZeroMemory(&siClient, sizeof(STARTUPINFO));
    siClient.cb = sizeof(STARTUPINFO);
    siClient.dwFlags = STARTF_USESTDHANDLES;
    siClient.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    siClient.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    siClient.hStdError = GetStdHandle(STD_ERROR_HANDLE);

    wsprintf(comlineClient, L"C:\\Client\\x64\\Debug\\Client.exe %d %d", arraySize, (int)hWpClient);

    if (!CreateProcess(NULL, comlineClient, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &siClient, &piClient))
    {
        cout << "Failed to start Client process" << endl;
        return 1;
    }

    CloseHandle(hWpClient);
    WaitForSingleObject(piClient.hProcess, INFINITE);
    char buffer[256];
    DWORD read, written;

    while (ReadFile(hRpClient, buffer, sizeof(buffer) - 1, &read, NULL) && read > 0)
    {
        buffer[read] = '\0';
        cout << buffer << endl;
        WriteFile(hWpPart, buffer, read, &written, NULL);
    }

    CloseHandle(hRpClient);
    CloseHandle(hWpPart);

    ZeroMemory(&siPart, sizeof(STARTUPINFO));
    siPart.cb = sizeof(STARTUPINFO);
    siPart.dwFlags = STARTF_USESTDHANDLES;
    siPart.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    siPart.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    siPart.hStdError = GetStdHandle(STD_ERROR_HANDLE);

    wsprintf(comlinePart, L"C:\\Part\\x64\\Debug\\Part.exe %d %d", (int)hRpPart, (int)hWpPart);

    if (!CreateProcess(NULL, comlinePart, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &siPart, &piPart))
    {
        cout << "Failed to start Part process" << endl;
        return 1;
    }

    WaitForSingleObject(piPart.hProcess, INFINITE);

    while (ReadFile(hRpPart, buffer, sizeof(buffer) - 1, &read, NULL) && read > 0)
    {
        buffer[read] = '\0';
        cout << buffer << endl;
    }

    cout << "\nPress any key to continue...";
    cin.ignore();
    cin.get();

    CloseHandle(piClient.hProcess);
    CloseHandle(piClient.hThread);
    CloseHandle(piPart.hProcess);
    CloseHandle(piPart.hThread);
    CloseHandle(hRpPart);
    CloseHandle(mutex);

    return 0;
}

// chrome-test.cpp : Defines the entry point for the application.
//

#include "chrome-test.h"

using namespace std;

std::string GetChromeCanaryPath()
{
    TCHAR szPath[MAX_PATH];
    if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, szPath)))
    {
        std::string strPath(szPath);
        strPath += "\\Google\\Chrome SxS\\Application\\chrome.exe";
        if (PathFileExists(strPath.c_str()))
            return strPath;
    }
    return "";
}

int main()
{
    std::string chromeCanaryPath = GetChromeCanaryPath();
    std::cout << chromeCanaryPath << std::endl;

    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Replace "C:\\path\\to\\your\\executable.exe" with the path to your executable
    // Replace "-arg1 -arg2" with the command line arguments you want to pass
    chromeCanaryPath.append(" --headless --disable-gpu --remote-debugging-port=9222 https://www.example.com/");
    std::cout << chromeCanaryPath << std::endl;
    if (!CreateProcessA(NULL, const_cast<LPSTR>(chromeCanaryPath.c_str()), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
    {
        printf("CreateProcess failed (%d).\n", GetLastError());
        return 1;
    }

    // Wait for the process to finish
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Close process and thread handles
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}

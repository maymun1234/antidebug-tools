#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <string>
#include "Common/settings.h"
#include "Common/globals.h"
#include "Common/literal.h"
#include "Common/helperFunctions.h"
#include "Security/AntiDebug/antidebug.h"

using namespace std;

// Antidebug process isimleri
const std::string antidebugProcessName[] = {
    "spotify.exe",
    "spotify"
};
const int antidebugProcessCount = sizeof(antidebugProcessName) / sizeof(antidebugProcessName[0]);


bool checkProcesses() {
    bool status = false;
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) return false;

    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(PROCESSENTRY32);

    if (Process32First(hSnapshot, &pe)) {
        do {
            string processName = pe.szExeFile; // normal string
            for (int i = 0; i < antidebugProcessCount; ++i) {
                if (contains(processName, antidebugProcessName[i])) {
                    cout << "Kotu amacli yazilim bulundu: " << processName << endl;
                    status = true;
                    break; // aynı process için diğer patternleri kontrol etme
                }
            }
        } while (Process32Next(hSnapshot, &pe));
    }

    CloseHandle(hSnapshot);
    return status;
}

bool CheckProcessesNames() {
    wcout << L"PROGRAMLAR KONTROL EDİLİYOR\n";
    return checkProcesses();
}
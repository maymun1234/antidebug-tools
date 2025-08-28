#include <windows.h>
#include <iostream>

// NtQueryInformationProcess tanımı (ntdll.dll'den import edilir)
typedef NTSTATUS (NTAPI *pNtQueryInformationProcess)(
    HANDLE ProcessHandle,
    ULONG ProcessInformationClass,
    PVOID ProcessInformation,
    ULONG ProcessInformationLength,
    PULONG ReturnLength
);

// ProcessInformationClass değerleri
#ifndef ProcessDebugPort
#define ProcessDebugPort 7
#endif
#ifndef ProcessDebugObjectHandle
#define ProcessDebugObjectHandle 30
#endif
#ifndef ProcessDebugFlags
#define ProcessDebugFlags 31
#endif

void checkdebugport(void) {
    HMODULE hNtdll = GetModuleHandleW(L"ntdll.dll");
    if (!hNtdll) {
        printf("[DLL Handler] ntdll yuklenemedi.\n");
        return;
    }

    auto NtQueryInformationProcess = 
        (pNtQueryInformationProcess)GetProcAddress(hNtdll, "NtQueryInformationProcess");
    if (!NtQueryInformationProcess) {
        printf("[DLL Handler] NtQueryInformationProcess bulunamadi.\n");
        return;
    }

    NTSTATUS status;
   //44
    ULONG returnLen = 0;

    ULONG_PTR debugPort = 0;
    status = NtQueryInformationProcess(GetCurrentProcess(), ProcessDebugPort,
                                   &debugPort, sizeof(debugPort), &returnLen);
    if (status == 0 /* STATUS_SUCCESS */) {
        printf("[DLL Handler] DebugPort: 0x%08X\n", debugPort);

        //ifdebugdedected();
    } else {
        printf("debugger bulunamadı. ortam güvenli. NTSTATUS=0x%08X\n", status);
    }

    // 2) ProcessDebugObjectHandle kontrolü
    HANDLE hDebugObj = nullptr;
    status = NtQueryInformationProcess(GetCurrentProcess(), ProcessDebugObjectHandle,
                                       &hDebugObj, sizeof(hDebugObj), &returnLen);
    if (status == 0) {
        printf("[DLL Handler] DebugObjectHandle: 0x%p\n", hDebugObj);
        ifdebugdedected();
    } else {
        printf("[DLL Handler] debugger bulunamadi. ortam guvenli.. NTSTATUS=0x%08X\n", status);
    }
//gjgjjggj
//ghhghg
    // 3) ProcessDebugFlags kontrolü
    ULONG debugFlags = 0;
    status = NtQueryInformationProcess(GetCurrentProcess(), ProcessDebugFlags,
                                       &debugFlags, sizeof(debugFlags), &returnLen);
    if (status == 0) {
        printf("[DLL Handler] DebugFlags: 0x%08X\n", debugFlags);
        ifdebugdedected();
    } else {
        printf("[DLL Handler] debugger bulunamadi. ortam guvenli.. NTSTATUS=0x%08X\n", status);
    }
}


void ifdebugdedected(){
    //buraya debugger tespit edilirse ne olacağpını yazın.
}

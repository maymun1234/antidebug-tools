#include <stdio.h>
#include <windows.h>

int checkBreakpoint(void* addr) {
    unsigned char *p = (unsigned char*)addr;
    if (*p == 0xCC) {
        return 1; // breakpoint var
    }
    return 0;
}

void secretFunction() {
    printf("Burada gizli bir işlem var.\n");
}
extern "C" int runtimeprotecttest(void){

    if (checkBreakpoint(reinterpret_cast<void*>(secretFunction))) {
    printf("Debugger tespit edildi!\n");
    exit(1);
}

    secretFunction();
    return 0;
}

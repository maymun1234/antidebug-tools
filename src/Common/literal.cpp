#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <vector>
#include <string>
#include "Common/settings.h"
#include "Common/globals.h"
#include "Common/literal.h"
using namespace std;


const char * Literal[LITERAL_size] = {
    "1.22",
    "licensekey.dll"
};

const char * GetLiteral(int ID){
    return Literal[ID];
}
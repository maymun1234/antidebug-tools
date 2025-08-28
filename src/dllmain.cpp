#include <windows.h>
#include <iostream>
#include <string>
#include "Common/settings.h"
#include "Common/globals.h"
#include "Common/literal.h"
#include "Util/util.h"
#include "Util/task.h"
#include "Security/License/LicenseController.h"
#include "Security/AntiDebug/antidebug.h"
#include "Security/AntiDebug/antidebugger.h"
#include "Security/TimeCheck/TimeCheck.h"

using namespace std;

extern "C" void InitExport(void){
    CheckProcessesNames();
    ControlLicense();

    //handler başlatmadan önce hash kontrolü yapılacak dosyaları definevars ile tanıtalım
    DefineVars();
  //  Sayacı başlat
    StartHandler();
    GetLastWriteTime();
}

extern "C" int GetLicenseStatus(void){
    return GetLicenseCondition();
}

extern "C" int GetDebuggerTools(void){
    return GetLicenseCondition();
}

extern "C" void ifdebugdedected(void){
    //buraya şüpheli durum tespit edildiğinde ney paılacağını yazın.
}

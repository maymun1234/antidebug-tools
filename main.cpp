#include <windows.h>
#include <iostream>
#include <string>
#include "Common/settings.h"
#include "Common/globals.h"
#include "Common/literal.h"
#include "Util/util.h"
#include "Util/task.h"
#include "Security/License/LicenseController.h"
#include "Security/Antidebug/antidebug.h"
#include "Security/AntiDebugger/antidebugger.h"
#include "Security/License/LicenseController.h"
#include "Security/TimeCheck/TimeCheckcpp.h"

using namespace std;

//intexport 

extern "C" __declspec(dllexport) void InitExport(void){
    CheckProcessesNames();
    ControlLicense();
    
    //handler başlatmadan önce hash kontrolü yapılacak dosyaları definevars ile tanıtalım
    DefineVars();
  //  Sayacı başlat
    StartHandler();
    GetLastWriteTime();
}

extern "C" __declspec(dllexport) int GetLicenseStatus(void){
    return GetLicenseCondition();
}


extern "C" extern "C" __declspec(dllexport) int GetDebuggerTools(void){
    return GetLicenseCondition();
}


//bu kısım trst etmek için lütfen sil

int main() {
std::cout << "[INFO] Program başlıyor..." << std::endl;


// DLL fonksiyonu gibi tanımlanmış InitExport'u çağırıyoruz
InitExport();


std::cout << "[INFO] InitExport çağrısı tamamlandı." << std::endl;
std::cout << "[INFO] Lisans durumu: " << GetLicenseStatus() << std::endl;
std::cout << "[INFO] Debugger durumu: " << GetDebuggerTools() << std::endl;

system("pause");
return 0;
}


extern "C" __declspec(dllexport) void ifdebugdedected(void){
    //buraya şüpheli durum tespit edildiğinde ney paılacağını yazın.
}



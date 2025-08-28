#include <windows.h>
#include <iostream>
#include <string>

// The functions are defined in the SecurityTool library, we just need to declare them here.
extern "C" void InitExport(void);
extern "C" int GetLicenseStatus(void);
extern "C" int GetDebuggerTools(void);

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

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <windows.h>
#include <bcrypt.h>
#include <iomanip>
#include "Security/filehashcheck/filehashcheck.h"

#pragma comment(lib, "bcrypt.lib")
#include "Common/helperFunctions.h"
#include "Security/hashutils/hashutils.h"



#define DLL_EXPORT extern "C" __declspec(dllexport)

// Dosyanın adını al ve exe kontrolü yap
static std::string getFileName(const std::string& path) {
    size_t pos = path.find_last_of("\\/");
    if (pos != std::string::npos) return path.substr(pos + 1);
    return path;
}
//eve gidince ymek yerim
static void exenamecheck(const char* exe_path) {
    std::string exeName = getFileName(exe_path);

    if (_stricmp(exeName.c_str(), "program.exe") != 0) {
       print_colored(false, "[ALERT] Bu DLL'i cagiran exe 'program.exe' degil!");
        std::cerr << "Caller exe: " << exe_path << std::endl;
    }
}

// DLL fonksiyonu: SHA-256 ile hash kontrolü
bool CheckDLLHash(const char* file_path) {
    char exePath[MAX_PATH];
    GetModuleFileNameA(NULL, exePath, MAX_PATH);
    exenamecheck(exePath);

    std::vector<BYTE> actual_hash = calculate_sha256(file_path);
    if (actual_hash.empty()) {
        print_colored(false, "[ERROR][HASHCHECK] Dosya okunamadi veya hash hesaplanamadi!");
        return false;
    }

    std::string fileName = getFileName(file_path);
    std::vector<BYTE> expected_hash;

    if (fileName.size() > 4 && _stricmp(fileName.c_str() + fileName.size() - 4, ".exe") == 0) {
        // EXE dosyası için hash
        expected_hash = {
            0x6f, 0x8c, 0xe5, 0xdb, 0x85, 0x1e, 0xa9, 0xe6,
    0x25, 0x98, 0x01, 0x67, 0x5b, 0x52, 0xb6, 0x17,
    0x6b, 0x4f, 0xe2, 0x23, 0x8f, 0xf4, 0x19, 0x49,
    0x85, 0xdb, 0xa3, 0x3e, 0x69, 0x66, 0x49, 0xad
        };
        std::cout << "[INFO] EXE dosyası hash kontrolü başlıyor: " << fileName << std::endl;
    } else if (fileName.size() > 4 && _stricmp(fileName.c_str() + fileName.size() - 4, ".lic") == 0) {
        // Lisans dosyası için hash
        expected_hash = {
            0x6f, 0x8c, 0xe5, 0xdb, 0x85, 0x1e, 0xa9, 0xe6,
    0x25, 0x98, 0x01, 0x67, 0x5b, 0x52, 0xb6, 0x17,
    0x6b, 0x4f, 0xe2, 0x23, 0x8f, 0xf4, 0x19, 0x49,
    0x85, 0xdb, 0xa3, 0x3e, 0x69, 0x66, 0x49, 0xad
        };
        std::cout << "[INFO] Lisans dosyası hash kontrolü başlıyor: " << fileName << std::endl;
    } else {
        std::cerr << "[ALERT] Dosya türü bilinmiyor: " << fileName << std::endl;
        return false;
    }

    std::cout << "[INFO] Dosya hash: ";
    print_hash(actual_hash);
    std::cout << "[INFO] Beklenen hash: ";
    print_hash(expected_hash);

    if (actual_hash == expected_hash) {
        print_colored(true, "[SUCCESS][HASHCHECK] Hash kontrolü başarılı.");
        return true;
    } else {
        print_colored(false, "[FAIL][HASHCHECK] Hash kontrolü başarısız!");
        return false;
    }
}


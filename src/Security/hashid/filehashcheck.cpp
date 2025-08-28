#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>

// CRC32 tablolarını başlat
DWORD crc32_table[256];
void init_crc32_table() {
    const DWORD polynomial = 0xEDB88320;
    for (DWORD i = 0; i < 256; i++) {
        DWORD crc = i;
        for (DWORD j = 0; j < 8; j++) {
            if (crc & 1)
                crc = (crc >> 1) ^ polynomial;
            else
                crc >>= 1;
        }
        crc32_table[i] = crc;
    }
}

// CRC32 hesaplama fonksiyonu
DWORD calculate_crc32(const BYTE* data, size_t length) {
    DWORD crc = 0xFFFFFFFF;
    for (size_t i = 0; i < length; i++) {
        BYTE index = (BYTE)((crc ^ data[i]) & 0xFF);
        crc = (crc >> 8) ^ crc32_table[index];
    }
    return crc ^ 0xFFFFFFFF;
}

// Konsol rengi ile yazdırma fonksiyonu
void print_colored(bool success, const std::string& message, DWORD expected, DWORD actual) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (success) {
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    } else {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
    }

    std::cout << message << std::endl;
    std::cout << "Expected: 0x" << std::hex << expected
              << " | Actual: 0x" << std::hex << actual << std::endl;

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

// DLL fonksiyonu: hash kontrolü
extern "C" bool CheckDLLHash(const char* dll_path, DWORD expected_hash) {
    init_crc32_table();

    std::ifstream file(dll_path, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "[ERROR][HASHCHECK] DLL açılamadı: " << dll_path << std::endl;
        return false;
    }

    // Dosya boyutunu güvenli şekilde al
    file.seekg(0, std::ios::end);
    size_t fileSize = static_cast<size_t>(file.tellg());
    file.seekg(0, std::ios::beg);

    if (fileSize == 0) {
        std::cerr << "[ERROR][HASHCHECK] DLL boş veya okunamadı: " << dll_path << std::endl;
        return false;
    }

    std::vector<BYTE> buffer(fileSize);
    file.read(reinterpret_cast<char*>(buffer.data()), fileSize);
    if (!file) {
        std::cerr << "[ERROR][HASHCHECK] DLL okuma hatası: " << dll_path << std::endl;
        return false;
    }

    DWORD actual_hash = calculate_crc32(buffer.data(), buffer.size());

    if (actual_hash != expected_hash) {
        print_colored(false, "[ALERT] DLL FALSE", expected_hash, actual_hash);
        return false;
    } else {
        print_colored(true, "[OK] DLL hash TRUE.", expected_hash, actual_hash);
        std::cerr << "konum: " << dll_path << std::endl;
        return true;
    }
}

// DLL giriş noktası
BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD  ul_reason_for_call,
                      LPVOID lpReserved) {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}

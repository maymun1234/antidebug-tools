//en son zaman soyutlaması ölçüldü



#include <chrono>
#include <iostream>
#include <windows.h>
#include "Security/TimeCheck/TimeCheck.h"
#include <tchar.h>
// --- static yardımcı metodlar (sadece bu dosyada geçerli) ---

// Şu anki zamanı al (system_clock)
static std::chrono::system_clock::time_point getNowSystem() {
    return std::chrono::system_clock::now();
}

// Şu anki zamanı al (steady_clock - monotonic, süre ölçmek için)

static std::chrono::steady_clock::time_point getNowSteady() {
    return std::chrono::steady_clock::now();
}

// İki zaman arasındaki farkı saniye cinsinden döndür (system_clock)
static long long diffSecondsSystem(
    const std::chrono::system_clock::time_point& t1,
    const std::chrono::system_clock::time_point& t2)
{
    return std::chrono::duration_cast<std::chrono::seconds>(t2 - t1).count();
}

// İki zaman arasındaki farkı milisaniye cinsinden döndür (steady_clock)
static long long diffMillisSteady(
    const std::chrono::steady_clock::time_point& t1,
    const std::chrono::steady_clock::time_point& t2)
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
}

// Dosyanın en son değiştirilme zamanını al (Windows API)
std::chrono::system_clock::time_point getFileLastWriteTime(const std::wstring& path) {
    HANDLE hFile = CreateFileW(
        path.c_str(),
        GENERIC_READ,
        FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
        nullptr,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        nullptr
    );

    if (hFile == INVALID_HANDLE_VALUE) {
        std::wcerr << L"[ERROR] Dosya açılamadı: " << path << std::endl;
        return std::chrono::system_clock::time_point{};
    }

    FILETIME ftWrite;
    if (!GetFileTime(hFile, nullptr, nullptr, &ftWrite)) {
        CloseHandle(hFile);
        std::wcerr << L"[ERROR] GetFileTime başarısız." << std::endl;
        return std::chrono::system_clock::time_point{};
    }



    std::wcout << L"[INFO] Dosya yazma zamanı alındı: " << path << std::endl;
    CloseHandle(hFile);

    // FILETIME → system_clock::time_point dönüşümü
    ULARGE_INTEGER ull;
    ull.LowPart = ftWrite.dwLowDateTime;
    ull.HighPart = ftWrite.dwHighDateTime;

    // FILETIME = 100-nanosecond intervals since Jan 1, 1601 (UTC)
    auto time = std::chrono::system_clock::time_point(
        std::chrono::duration_cast<std::chrono::system_clock::duration>(
            std::chrono::nanoseconds(ull.QuadPart * 100)
        )
    );
    return time;
}
//175
// --- global değişken ---
static std::chrono::system_clock::time_point lastWriteTime = getNowSystem();


// --- dışarı açılan fonksiyon (DLL export) ---

    std::chrono::system_clock::time_point GetLastWriteTime(void) {
        auto now = std::chrono::system_clock::now();
        timesingulairtycheck(now);
        std::cout << "[INFO] Last write time requested." << std::endl;
        std::cout << "[INFO] Last write time (epoch): "
                  << std::chrono::duration_cast<std::chrono::seconds>(
                         lastWriteTime.time_since_epoch())
                         .count()
                  << " seconds since epoch." << std::endl;
        return lastWriteTime;
    }

 void timesingulairtycheck(std::chrono::system_clock::time_point& t1){
        std::time_t tt = std::chrono::system_clock::to_time_t(t1);
        std::cout << "singularcheck: " << std::ctime(&tt) << std::endl;
        return;
}




void editstartedtime(void) {
    ULONGLONG lastWriteTime = 66;
    HKEY hKey;

    
}

//23
//o kargo hem emek kaybı hem iş kaybı hem doğaya zarar hem de diğer kullanıcıların iade edemem
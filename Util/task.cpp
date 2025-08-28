#include <windows.h>
#include <thread>
#include <atomic>
#include <chrono>
#include <iostream>

#include "util.h"
#include "task.h"
#include "../Security/AntiDebugger/antidebugger.h"
#include "../Security/hashid/hashID.h"
#include "../Security/filehashcheck/filehashcheck.h"
#include "../Security/Complexity/Complexity.h"
static std::thread g_worker;
static std::atomic<bool> g_running{false};
using string = std::string;
//alt thread fonksiyonu



//döngünün kontrol edeceği dosyaalrı lütfen ilk olarak burada verin
void DefineVars(){


    //dosya konumunu yaz
    const char* targetExePath = "program.exe";
    if (CheckDLLHash) {
        if (!CheckDLLHash(targetExePath)) {
            std::cerr << "EXE hash kontrolu basarisiz. Devam ediliyor...\n";
        } else {
            std::cout << "EXE hash kontrolu basarili.\n";
        }
    } else {
        std::cerr << "program.dll içinde CheckDLLHash fonksiyonu bulunamadi. EXE hash kontrolu atlandi.\n";
    }

     std::cerr << "diğer test\n";
    //dosya konumunu yaz.
    const char* targetLicensePath = "license.lic";
    if (CheckDLLHash) {
        if (!CheckDLLHash(targetLicensePath)) {
            std::cerr << "License hash kontrolu basarisiz. Devam ediliyor...\n";
        } else {
            std::cout << "License hash kontrolu basarili.\n";
        }
    } else {
        std::cerr << "program.dll içinde CheckDLLHash fonksiyonu bulunamadi. License hash kontrolu atlandi.\n";
    }

}

//bu döngüye güvenlik metodlarını yazın yazın
//bu döngüye metodlarını yazın yazın
//buraya güvenlik metodlarını yazın yazın
void handler_func() {
    using namespace std::chrono;
    auto next = steady_clock::now();
    while (g_running.load()) {
        // --- iş mantığı burada ---
        OutputDebugStringA("[DLL Handler] çalıştı!\n");
        printf("[DLL Handler] is working!\n");


        checkdebugport();
        //checkhash();
        CheckDuration();




        next += seconds(1);
        std::this_thread::sleep_until(next);
    }
    OutputDebugStringA("[DLL Handler] durduruldu.\n");
}

void StartHandler(void) {
    if (!g_running.load()) {
        g_running.store(true);
        g_worker = std::thread(handler_func);
        OutputDebugStringA("[DLL Handler] START.\n");
    }
}

 void StopHandler(void) {
    if (g_running.load()) {
        g_running.store(false);
        if (g_worker.joinable())
            g_worker.join();
    }
}

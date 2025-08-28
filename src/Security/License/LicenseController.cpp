//lisans dosyasına ulaşılıp kontrol edilmesi



#include <iostream>
#include <fstream>
#include <sstream>
#include <string> 

#include <vector>
#include <windows.h>
#include <bcrypt.h>
#include <iomanip>
#include <chrono>
#include "Security/License/LicenseController.h"
#include "Security/hashutils/hashutils.h"
#pragma comment(lib, "bcrypt.lib")

// Satırdan key=value ayıran yardımcı meodumuz
std::string getValue(const std::string& line, const std::string& key) {
    if (line.rfind(key + "=", 0) == 0) {
        return line.substr(key.size() + 1);
    }
    return "";
}

// SHA-256 ile lisans bütünlüğü kontrolü
bool checkLicense(const std::string& licPath) {
    // 1. Lisans dosyasını oku
    std::ifstream in(licPath);
    if (!in.is_open()) {
        std::cerr << "[ERROR] Lisans dosyası açılamadı.\n";
        return false;
    }

    std::string owner, validUntil, issueDate, signature;
    std::string line;
    while (std::getline(in, line)) {
        std::string v;
        if (!(v = getValue(line, "OWNER")).empty()) owner = v;
        if (!(v = getValue(line, "VALID_UNTIL")).empty()) validUntil = v;
        if (!(v = getValue(line, "ISSUE_DATE")).empty()) issueDate = v;
        if (!(v = getValue(line, "SIGNATURE")).empty()) signature = v;
    }
    in.close();

    if (owner.empty() || validUntil.empty()) {
        std::cerr << "[ERROR] Lisans dosyasında gerekli alanlar yok.\n";
        return false;
    }

    std::cout << "[INFO] Lisans sahibi: " << owner << "\n";
    std::cout << "[INFO] Bitiş tarihi : " << validUntil << "\n";

    // 2. Tarih kontrolü
    // Basit string karşılaştırma: YYYY-MM-DD HH:MM:SS formatında olduğu için lexicographic karşılaştırma çalışır.
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);

    std::tm now_tm{};
    localtime_s(&now_tm, &t);
    std::ostringstream oss;
    oss << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S");

    if (oss.str() > validUntil) {
        std::cerr << "[ALERT] Lisans süresi dolmuş!\n";
        return false;
    }

    // 3. Hash kontrolü (bütünlük için)
    std::vector<BYTE> actual_hash = calculate_sha256(licPath);
    if (actual_hash.empty()) {
        std::cerr << "[ERROR] Lisans hash hesaplanamadı.\n";
        return false;
    }

    

    std::cout << "[OK] Lisans geçerli.\n";
    return true;
}

int ControlLicense(void) {
    std::string licFile = "license.lic";

    if (!checkLicense(licFile)) {
        std::cerr << "Program lisanssız çalışamaz!\n";
        return 1;
    }

    std::cout << "Program başlatılıyor...\n";
    return 0;
}

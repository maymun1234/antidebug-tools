#include <windows.h>
#include <iostream>
#include <string>

// Basit CRC32 tablosu
DWORD crc32_table[256];

void init_crc32_table() {
    DWORD poly = 0xEDB88320;
    for (DWORD i = 0; i < 256; i++) {
        DWORD crc = i;
        for (DWORD j = 0; j < 8; j++)
            crc = (crc >> 1) ^ (-(int)(crc & 1) & poly);
        crc32_table[i] = crc;
    }
}

DWORD calculate_crc32(const BYTE* data, size_t length) {
    DWORD crc = 0xFFFFFFFF;
    for (size_t i = 0; i < length; i++)
        crc = (crc >> 8) ^ crc32_table[(crc ^ data[i]) & 0xFF];
    return crc ^ 0xFFFFFFFF;
}

// Hash kontrol fonksiyonu
void checkhash(void) {
    init_crc32_table(); // tabloyu initialize et
    
    std::string s = "heyho";
    DWORD expected = 0x5a0a6e9b; // önceden hesaplanmış CRC32 ("heyho" için)
    
    DWORD actual = calculate_crc32((const BYTE*)s.c_str(), s.size());
    
    if (actual != expected) {
        std::cout << "[ALERT] Kod veya data manipüle edilmiş!" << std::endl;
        std::cout << "Expected: 0x" << std::hex << expected 
                  << " | Actual: 0x" << std::hex << actual << std::endl;
       // ExitProcess(1);
    } else {
        std::cout << "[OK] Hash doğrulandı." << std::endl;
    }
}

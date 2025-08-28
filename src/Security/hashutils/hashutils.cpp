
#include "Security/hashutils/hashutils.h"
#include <windows.h>
#include <bcrypt.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
#include "Common/helperFunctions.h"


#pragma comment(lib, "bcrypt.lib")
//dosyalaır sha ile şifreleem
std::vector<unsigned char> calculate_sha256(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) return {};

    std::vector<unsigned char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    BCRYPT_ALG_HANDLE hAlg = NULL;
    BCRYPT_HASH_HANDLE hHash = NULL;
    DWORD hashObjectSize = 0, dataSize = 0;

    if (BCryptOpenAlgorithmProvider(&hAlg, BCRYPT_SHA256_ALGORITHM, NULL, 0) != 0) return {};
    if (BCryptGetProperty(hAlg, BCRYPT_OBJECT_LENGTH, (PBYTE)&hashObjectSize, sizeof(DWORD), &dataSize, 0) != 0) return {};

    std::vector<unsigned char> hashObject(hashObjectSize);
    std::vector<unsigned char> hash(32);

    if (BCryptCreateHash(hAlg, &hHash, hashObject.data(), hashObjectSize, NULL, 0, 0) != 0) return {};
    if (BCryptHashData(hHash, buffer.data(), (ULONG)buffer.size(), 0) != 0) return {};
    if (BCryptFinishHash(hHash, hash.data(), 32, 0) != 0) return {};

    BCryptDestroyHash(hHash);
    BCryptCloseAlgorithmProvider(hAlg, 0);

    return hash;
}

void print_hash(const std::vector<unsigned char>& hash) {
    for (auto b : hash)
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)b;
    std::cout << std::dec << std::endl;
}


// Konsol rengi ile mesaj yazdır

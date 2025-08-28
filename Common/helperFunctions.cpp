#include <string>
#include <algorithm>
#include "settings.h"
#include "globals.h"
#include "literal.h"
#include "helperFunctions.h"
#include <windows.h>
#include <bcrypt.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
using namespace std;


// Küçük harfe çeviren yardımcı fonksiyon. pencerelere bakarken kullanıyoruz.
std::string toLower(const std::string& str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return lowerStr;
}


// String içinde başka bir string var mı kontrol eder
bool contains(const std::string& str, const std::string& pattern) {
    std::string lowerStr = toLower(str);
    std::string lowerPattern = toLower(pattern);
    return lowerStr.find(lowerPattern) != std::string::npos;
}

void print_colored(bool success, const std::string& message) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (success)
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    else
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);

    std::cout << message << std::endl;
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
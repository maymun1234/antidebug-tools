#ifndef TIMECHECKCPP
#define TIMECHECKCPP
#include <chrono>
#include <iostream>
#include <windows.h>
std::chrono::system_clock::time_point GetLastWriteTime(void);
std::chrono::system_clock::time_point GetFileLastWriteTime(const std::wstring& path);
void timesingulairtycheck(std::chrono::system_clock::time_point& t1);
void editstartedtime(void);
#endif // TIMECHECKCPP
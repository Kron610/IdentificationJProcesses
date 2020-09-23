#ifndef GETPROCESSBYNAME_H
#define GETPROCESSBYNAME_H

#include <windows.h>
#include <tlhelp32.h>
#include <string.h>
#include <cstring>
#include <vector>


std::vector<DWORD> GetProcessByName(const wchar_t* pName, const wchar_t* pName2);

#endif // GETPROCESSBYNAME_H

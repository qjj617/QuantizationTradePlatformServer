#pragma once
#include<string>
#include <iostream>
using namespace std;

int TimetoInt(string sTime);
int DatetoInt(string sDate);

template<size_t size> inline void APIStrncpy(char(&Dst)[size], const char* source)
{
#ifdef WIN32
	strncpy_s(Dst, source, sizeof(Dst) - 1);
#endif

#ifdef linux
	strncpy(Dst, source, sizeof(Dst));
	//Dst[size] = '\0';
#endif
}
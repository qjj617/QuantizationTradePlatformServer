#include "TfbCommon.h"

int TimetoInt(string sTime)
{
	char *cha = (char*)sTime.data();             // 将string转换成char*。
	int nYear;
	int nMonth;
	int nDay;
	int nHour;
	int nMinute;
	int nSecond;
	sscanf_s(cha, "%d-%d-%d %d:%d:%d", &nYear, &nMonth, &nDay, &nHour, &nMinute, &nSecond);// 将string存储的日期时间，转换为int临时变量。
	int nTime = nYear * 10000 + nMonth * 100 + nDay;

	return nTime;
}

int DatetoInt(string sDate)
{
	char *cha = (char*)sDate.data();             // 将string转换成char*。
	int nYear;
	int nMonth;
	int nDay;
	sscanf_s(cha, "%d-%d-%d", &nYear, &nMonth, &nDay);// 将string存储的日期时间，转换为int临时变量。
	int nDate = nYear * 10000 + nMonth * 100 + nDay;

	return nDate;
}
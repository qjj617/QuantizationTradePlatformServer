#include "TfbCommon.h"

int TimetoInt(string sTime)
{
	char *cha = (char*)sTime.data();             // ��stringת����char*��
	int nYear;
	int nMonth;
	int nDay;
	int nHour;
	int nMinute;
	int nSecond;
	sscanf_s(cha, "%d-%d-%d %d:%d:%d", &nYear, &nMonth, &nDay, &nHour, &nMinute, &nSecond);// ��string�洢������ʱ�䣬ת��Ϊint��ʱ������
	int nTime = nYear * 10000 + nMonth * 100 + nDay;

	return nTime;
}

int DatetoInt(string sDate)
{
	char *cha = (char*)sDate.data();             // ��stringת����char*��
	int nYear;
	int nMonth;
	int nDay;
	sscanf_s(cha, "%d-%d-%d", &nYear, &nMonth, &nDay);// ��string�洢������ʱ�䣬ת��Ϊint��ʱ������
	int nDate = nYear * 10000 + nMonth * 100 + nDay;

	return nDate;
}
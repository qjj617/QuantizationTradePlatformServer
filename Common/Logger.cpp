#include "Logger.h"
#include <io.h>

//������Ϣ���ӵ������
ofstream Logger::m_debug_log_file;
//��Ϣ���ӵ������
ofstream Logger::m_info_log_file;
//������Ϣ�������
ofstream Logger::m_warn_log_file;
//������Ϣ�������
ofstream Logger::m_error_log_file;
//���ش�����Ϣ�������
ofstream Logger::m_fatal_log_file;
//��ʼ��ʱ�����־��Ϣ�ĵȼ�
LOG_LEVEL Logger::m_logLevel = LOG_LEVEL::LL_OFF;
//��־�洢·��
string Logger::m_strLogDir;

Logger::Logger()
{
}

Logger::~Logger()
{
	m_debug_log_file.close();
	m_debug_log_file.close();
	m_info_log_file.close();
	m_warn_log_file.close();
	m_error_log_file.close();
	m_fatal_log_file.close();
}

//�ж��ַ����Ƿ������ڸ�ʽyyyy-MM-dd
bool Logger::IsDateFormat(const char *pszParam)
{
	bool bFlag = true;
	for (int i = 0; '\0' != pszParam[i]; i++)
	{
		if (i < 4)
		{
			if ((pszParam[i] < '0') || (pszParam[i] > '9'))
			{
				return false;
			}
		}
		else if (4 == i)
		{
			if ('-' != pszParam[i])
			{
				return false;
			}
		}
		else if ((i > 4) && (i < 7))
		{
			if ((pszParam[5] < '0') || (pszParam[5] > '1'))
			{
				return false;
			}
			else if (pszParam[5] == '1')
			{
				if ((pszParam[6] < '0') || (pszParam[6] > '2'))
				{
					return false;
				}
			}

			if ((pszParam[6] < '0') || (pszParam[6] > '9'))
			{
				return false;
			}
		}
		else if (7 == i)
		{
			if ('-' != pszParam[i])
			{
				return false;
			}
		}
		else if ((i > 7) && (i < 10))
		{
			if ((pszParam[8] < '0') || (pszParam[8] > '3'))
			{
				return false;
			}
			else if (pszParam[8] == '3')
			{
				if ((pszParam[9] < '0') || (pszParam[9] > '1'))
				{
					return false;
				}
			}

			if ((pszParam[9] < '0') || (pszParam[9] > '9'))
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}

	return true;
}

//��ȡ��������
string Logger::GetDate()
{
	char szDate[16] = { 0 };
	time_t timep;
	struct tm p;

#ifdef WIN32
	time(&timep);
	localtime_s(&p, &timep);
	sprintf_s(szDate, "%04d-%02d-%02d", (1900 + p.tm_year), (1 + p.tm_mon), p.tm_mday);
#elif linux
	time(&timep);
	p = localtime(&timep);
	sprintf(szDate, "%04d-%02d-%02d", (1900 + p->tm_year), (1 + p->tm_mon), p->tm_mday);
#endif
	

	return szDate;
}

//��ȡ��ǰʱ��
string Logger::GetTime()
{
	char szTime[16] = { 0 };
	time_t timep;
	struct tm p;

#ifdef WIN32
	time(&timep);
	localtime_s(&p, &timep);
	sprintf_s(szTime, "%02d:%02d:%02d", p.tm_hour, p.tm_min, p.tm_sec);
#elif linux
	time(&timep);
	p = localtime(&timep);
	sprintf(szTime, "%02d:%02d:%02d", p->tm_hour, p->tm_min, p->tm_sec);
#endif

	return szTime;
}

//�ж��Ƿ�������
int Logger::IsLeapYear(const int year)
{
	if (((year % 4 == 0) && (year % 100 != 100)) || (year % 400 == 0))
	{
		return 1;
	}
	else
		return 0;
}

//��ȡ����strLaterDate������strPreDate�����������strLaterDateΪ��������ڣ����ڸ�ʽyyyy-MM-dd
int Logger::GetDays(const string& strPreDate, const string& strLaterDate)
{
	unsigned int year1, year2, mon1, mon2, day1, day2;
	char szTemp[6] = { 0 };
	int days = 0;
	int i = 0;

	memset(szTemp, 0, 6);
	memcpy(szTemp, strPreDate.c_str(), 4);
	year1 = atoi(szTemp);

	memset(szTemp, 0, 6);
	memcpy(szTemp, strPreDate.c_str() + 5, 2);
	mon1 = atoi(szTemp);

	memset(szTemp, 0, 6);
	memcpy(szTemp, strPreDate.c_str() + 8, 2);
	day1 = atoi(szTemp);

	memset(szTemp, 0, 6);
	memcpy(szTemp, strLaterDate.c_str(), 4);
	year2 = atoi(szTemp);

	memset(szTemp, 0, 6);
	memcpy(szTemp, strLaterDate.c_str() + 5, 2);
	mon2 = atoi(szTemp);

	memset(szTemp, 0, 6);
	memcpy(szTemp, strLaterDate.c_str() + 8, 2);
	day2 = atoi(szTemp);

	//�ж��м��Ƿ�������
	for (i = year1; i < year2; i++)
	{
		days += (1 == IsLeapYear(i)) ? 366 : 365;
	}

	for (i = 1; i < mon1; i++)
	{
		switch (i) {
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			days -= 31;
			break;
		case 2:
			days -= (1 == IsLeapYear(year1)) ? 29 : 28;
			break;
		case 4:
		case 6:
		case 9:
		case 11:
			days -= 30;
			break;
		default:
			break;
		}
	}

	days -= day1;

	for (i = 1; i < mon2; i++)
	{
		switch (i) {
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			days += 31;
			break;
		case 2:
			days += (1 == IsLeapYear(year2)) ? 29 : 28;
			break;
		case 4:
		case 6:
		case 9:
		case 11:
			days += 30;
			break;
		default:
			break;
		}
	}

	days += day2;

	return days;
}

//ɾ���洢��ָ��������־��Ĭ����־���30��,��ʼ����־ϵͳ������øú���������־����
void Logger::DeleteLog(int nStorageDays)
{
	string strCurDate;
	strCurDate = GetDate();

#ifdef WIN32
	WIN32_FIND_DATAA wfd;
	int iLength = 0;
	string strLogDir = m_strLogDir;
	strLogDir += "\\*.*";

	//���ҵ�һ���ļ���
	HANDLE hFile = ::FindFirstFileA(strLogDir.c_str(), &wfd);
	BOOL bRet = TRUE;
	while (bRet && (NULL != hFile))
	{
		if (FILE_ATTRIBUTE_DIRECTORY == wfd.dwFileAttributes)
		{
			if ('.' != wfd.cFileName[0] && IsDateFormat(wfd.cFileName))
			{
				//�ж���־Ŀ¼�Ƿ񳬹�ָ���洢����
				if (GetDays(wfd.cFileName, strCurDate) > nStorageDays)
				{
					//ɾ���洢��������ָ����������־Ŀ¼
					SHFILEOPSTRUCTA FileOp;
					FileOp.fFlags = FOF_NOCONFIRMATION;
					FileOp.hNameMappings = NULL;
					FileOp.hwnd = NULL;
					FileOp.lpszProgressTitle = NULL;
					FileOp.pFrom = (m_strLogDir + "\\" + wfd.cFileName).c_str();
					FileOp.pTo = NULL;
					FileOp.wFunc = FO_DELETE;
					SHFileOperationA(&FileOp);
				}
			}
		}
		//������һ��
		bRet = ::FindNextFileA(hFile, &wfd);
	}


#elif linux
	char szCurFile[16] = { 0 };
	char szFile[16] = { 0 };
	char szTemp[64] = { 0 };
	DIR *pDir = NULL;
	struct dirent *pdirent = NULL;

	pDir = opendir(pLogDir);
	if (NULL == pDir)
	{
		printf("open dir failed ...\n");
		return -1;
	}

	GetDateFilename(szCurFile);
	memcpy(szDate1, szCurFile, 8);

	while ((pdirent = readdir(pDir)) != NULL)
	{
		if (strcmp(pdirent->d_name, ".") == 0 || strcmp(pdirent->d_name, "..") == 0)
		{
			continue;
		}

		if (8 == pdirent->d_type)
		{
			strcpy(szFile, pdirent->d_name);
			memcpy(szDate2, szFile, 8);

			if (GetDays(szDate2, szDate1) > 30)
			{
				sprintf(szTemp, "%s%s", pLogDir, szFile);
				remove(szTemp);
			}
		}
	}

	closedir(pDir);
#endif
}

//��ʼ����־ϵͳ��ָ����־�洢·���������־����
bool Logger::InitLogger(string strLogDir, LOG_LEVEL logLevel)
{
	m_strLogDir = strLogDir;
	strLogDir += "\\";
	strLogDir += GetDate();
	m_logLevel = logLevel;

	//�ж���־Ŀ¼�Ƿ����
	int nRet = _access(m_strLogDir.c_str(), 0);
	if(-1 == nRet)
	{
		//������־Ŀ¼
		_mkdir(m_strLogDir.c_str());
	}

	//�жϵ�����־Ŀ¼�Ƿ���ڣ���������ڴ���Ŀ¼
	nRet = 0;
	nRet = _access(strLogDir.c_str(), 0);
	if (-1 == nRet)
	{
		//����������־Ŀ¼
		_mkdir(strLogDir.c_str());
	}

	m_debug_log_file.open(strLogDir + "\\debug.log", ios::app);
	m_info_log_file.open(strLogDir + "\\info.log", ios::app);
	m_warn_log_file.open(strLogDir + "\\warn.log", ios::app);
	m_error_log_file.open(strLogDir + "\\error.log", ios::app);
	m_fatal_log_file.open(strLogDir + "\\fatal.log", ios::app);

	if (m_debug_log_file.is_open() && 
		m_info_log_file.is_open() && 
		m_warn_log_file.is_open() && 
		m_error_log_file.is_open() && 
		m_fatal_log_file.is_open())
	{
		return true;
	}

	return false;
}

//���ô洢·��
void Logger::SetLogDir(string strLogDir)
{
	m_strLogDir = strLogDir;
}

//������־�ȼ�
void Logger::SetLogLevel(LOG_LEVEL logLevel)
{
	m_logLevel = logLevel;
}

//�����־
void Logger::log(LOG_LEVEL logLevel, string strLog)
{
	string strOut = GetDate();
	strOut += " ";
	strOut += GetTime();
	strOut += ": ";
	strOut += strLog;

	switch (m_logLevel)
	{
		case LOG_LEVEL::LL_ALL:
		case LOG_LEVEL::LL_DEBUG:
			{
				if (LOG_LEVEL::LL_DEBUG == logLevel)
				{
					m_debug_log_file << strOut << endl << flush;
				}		
			}
		case LOG_LEVEL::LL_INFO:
			{
				if (LOG_LEVEL::LL_INFO == logLevel)
				{
					m_info_log_file << strOut << endl << flush;
				}
			}
		case LOG_LEVEL::LL_WARN:
			{
				if (LOG_LEVEL::LL_WARN == logLevel)
				{
					m_warn_log_file << strOut << endl << flush;
				}
			}
		case LOG_LEVEL::LL_ERROR:
			{
				if (LOG_LEVEL::LL_ERROR == logLevel)
				{
					m_error_log_file << strOut << endl << flush;
				}
			}		
		case LOG_LEVEL::LL_FATAL:
			{
				if (LOG_LEVEL::LL_FATAL == logLevel)
				{
					m_fatal_log_file << strOut << endl << flush;
				}
			}		
		case LOG_LEVEL::LL_OFF:
			break;
		default:
			break;
	}
}

//���DEBUG�������־
void Logger::debug(string strLog)
{
	log(LOG_LEVEL::LL_DEBUG, strLog);
}

//���INFO�������־
void Logger::info(string strLog)
{
	log(LOG_LEVEL::LL_INFO, strLog);
}

//���WARN�������־
void Logger::warn(string strLog)
{
	log(LOG_LEVEL::LL_WARN, strLog);
}

//���ERROR�������־
void Logger::error(string strLog)
{
	log(LOG_LEVEL::LL_ERROR, strLog);
}

//���FATAL�������־
void Logger::fatal(string strLog)
{
	log(LOG_LEVEL::LL_FATAL, strLog);
}

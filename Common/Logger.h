#pragma once
#include <fstream>
#include <string>
#include <time.h>
using namespace std;

#ifdef _MSC_VER  
#include <Windows.h>
#include <direct.h> 
#include <tchar.h>
#elif __GNUC__
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#endif

//��־����ȼ������ڵ��ڵļ������־�����
enum LOG_LEVEL
{
	//������־��Ϣ
	LL_ALL,
	//������Ϣ
	LL_DEBUG,
	//ϵͳ����ʱһ���¼��Ϣ
	LL_INFO,
	//���������Ǳ�ڴ��������
	LL_WARN,
	//��Ȼ���������¼�������Ȼ��Ӱ��ϵͳ�ļ�������
	LL_ERROR,
	//ָ��ÿ�����صĴ����¼����ᵼ��Ӧ�ó�����˳�
	LL_FATAL,
	//��ߵȼ��ģ����ڹر�������־��¼
	LL_OFF
};

class Logger
{
public:
	Logger();
	~Logger();

	//��ʼ����־ϵͳ��ָ����־�洢·��, �����־�������־�洢����
	static bool InitLogger(string strLogDir = "..\\logs", LOG_LEVEL logLevel = LOG_LEVEL::LL_OFF);
	//ɾ���洢��ָ��������־��Ĭ����־���30��,��ʼ����־ϵͳ������øú���������־����
	static void DeleteLog(int nStorageDays = 30);
	//���ô洢·��
	static void SetLogDir(string strLogDir = "..\\logs");
	//������־�ȼ�,���ڵ���ָ���������־�������
	static void SetLogLevel(LOG_LEVEL logLevel = LOG_LEVEL::LL_OFF);
	//�����־
	static void log(LOG_LEVEL logLevel, string strLog);
	//���DEBUG�������־
	static void debug(string strLog);
	//���INFO�������־
	static void info(string strLog);
	//���WARN�������־
	static void warn(string strLog);
	//���ERROR�������־
	static void error(string strLog);
	//���FATAL�������־
	static void fatal(string strLog);

private:
	//�ж��ַ����Ƿ������ڸ�ʽyyyy-MM-dd
	static bool IsDateFormat(const char *pszParam);
	//��ȡ��������,���ڸ�ʽyyyy-MM-dd
	static string GetDate();
	//��ȡ��ǰʱ�䣬ʱ���ʽHH:mm:ss
	static string GetTime();
	//�ж��Ƿ�������
	static int IsLeapYear(const int year);
	//��ȡ����strLaterDate������strPreDate�����������strLaterDateΪ��������ڣ����ڸ�ʽyyyy-MM-dd
	static int GetDays(const string& strPreDate, const string& strLaterDate);
	//������Ϣ���ӵ������
	static ofstream m_debug_log_file;
	//��Ϣ���ӵ������
	static ofstream m_info_log_file;
	//������Ϣ�������
	static ofstream m_warn_log_file;
	//������Ϣ�������
	static ofstream m_error_log_file;
	//���ش�����Ϣ�������
	static ofstream m_fatal_log_file;
	//��ʼ��ʱ�����־��Ϣ�ĵȼ�
	static LOG_LEVEL m_logLevel;
	//��־�洢·��
	static string m_strLogDir;
};
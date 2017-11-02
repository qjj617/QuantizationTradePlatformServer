#pragma once
#include <AFX.h>
#include <sstream>
#include <iomanip>
#include <string>
using namespace std;

class Cstring : public string
{
public:
	Cstring();
	Cstring(const string& str);
	Cstring(const char* pstr);
	Cstring(const Cstring& str);
	Cstring(const TCHAR *pstr);
	Cstring(const CString& str);
	~Cstring(void);

	Cstring& operator =(const Cstring& str);
	Cstring& operator =(const TCHAR* pStr);
	Cstring& operator =(const CString& str);
	operator TCHAR*();
	operator CString();
	//��ֵ��һ��CString���͵�����ʱ����ֵ�ı䣬���ñ�����ֵ������֮�ı䣬�����¸�ֵ
	operator CString&();
	void clear();
	//����ַ������еĿո�
	Cstring& trim_all();
	//����ַ�������ָ�����ַ�
	Cstring& trim_all(const char ch);
	//����ַ�������ָ���������ַ�
	Cstring& trim_all(const string str);
	//����ַ�����ߵĿո�������һ���ǿո���ַ������
	Cstring& trim_left();
	//����ַ������ָ�����ַ���������һ����ָ�����ַ������
	Cstring& trim_left(const char ch);
	//����ַ������ָ���������ַ���������һ����ָ���������ַ������
	Cstring& trim_left(const string str);
	//����ַ����ұߵĿո�������һ���ǿո���ַ������
	Cstring& trim_right();
	//����ַ����ұ�ָ�����ַ���������һ����ָ�����ַ������
	Cstring& trim_right(const char ch);
	//����ַ����ұ�ָ���������ַ���������һ����ָ���������ַ������
	Cstring& trim_right(const string str);

	//����ֵ���͵�����ת�����ַ���
	template<class T>
	void to_string(const T& t, int nFixed = 2)
	{
		stringstream ss;
		ss << fixed << setprecision(nFixed) << t;
		this->clear();
		this->append(ss.str());
	}

	//���ַ���ת������ֵ������
	template<class T>
	T to_value(int nFixed = 2)
	{
		stringstream ss;
		ss << this->c_str();
		T t;
		ss >> fixed >> setprecision(nFixed) >> t;
		return t;
	}

private:
	void TcharToChar(const TCHAR * tchar, char * _char);
	void CharToTchar(const char * _char, TCHAR * tchar);

	CString m_str;
};


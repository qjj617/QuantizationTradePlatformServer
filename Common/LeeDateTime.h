#pragma once
#include <ctime>
#include <sstream>
#include <windows.h>
using namespace std;

class CLeeDateTime;
class CLeeDateTimeSpan {
	friend class CLeeDateTime;
public:
	CLeeDateTimeSpan()noexcept : m_span(0.0){ }
	CLeeDateTimeSpan(int days, int hours, int minutes, int seconds) noexcept
		: m_span(days + hours / 24.0 + minutes / 60.0 / 24.0 + seconds / 3600.0 / 24.0){ }
	CLeeDateTimeSpan(double span) noexcept: m_span(span){ }
	CLeeDateTimeSpan& operator=(const CLeeDateTimeSpan&rhs) noexcept {
		if (this == &rhs) {
			return *this;
		}
		m_span = rhs.m_span;
		return *this;
	}
	operator double() const noexcept { return m_span; }//����ת������,ת��Ϊdouble
	void SetDateTimeSpan(int days, int hours, int minutes, int seconds) noexcept {
		m_span = days + hours / 24.0 + minutes / 60.0 / 24.0 + seconds / 3600.0 / 24.0;
	}
	bool operator==(const CLeeDateTimeSpan& rhs) const {
		return m_span - rhs.m_span < HALF_SECOND &&
			rhs.m_span - m_span < HALF_SECOND;
	}
	bool operator!=(const CLeeDateTimeSpan& rhs) const { return !(*this == rhs); }
	bool operator>(const CLeeDateTimeSpan& rhs) const {
		return m_span - rhs.m_span >= HALF_SECOND;
	}
	bool operator<(const CLeeDateTimeSpan& rhs) const {
		return  rhs.m_span - m_span >= HALF_SECOND;
	}
	bool operator>=(const CLeeDateTimeSpan& rhs) const {
		return  !(*this < rhs);
	}
	bool operator<=(const CLeeDateTimeSpan& rhs) const {
		return  !(*this > rhs);
	}
	CLeeDateTimeSpan operator+(const CLeeDateTimeSpan& rhs) const {
		return CLeeDateTimeSpan(m_span + rhs.m_span);
	}
	CLeeDateTimeSpan operator-(const CLeeDateTimeSpan& rhs) const {
		return CLeeDateTimeSpan(m_span - rhs.m_span);
	}
	CLeeDateTimeSpan& operator+=(const CLeeDateTimeSpan& rhs) {
		m_span += rhs.m_span;
		return *this;
	}
	CLeeDateTimeSpan& operator-=(const CLeeDateTimeSpan& rhs) {
		m_span -= rhs.m_span;
		return *this;
	}
	double GetTotalDays() const noexcept { return m_span; }//�õ�������
	double GetTotalHours() const noexcept { return m_span * 24.0; }//�õ���Сʱ��
	double GetTotalMinutes() const noexcept { return m_span * (24.0 * 60.0); }//�õ��ܷ�����
	double GetTotalSeconds() const noexcept { return m_span * (24.0 * 60.0 * 60.0); }//�õ�������
private:
	double m_span;
	constexpr static double HALF_SECOND = 0.5 / (24.0 * 60.0 * 60.0);//����
};

//����ʱ����,�ܱ�ʾ1601/01/01����������
class CLeeDateTime {
public:
	CLeeDateTime() : m_dt(0.0) { }
	CLeeDateTime(double d) : m_dt(d) { }
	CLeeDateTime(time_t t) : m_dt(time_t_to_double(t)) { }
	CLeeDateTime(const struct tm& s) noexcept;
	CLeeDateTime(const SYSTEMTIME& st) noexcept;//�Ὣ������Ҳ����
	CLeeDateTime(int year, int month, int day, 
		int hour = 0, int minute = 0, int second = 0) noexcept;
	CLeeDateTime(const string& str) noexcept;
	CLeeDateTime(const CLeeDateTime& c) : m_dt(c.m_dt) { }//�������캯��
	string Format(const string& format = "%Y-%m-%d %H:%M:%S") const;//��ʽ�����ʱ��,��ʽ�����strftime�����ĸ�ʽ
	void SetDateTime(int year, int month, int day,
		int hour = 0, int minute = 0, int second = 0) noexcept;//��������ʱ��
	void ParseDateTime(const string& str) noexcept;//���ַ����н�������ʱ��
	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;
	int GetHour() const;
	int GetMinute() const;
	int GetSecond() const;
	int GetDayOfWeek() const;//һ�ܵĵڼ���. ����Ϊ0, ����Ϊ6.
	SYSTEMTIME Get_SYSTEMTIME() const;
	struct tm Get_tm() const;
	time_t Get_time_t() const;
	bool IsLeapYear() const;//�Ƿ�������
	operator double() const { return m_dt; }//����ת������,ת��Ϊdouble
	CLeeDateTime& operator=(const CLeeDateTime& rhs);//��ֵ����
	bool operator==(const CLeeDateTime& rhs) const;
	bool operator!=(const CLeeDateTime& rhs) const;
	bool operator>(const CLeeDateTime& rhs) const;
	bool operator<(const CLeeDateTime& rhs) const;
	bool operator>=(const CLeeDateTime& rhs) const;
	bool operator<=(const CLeeDateTime& rhs) const;

	CLeeDateTime operator+(const CLeeDateTimeSpan& span) const noexcept;
	CLeeDateTime& operator+=(const CLeeDateTimeSpan& span) noexcept;
	CLeeDateTime operator-(const CLeeDateTimeSpan& span) const noexcept;
	CLeeDateTime& operator-=(const CLeeDateTimeSpan& span) noexcept;

	CLeeDateTimeSpan operator-(const CLeeDateTime& rhs) const noexcept;//��������ʱ�������

	static CLeeDateTime GetCurrentTime();//�õ���ǰʱ��
	static bool IsLeapYear(int year);//ĳ���Ƿ�������
	static int GetDays(int year, int month);//�õ�ĳ��ĳ�µ�����
	static int GetTimeZone();//�õ�����ʱ��						 
	static double time_t_to_double(time_t t);//��time_t����ʱ��ת��Ϊdouble����
	static time_t double_to_time_t(double d);//��double����ʱ��ת��Ϊtime_t����
private:
	double m_dt;
	constexpr static double HALF_SECOND = 0.5 / 3600.0 / 24.0;//����
};

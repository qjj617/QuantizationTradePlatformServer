#pragma once
#include "XJAccountInfo.h"

class CAccountInfoManager
{
private:
	CAccountInfoManager();
	CAccountInfoManager(const CAccountInfoManager&);
	CAccountInfoManager& operator =(const CAccountInfoManager&);
public:
	~CAccountInfoManager();

	//����һ���ʽ��˻���Ϣ����ʵ�������ڵ���ģʽ
	static CAccountInfoManager& GetAccountInfoManager()
	{
		static CAccountInfoManager obj;
		return obj;
	}
	
	//�����˻�
	void AddAccount(string strAccountId, CAccountInfo *pAccount);
	//ɾ���˻�
	void DeleteAccount(string strAccountId);
	//�����ʽ��˻����Ҷ�Ӧ���˻�ʵ��
	CAccountInfo* GetAccountByAccountId(string strAccountId);

private:
	map<string, CAccountInfo*> m_Account_map;
};


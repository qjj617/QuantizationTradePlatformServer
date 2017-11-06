#include "stdafx.h"
#include "XJAccountInfoManager.h"


CAccountInfoManager::CAccountInfoManager()
{
}


CAccountInfoManager::~CAccountInfoManager()
{
	for (auto pair : m_Account_map)
	{
		delete pair.second;
	}
}

//�����˻�
void CAccountInfoManager::AddAccount(string strAccountId, CAccountInfo *pAccount)
{
	m_Account_map[strAccountId] = pAccount;
}

//ɾ���˻�
void CAccountInfoManager::DeleteAccount(string strAccountId)
{
	map<string, CAccountInfo*>::const_iterator it = m_Account_map.find(strAccountId);
	if (it != m_Account_map.cend())
	{
		delete (*it).second;
		m_Account_map.erase(it);
	}
}
//�����ʽ��˻����Ҷ�Ӧ���˻�ʵ��
CAccountInfo* CAccountInfoManager::GetAccountByAccountId(string strAccountId)
{
	map<string, CAccountInfo*>::const_iterator it = m_Account_map.find(strAccountId);
	if (it != m_Account_map.cend())
	{
		return (*it).second;
	}

	return NULL;
}

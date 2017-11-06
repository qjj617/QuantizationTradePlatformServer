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

//增加账户
void CAccountInfoManager::AddAccount(string strAccountId, CAccountInfo *pAccount)
{
	m_Account_map[strAccountId] = pAccount;
}

//删除账户
void CAccountInfoManager::DeleteAccount(string strAccountId)
{
	map<string, CAccountInfo*>::const_iterator it = m_Account_map.find(strAccountId);
	if (it != m_Account_map.cend())
	{
		delete (*it).second;
		m_Account_map.erase(it);
	}
}
//根据资金账户查找对应的账户实例
CAccountInfo* CAccountInfoManager::GetAccountByAccountId(string strAccountId)
{
	map<string, CAccountInfo*>::const_iterator it = m_Account_map.find(strAccountId);
	if (it != m_Account_map.cend())
	{
		return (*it).second;
	}

	return NULL;
}

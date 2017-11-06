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

	//创建一个资金账户信息管理实例，属于单列模式
	static CAccountInfoManager& GetAccountInfoManager()
	{
		static CAccountInfoManager obj;
		return obj;
	}
	
	//增加账户
	void AddAccount(string strAccountId, CAccountInfo *pAccount);
	//删除账户
	void DeleteAccount(string strAccountId);
	//根据资金账户查找对应的账户实例
	CAccountInfo* GetAccountByAccountId(string strAccountId);

private:
	map<string, CAccountInfo*> m_Account_map;
};


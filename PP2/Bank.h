#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <mutex>

#include "BankClient.h"

enum syncPrimitives
{
	criticalSection,
	mutex
};

class CBank
{
public:
	CBank(std::string syncPrimitive);
	~CBank();
	CBankClient* CreateClient();
	void UpdateClientBalance(CBankClient& client, int value);
	std::vector<CBankClient> GetClients();
	int CBank::GetClientBalance(int clientId);
	void CBank::SetClientBalance(int clientId, int balance);
	int CBank::GetTotalBalance();

private:
	std::vector<CBankClient> m_clients;
	std::map<int, int> clientInfo;
	int m_totalBalance;
	syncPrimitives m_syncPrimitive;

	void SetTotalBalance(int value);
	void SomeLongOperations();
	void EnableSync();
	void DisableSync();
	std::mutex MutexBankCalculate;
	CRITICAL_SECTION CritacalSectionBankCalculate;
};
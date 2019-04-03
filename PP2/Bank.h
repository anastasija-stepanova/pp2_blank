#pragma once
#include <iostream>
#include <vector>
#include <map>

#include "BankClient.h"

class CBank
{
public:
	CBank();
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

	void SetTotalBalance(int value);
	void SomeLongOperations();
};
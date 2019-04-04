	#include "Bank.h"

CBank::CBank(std::string syncPrimitive)
{
	m_clients = std::vector<CBankClient>();
	m_totalBalance = 0;
	m_syncPrimitive = syncPrimitives(atoi(syncPrimitive.c_str() + 1));
	InitializeCriticalSection(&CritacalSectionBankCalculate);
}

CBankClient* CBank::CreateClient()
{
	unsigned clientId = unsigned(m_clients.size());
	CBankClient* client = new CBankClient(this, clientId);
	m_clients.push_back(*client);
	return client;
}

CBank::~CBank() 
{
	DeleteCriticalSection(&CritacalSectionBankCalculate);
} 

std::vector<CBankClient> CBank::GetClients()
{
	return m_clients;
}

void CBank::EnableSync() 
{
	if (CBank::m_syncPrimitive == syncPrimitives::mutex)
	{
		MutexBankCalculate.lock();
	}
	else if (CBank::m_syncPrimitive == syncPrimitives::criticalSection)
	{
		EnterCriticalSection(&CritacalSectionBankCalculate);
	}
}

void CBank::DisableSync() 
{
	if (CBank::m_syncPrimitive == syncPrimitives::mutex)
	{
		MutexBankCalculate.unlock();
	}
	else if (CBank::m_syncPrimitive == syncPrimitives::criticalSection)
	{
		LeaveCriticalSection(&CritacalSectionBankCalculate);
	}
}

int CBank::GetClientBalance(int clientId)
{
	return clientInfo[clientId];
}

void CBank::SetClientBalance(int clientId, int balance)
{
	auto it = clientInfo.find(clientId);
	if (it == clientInfo.end()) 
	{
		clientInfo.emplace(clientId, balance);
		return;
	}

	it->second += balance;
}

void CBank::UpdateClientBalance(CBankClient &client, int value)
{
	CBank::EnableSync();
	int totalBalance = GetTotalBalance();
	std::cout << "Client " << client.GetId() << " initiates reading total balance. Total = " << totalBalance << "." << std::endl;
	
	SomeLongOperations();
	totalBalance += value;
	SetClientBalance(client.GetId(), value);

	std::cout
		<< "Client " << client.GetId() << " updates his balance with " << value
		<< " and initiates setting total balance to " << totalBalance
		<< ". Must be: " << GetTotalBalance() + value << "." << std::endl;

	// Check correctness of transaction through actual total balance
	if (totalBalance != GetTotalBalance() + value) {
		std::cout << "! ERROR !" << std::endl;
	}

	SetTotalBalance(totalBalance);
	CBank::DisableSync();
}

int CBank::GetTotalBalance()
{
	return m_totalBalance;
}

void CBank::SetTotalBalance(int value)
{
	m_totalBalance = value;
}

void CBank::SomeLongOperations()
{
	Sleep(1000);
}
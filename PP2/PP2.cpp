#include "stdafx.h"
#include "Bank.h"
#include "BankClient.h"

using namespace std;

void ShowInstractions()
{
	cout << "PP2.exe countClient syncPrimitive" << endl;
	cout << "Count clients more one" << endl;
	cout << "Sync primitives: criticalSection or mutex" << endl;
	cout << "-----------------------" << endl;
}

int main(int argc, char *argv[])
{
	int clientCount = 2;
	string syncPrimitive = "";

	ShowInstractions();

	if (argc != 3)
	{
		cout << "PP2.exe countClient syncPrimitive" << endl;
		return 1;
	}

	clientCount = atoi(argv[1]);
	syncPrimitive = atoi(argv[2]);

	CBank* bank = new CBank(syncPrimitive);

	for (int i = 0; i < clientCount; i++) 
	{
		CBankClient* client = bank->CreateClient();
	}

	string command = "";
	while (cin >> command)
	{
		if (command == "exit" || command == "quit") 
		{
			return 0;
		}
	}

	int clientTotalBalance = 0;

	for (CBankClient client : bank->GetClients()) {
		auto clientBalance = bank->GetClientBalance(client.GetId());
		cout << "Client: " << client.GetId() << " balance:" << clientBalance << endl;
		clientTotalBalance += clientBalance;
	}

	cout << "Clients balance: " << clientTotalBalance << endl;
	cout << "Bank balance: " << bank->GetTotalBalance() << endl;

    return 0;
}
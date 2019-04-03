#include "stdafx.h"
#include "Bank.h"
#include "BankClient.h"

using namespace std;

int main(int argc, char *argv[])
{
	int clientCount = 2;

	if (argc == 2)
	{
		clientCount = atoi(argv[1]);
	}

	CBank* bank = new CBank();

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
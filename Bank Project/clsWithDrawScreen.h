#pragma once
#include<string>
#include<iomanip>
#include"clsScreen.h"
#include"clsBankClient.h"
#include"clsInputValidate.h"


class clsWithDrawScreen : protected clsScreen
{
private:
	static void _PrintClientCard(clsBankClient Data)
	{
		cout << "\n=============(Acount Card)===============\n\n";
		cout << "  Name ==> " << Data.FirstName << endl;
		cout << "  Acount Number ==> " << Data.AccNum() << endl;
		cout << "  Phone Number ==> " << Data.Phone << endl;
		cout << "  Balance ==> " << Data.Balance << endl;
		cout << "  PinCode ==> " << Data.PinCode << endl;
		cout << "\n==========================================\n\n";
	}

public:
	static void ShowWithDrawScreen()
	{
		_DrawScreenHeader("\tWithDraw Screen");

		short Amount = 0;
		string AccNum = "";

		cout << "inter Account Number: ";
		getline(cin >> ws, AccNum);

		while (!clsBankClient::IsClientExist(AccNum))
		{
			cout << "\nThis Account Number isn't Exist, Please inter another one: ";
			getline(cin >> ws, AccNum);
		}
		clsBankClient Client = clsBankClient::Find(AccNum);

		_PrintClientCard(Client);

		cout << "Please inter withdraw Amount: ";
		cin >> Amount;

		while (Amount > Client.Balance)
		{
			cout << "Amount Exceeds the Balance, you can withdraw up to: " << Client.Balance << endl;
			cout << "Please inter another Amount: ";
			cin >> Amount;
		}

		char Confirm = 'N';
		cout << "Are you Sure you want to perform this Transaction?[Y][N]:  ";
		cin >> Confirm;
		if (toupper(Confirm) == 'Y')
		{
			Client.WithDraw(Amount);
			cout << "\nDeposite performed Successfully";
			cout << "\nNew Balance is: " << Client.Balance;
		}
		else
		{
			cout << "\n Process Was Cancelled";
		}
	}

};
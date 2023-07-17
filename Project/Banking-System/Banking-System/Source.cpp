#include<iostream> 
#include<conio.h> 
#include<string>

using namespace std;

class Account	//base class
{
protected:
	int acc_num; string acc_title; int balance;

public:
	Account(int an = 0, string n = " ", int b = 0)	//parameterized constructor
	{


		acc_num = an; acc_title = n; balance = b;
	}

	//set & get functions of class

	void setacc_num(int an)
	{
		acc_num = an;
	}
	int getacc_num()
	{
		return acc_num;
	}
	void setacc_title(string n)
	{
		acc_title = n;
	}
	string getacc_title()
	{
		return acc_title;
	}
	void setbalance(int b)
	{
		balance = b;
	}
	int getbalance()
	{
		return balance;
	}

	//function to modify account 
	void modify_account()
	{
		cout << "\n **Previous Detail** \n";	//show previous detail before modification
		account_detail();
		char choice;
		cout << "\n\n ****Modify Account****\n\n" << endl; 
		cout << " Do you want to modify Account Title (y/n): "; 
		cin >> choice;

		if (choice == 'y')
		{

			cout << " Enter New Account Title: "; 
			cin >> acc_title;
			cout << "\n ***Account Title Updated***\n" << endl;
		}

		cout << " Do you want to modify Account Balance (y/n): "; 
		cin >> choice;

		if (choice == 'y')
		{
			cout << "\n Do you want to deposit cash or withdraw cash (d/w): "; 
			cin >> choice;

			if (choice == 'd')
			{
				int d;
				cout << " Enter Deposit Amount: "; 
				cin >> d;
				deposit_amount(d);
				cout << "\n ***Balance Updated***\n" << endl;
			}
			else
			{
				int w;
				cout << " Enter Withdraw Amount: "; 
				cin >> w;
				withdraw_amount(w);
				cout << "\n ***Balance Updated***\n" << endl;
			}
		}
		cout << "\n **New Detail** \n";		//show new detail after modification
		account_detail();

	}


	//function to deposit amount
	void deposit_amount(int deposit)
	{
		balance += deposit;
	}

	//function to withdraw amount 
	void withdraw_amount(int withdraw)
	{
		balance -= withdraw;
	}

	//function to check balance 
	void balanceinquiry()
	{
		cout << "\n Available Balance in Account: " << balance << endl;
	}

	//virtual functions
	virtual void create_account() = 0; 
	virtual void account_detail() = 0;
};

class Current_Account : public Account	//derived class
{
	int deposit;

public:
	Current_Account(int an = 0, string n = " ", int b = 0, int d = 0) :Account(an, n, b)	//parameterized constructor
	{
		deposit = d;
	}

	//set & get functions



	void setdeposit(int d)
	{
		deposit = d;
	}
	int getdeposit()
	{
		return deposit;
	}

	//funtion to create new account 
	void create_account()
	{
		cout << " Enter Account Number: "; 
		cin >> acc_num;
		cout << " Enter Account Title: "; 
		cin >> acc_title;
		cout << " Enter Initial Deposit Amount: "; 
		cin >> deposit;
		balance += deposit;
		cout << "\n\n ***Account Created***\n\n" << endl;
	}

	//function to check account detail 
	void account_detail()
	{
		cout << "\n ***Current Account Detail***\n" << endl; 
		cout << " Account Number: " << acc_num << endl; 
		cout << " Account Title: " << acc_title << endl; 
		cout << " Balance: " << balance << endl;
	}
};

class Saving_Account : public Account
{
	int min_deposit; 
	double interest;

public:
	Saving_Account(int an = 0, string n = " ", int b = 0, int md = 0, int i = 0) : Account(an, n, b)	//parameterized constructor
	{
		min_deposit = md; 
		interest = i;
	}

	//set & get functions

	void setmin_deposit(int md)
	{
		min_deposit = md;
	}
	int getmin_deposit()
	{
		return min_deposit;
	}
	void setinterest(int i)
	{
		interest = i;
	}
	double getinterest()
	{
		return interest;
	}

	//funtion to create new account 
	void create_account()
	{
		cout << " Enter Account Number: "; 
		cin >> acc_num;
		cout << " Enter Account Title: "; 
		cin >> acc_title;
		cout << " Enter Initial Deposit Amount (Not less than 100k): "; 
		cin >> min_deposit;
		balance += min_deposit; 
		interest = 0.1 * balance;
		cout << "\n\n ***Account Created***\n\n" << endl;
	}

	//function to check account detail 
	void account_detail()
	{
		cout << "\n ***Saving Account Detail***\n" << endl; 
		cout << " Account Number: " << acc_num << endl; 
		cout << " Account Title: " << acc_title << endl; 
		cout << " Balance: " << balance << endl;
		interest = 0.1 * balance;
		cout << " Annual Interest: " << interest << endl;
	}
};

//functions prototype
bool find_acc(Account* p[], int size, int acc); 
int index(Account* p[], int size, int acc);

int main()
{
	Account* ptr[100];	//pointer to base class

	//storing some data in array
	ptr[0] = new Current_Account(999, "John", 10000, 5500); 
	ptr[1] = new Current_Account(888, "Ali", 45500); 
	ptr[2] = new Saving_Account(777, "Abdullah", 150000); 
	ptr[3] = new Saving_Account(666, "Watson", 100000);

	int i = 4; int option; do
	{
		//main menu

		cout << "\n	\n"; cout << "\tBANK MANAGEMENT SYSTEM";
		cout << "\n	\n"; cout << "\n (1) Create New Account";
		cout << "\n (2) Modify Account";
		cout << "\n (3) Check Account Detail";


		cout << "\n (4) Balance Inquiry"; cout << "\n (5) Deposit Amount"; cout << "\n (6) Withdraw Amount"; cout << "\n (7) Pay Utility Bills"; cout << "\n (8) Exit";
		cout << "\n\n Select your option: "; cin >> option;

		int n;
		switch (option)
		{
		case 1:	//create new account

			cout << "\n Choose Account Type (c/s): "; 
			char type;
			cin >> type;

			if (type == 'c')
			{
				ptr[i] = new Current_Account;	//dynamic binding 
				ptr[i]->create_account();
				i++;
			}
			else
			{
				ptr[i] = new Saving_Account;	//dynamic binding 
				ptr[i]->create_account();
				i++;
			}
			break;

		case 2:	//modify account

			cout << "\n Enter Account Number: "; 
			cin >> n;

			if (find_acc(ptr, i, n))
			{
				ptr[index(ptr, i, n)]->modify_account();
			}
			else
			{
				cout << "\n ***Account Not Found***\n" << endl;
			}
			break;

		case 3:	//check account details

			cout << "\n Enter Account Number: "; 
			cin >> n;

			if (find_acc(ptr, i, n))
			{
				ptr[index(ptr, i, n)]->account_detail();
			}
			else
			{
				cout << "\n ***Account Not Found***\n" << endl;
			}
			break;

		case 4:	//Balance Inquiry

			cout << "\n Enter Account Number: "; 
			cin >> n;

			if (find_acc(ptr, i, n))
			{
				ptr[index(ptr, i, n)]->balanceinquiry();
			}
			else
			{
				cout << "\n ***Account Not Found***\n" << endl;
			}
			break;

		case 5:	//deposit amount

			cout << "\n Enter Account Number: "; 
			cin >> n;

			if (find_acc(ptr, i, n))
			{
				cout << " Enter Deposit Amount: "; 
				int dep;
				cin >> dep;
				ptr[index(ptr, i, n)]->deposit_amount(dep);

				cout << "\n New Detail after Deposit "; 
				ptr[index(ptr, i, n)]->account_detail();
			}
			else
			{
				cout << "\n ***Account Not Found***\n" << endl;
			}
			break;

		case 6:	//withdraw amount

			cout << "\n Enter Account Number: "; 
			cin >> n;

			if (find_acc(ptr, i, n))
			{
				cout << " Enter Withdraw Amount: "; 
				int wid;
				cin >> wid;
				ptr[index(ptr, i, n)]->withdraw_amount(wid);

				cout << "\n New Detail after Withdraw "; 
				ptr[index(ptr, i, n)]->account_detail();
			}
			else
			{
				cout << "\n ***Account Not Found***\n" << endl;
			}
			break;

		case 7:	//pay utility bills

			cout << "\n Enter Bill Number: "; 
			int billnum;
			cin >> billnum;

			cout << " Enter Bill Amount: "; 
			int billamt;
			cin >> billamt;

			cout << "\n ***Bill Payed***" << endl;
		}

	} while (option != 8); 
	delete ptr[100];
	
	_getch(); 
	return 0;
}

//function definitions

//function to find account record in array 
bool find_acc(Account *p[], int size, int acc)
{
	bool found = false;
	for (int i = 0; i <= size; i++)
	{
		if (p[i]->getacc_num() == acc)
		{
			found = true; 
			break;
		}
	}
	return found;
}

//function to fetch index number of required account in an array 
int index(Account *p[], int size, int acc)
{
	for (int i = 0; i <= size; i++)
	{
		if (p[i]->getacc_num() == acc)
		{
			return i; 
			break;
		}
	}
}

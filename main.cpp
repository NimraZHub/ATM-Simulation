#include <iostream>
#include <iomanip>
#include <string>
#include <limits> // for input validation
using namespace std;

//========================= ATM Class =========================
class ATM
{
private:
    double balance;
    string pin;

public:
    // Constructor with default balance and PIN
    ATM(double initialBalance=10000, string defaultPIN="1234")
    {
        balance = initialBalance;
        pin = defaultPIN;
    }

    // Verify PIN
    bool verifyPIN(const string &enteredPIN)
    {
        return enteredPIN == pin;
    }

    // Get balance
    double getBalance()
    {
        return balance;
    }

    // Deposit money
    void deposit(double amount)
    {
        balance += amount;
        cout<<"\nDeposit successful. New balance: "<<fixed<<setprecision(2)<<balance<<endl;
    }

    // Withdraw money
    void withdraw(double amount)
    {
        balance -= amount;
        cout<<"\nWithdrawal successful. Remaining balance: "<<fixed<<setprecision(2)<<balance<<endl;
    }
};

// ========================= Controller Class =========================
class ATMController
{
public:
    void run()
    {
        ATM atm; // Create ATM object with default balance & PIN
        string enteredPIN;
        int attempts=0;

        cout<<"====================================="<<endl;
        cout<<"         Welcome to ATM System        "<<endl;
        cout<<"====================================="<<endl;

        // PIN Verification
        while(attempts<3)
        {
            cout<<"Enter your 4-digit PIN: ";
            cin>>enteredPIN;

            if(atm.verifyPIN(enteredPIN))
            {
                cout<<"Access Granted. Welcome."<<endl;
                showMenu(atm);
                return;
            }
            else
            {
                attempts++;
                cout<<"Incorrect PIN. Attempts left: "<<3-attempts<<endl;
            }
        }

        cout<<"Too many incorrect attempts. Exiting..."<<endl;
    }

private:
    void showMenu(ATM &atm)
    {
        int choice;
        double amount;

        while(true)
        {
            cout<<endl;
            cout<<"=========== Main Menu ==========="<<endl;
            cout<<"1. Check Balance"<<endl;
            cout<<"2. Deposit Money"<<endl;
            cout<<"3. Withdraw Money"<<endl;
            cout<<"4. Exit"<<endl;
            cout<<"================================="<<endl;

            // Input validation for menu choice
            cout<<"Enter your choice: ";
            if(!(cin>>choice))
            {
                cin.clear(); // clear error flag
                cin.ignore(numeric_limits<streamsize>::max(),'\n'); // discard invalid input
                cout<<"Invalid input. Please enter a number."<<endl;
                continue;
            }

            switch(choice)
            {
                case 1:
                    cout<<"Your current balance is: "<<fixed<<setprecision(2)<<atm.getBalance()<<endl;
                    break;

                case 2:
                    while(true)
                    {
                        cout<<"Enter amount to deposit (0 to cancel): ";
                        if(!(cin>>amount))
                        {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(),'\n');
                            cout<<"Invalid input. Please enter a valid amount."<<endl;
                            continue;
                        }
                        if(amount==0)
                        {
                            cout<<"Deposit cancelled."<<endl;
                            break;
                        }
                        if(amount>0)
                        {
                            atm.deposit(amount);
                            break;
                        }
                        else
                        {
                            cout<<"Invalid deposit amount. Try again."<<endl;
                        }
                    }
                    break;

                case 3:
                    while(true)
                    {
                        cout<<"Enter amount to withdraw (0 to cancel): ";
                        if(!(cin>>amount))
                        {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(),'\n');
                            cout<<"Invalid input. Please enter a valid number."<<endl;
                            continue;
                        }
                        if(amount==0)
                        {
                            cout<<"Withdrawal cancelled."<<endl;
                            break;
                        }
                        if(amount>0 && amount<=atm.getBalance())
                        {
                            atm.withdraw(amount);
                            break;
                        }
                        else if(amount>atm.getBalance())
                        {
                            cout<<"Insufficient funds. Try again."<<endl;
                        }
                        else
                        {
                            cout<<"Invalid withdrawal amount. Try again."<<endl;
                        }
                    }
                    break;

                case 4:
                    cout<<"Thank you for using the ATM. Goodbye!"<<endl;
                    return;

                default:
                    cout<<"Invalid choice. Please try again."<<endl;
            }
        }
    }
};

// ========================= Main Function =========================
int main()
{
    ATMController controller;
    controller.run();
    return 0;
}

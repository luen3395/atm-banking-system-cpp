/*---------------------------------------------------------
    WUST  C++ programming
   IT217. Programming Language
   Luis E. Argueta
   Final Project.
   Submittion date: 09/15/2024
   Purpose: Develop a ATM program that allow user to deposit, withdraw and shoe the balance of an account.
   			By introducing a pin from an list provided to give access, the user is provided a menu that will be repetitive until
   			th user press 4 to exit and create a document with the information
-----------------------------------------------------------*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std; // Using the standar namespace to avoid 'std :: before standar library identifier'

// Function to display the welcome message
void myBankWelcome() 
{
    cout << "Welcome to Argueta Bank ATM!" << endl;
}

// Function to display the menu options
void myBankUserMenu() 
{
    cout << "1. Deposit" << endl;
    cout << "2. Withdraw" << endl;
    cout << "3. Balance" << endl;
    cout << "4. Exit" << endl;
}

// Function to check if the entered PIN is valid
int mySearch(int pinCodes[], int numPins, int pin) 
{
    for (int i = 0; i < numPins; ++i) {
        if (pinCodes[i] == pin) {
            return 1;
        }
    }
    return 0;
}

// Function to display invalid PIN code message
void myPinCodeWarningMessage() 
{
    cout << "Invalid PIN code. Please try again." << endl;
}

// Function to display invalid menu selection message
void myMenuWarningMessage() 
{
    cout << "Invalid menu selection. Please try again." << endl;
}

// Function to display insufficient funds message
void myWithdrawWarningMessage() 
{
    cout << "Insufficient funds. Withdrawal cannot be processed." << endl;
}

// Function to write the account summary to an output file
void writeAccountSummary(const string& userName, double balance, const string& lastName) 
{
    ofstream outFile("Argueta_FP.txt");
    if (outFile.is_open()) {
        outFile << "Argueta Bank" << endl; // Bank name
        outFile << userName << endl;  // User name
        outFile << "Your balance is: $" << balance << endl; // Balance
        outFile << "Thank you for using Argueta Bank ATM!" << endl; // Thank you message
        outFile.close();
    } else {
        cout << "Error opening output file!" << endl;
    }
}

int main() 
{
    int pinCodes[300];
    int numPins = 0;
    ifstream inFile("aprovedPinCodes.txt");	//Open the file with PIN numbers.
    if (inFile.is_open()) 
	{
        while (inFile >> pinCodes[numPins] && numPins < 300) {
            ++numPins;
        }
        inFile.close();
    } else {
        cout << "Error opening PIN code file!" << endl;
        return 1;
    }

    myBankWelcome();	//Show welcome message

	//Ask the user for a PIN acccess and check if it is in the provided list
    string userName;
    int pin;
    cout << "Enter your name: ";
    getline(cin, userName);
    cout << "Enter your 4-digit PIN code: ";
    cin >> pin;

    if (!mySearch(pinCodes, numPins, pin)) 	//module to check the PIN
    {
        myPinCodeWarningMessage();
        return 1;
    }

    double balance = 2500.0;
    int menuChoice = 0;

    while (menuChoice != 4) //Loop for the choice made by user
    {
        myBankUserMenu();
        cout << "Enter your choice: ";
        cin >> menuChoice;

        if (menuChoice == 1) 
        {
            double depositAmount;
            cout << "Enter deposit amount: $";
            cin >> depositAmount;
            balance += depositAmount;
        }
        else if (menuChoice == 2) 
        {
            double withdrawAmount;
            cout << "Enter withdrawal amount: $";
            cin >> withdrawAmount;
            if (withdrawAmount > balance) 
            {
                myWithdrawWarningMessage();
            } 
            else 
            {
                balance -= withdrawAmount;
            }
        }
        else if (menuChoice == 3) 
        {
            cout << userName << ", your balance is $" << balance << endl;
        }
        else if (menuChoice == 4) 
        {
            writeAccountSummary(userName, balance, "Argueta");
            cout << "Your account summary was written in Argueta_FP.txt. Please open the file." << endl;
            cout << "Thank you for using Argueta Bank ATM. Goodbye!" << endl;
        }
        else 
        {
            myMenuWarningMessage();
        }
    }

    return 0;
}


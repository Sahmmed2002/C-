#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Account {
private:
    string name;
    int accountNumber;
    double balance;

public:
    void createAccount() {
        cout << "Enter Account Number: ";
        cin >> accountNumber;
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Initial Balance: ";
        cin >> balance;

        ofstream file("accounts.txt", ios::app);
        file << accountNumber << " " << name << " " << balance << endl;
        file.close();

        cout << "Account created successfully!\n";
    }

    void displayAllAccounts() {
        ifstream file("accounts.txt");
        if (!file) {
            cout << "No account records found.\n";
            return;
        }

        cout << "\n--- Account List ---\n";
        while (file >> accountNumber >> ws && getline(file, name, ' ') >> balance) {
            cout << "Account Number: " << accountNumber << "\n";
            cout << "Name: " << name << "\n";
            cout << "Balance: $" << balance << "\n";
            cout << "-------------------------\n";
        }
        file.close();
    }

    void transaction(int accNo, bool isDeposit) {
        ifstream file("accounts.txt");
        ofstream temp("temp.txt");
        bool found = false;

        while (file >> accountNumber >> ws && getline(file, name, ' ') >> balance) {
            if (accountNumber == accNo) {
                double amount;
                cout << (isDeposit ? "Enter amount to deposit: " : "Enter amount to withdraw: ");
                cin >> amount;

                if (!isDeposit && amount > balance) {
                    cout << "Insufficient balance.\n";
                }
                else {
                    balance += (isDeposit ? amount : -amount);
                    cout << (isDeposit ? "Deposited $" : "Withdrew $") << amount << " successfully.\n";
                }
                found = true;
            }
            temp << accountNumber << " " << name << " " << balance << endl;
        }

        file.close();
        temp.close();
        remove("accounts.txt");
        rename("temp.txt", "accounts.txt");

        if (!found) {
            cout << "Account not found.\n";
        }
    }

    void checkBalance(int accNo) {
        ifstream file("accounts.txt");
        bool found = false;

        while (file >> accountNumber >> ws && getline(file, name, ' ') >> balance) {
            if (accountNumber == accNo) {
                cout << "Account Number: " << accountNumber << "\n";
                cout << "Name: " << name << "\n";
                cout << "Balance: $" << balance << "\n";
                found = true;
                break;
            }
        }
        file.close();
        if (!found) {
            cout << "Account not found.\n";
        }
    }
};

// --- Main Menu ---
int main() {
    Account acc;
    int choice, accNo;

    do {
        cout << "\n--- Bank Management System ---\n";
        cout << "1. Create Account\n";
        cout << "2. Display All Accounts\n";
        cout << "3. Deposit\n";
        cout << "4. Withdraw\n";
        cout << "5. Check Balance\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            acc.createAccount();
            break;
        case 2:
            acc.displayAllAccounts();
            break;
        case 3:
            cout << "Enter account number: ";
            cin >> accNo;
            acc.transaction(accNo, true);
            break;
        case 4:
            cout << "Enter account number: ";
            cin >> accNo;
            acc.transaction(accNo, false);
            break;
        case 5:
            cout << "Enter account number: ";
            cin >> accNo;
            acc.checkBalance(accNo);
            break;
        case 6:
            cout << "Exiting program...\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 6);

    return 0;
}

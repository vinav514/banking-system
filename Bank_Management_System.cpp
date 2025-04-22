#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;

const int maxName = 50;
const int maxMoney = 7;
const int maxNumber = 12;
const int typeSize = 4;
const string sep = " |";
const int totalLen = maxName + maxNumber + typeSize + maxMoney + sep.size() * 4;
const string sepLine = sep + string(totalLen - 1, '=') + '|';

class Bank {
private:
    unsigned long long account_number;
    char holder_name[51];
    int deposit;
    char type;

public:
    void System_clear();
    void Get_Data();
    void Write_Data();
    void deposit_withdraw(int n, int option);
    void Display_Individual_Records(unsigned long long n);
    void report() const;
    void Show_account() const; 
    void dep(int); 
    void draw(int x); 
    unsigned long long retacno() const; 
    int retdeposit() const; 
    char rettype() const;
    void Modification_data();
};

template <typename T>
bool getInput(T& value) {
    cin >> value;
    if (cin.fail()) {
        cin.clear(); // clear error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
        cout << "Invalid input, please try again.\n";
        return false;
    }
    return true;
}

void Bank::Get_Data() {
    cout << "\n\n===========CREATE BANK ACCOUNT===========\n\n";
    cout << "\nEnter the Account Number:";
    while (!getInput(account_number) || to_string(account_number).size() != 12) {
        cout << "The account number must be 12 digits. Please try again.\n";
    }

    cout << "\nEnter Account Holder Name: ";
    cin.ignore();
    cin.getline(holder_name, 51);

    cout << "\nWhich type of Account \n[S for Saving Account] (or)[C for Current Account]: ";
    cin >> type;
    type = toupper(type);
    while (type != 'S' && type != 'C') {
        cout << "Please enter either 'S' or 'C' to avoid data corruption: ";
        cin >> type;
        type = toupper(type);
    }

    if (type == 'S') {
        cout << "\nEnter the Initial Amount for Saving Account [Minimum 500/-]: ";
        while (!getInput(deposit) || deposit < 500 || deposit >= 1000000) {
            cout << "Amount must be between 500/- and 1000000/-.\n";
        }
        cout << "\nAccount has been Created Successfully.";
    } else if (type == 'C') {
        cout << "\nEnter the Initial Amount for Current Account [Minimum 1000/-]: ";
        while (!getInput(deposit) || deposit < 1000 || deposit >= 1000000) {
            cout << "Amount must be between 1000/- and 1000000/-.\n";
        }
        cout << "\nAccount has been Created Successfully.";
    }
}

void Bank::Write_Data() {
    ofstream outFile;
    outFile.open("account.dat", ios::binary | ios::app);
    Get_Data();
    outFile.write((char*)this, sizeof(*this));
    outFile.close();
}

void Bank::Modification_data() {
    cout << "\nAccount No: " << account_number;
    cout << "\nModify Account Holder Name: ";
    cin.ignore();
    cin.getline(holder_name, 51);

    cout << "\nModify Type of Account: ";
    cin >> type;
    type = toupper(type);

    cout << "\nModify Total Balance Amount: ";
    while (!getInput(deposit) || deposit < 500 || deposit >= 1000000) {
        cout << "Amount must be between 500/- and 1000000/-.\n";
    }
}

void Bank::Display_Individual_Records(unsigned long long n) {
    bool flag = false;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile) {
        cout << "\nAn Error Occurred. Please try again.";
        return;
    }
    cout << "\nBALANCE DETAILS\n";

    while (inFile.read((char*)this, sizeof(*this))) {
        if (retacno() == n) {
            Show_account();
            flag = true;
        }
    }
    inFile.close();
    if (flag == false)
        cout << "\n\nAccount Details not Found.";
}

void Bank::report() const {
    cout << sep <<
        setw(maxNumber) << account_number << sep <<
        setw(maxName) << holder_name << sep <<
        setw(typeSize) << type << sep <<
        setw(maxMoney) << deposit << sep << endl << sepLine << endl;
}

void Bank::dep(int x) {
    deposit = deposit + x;
}

void Bank::draw(int x) {
    deposit -= x;
}

void Bank::Show_account() const {
    cout << "\nAccount No: " << account_number;
    cout << "\nAccount Holder Name: ";
    cout << holder_name;
    if (type == 'S') {
        cout << "\nType of Account: Saving ";
    } else {
        cout << "\nType of Account: Current ";
    }
    cout << "\nTotal Balance: " << deposit;
}

unsigned long long Bank::retacno() const {
    return account_number;
}

int Bank::retdeposit() const {
    return deposit;
}

char Bank::rettype() const {
    return type;
}

void Bank::System_clear() {
    system("cls");
}

void system_clear() {
    system("cls");
}

void Get_All_Data() {
    Bank call;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile) {
        cout << "An Error Occurred. Please try again.";
        return;
    }
    cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";
    cout << sepLine << endl << sep <<
        setw(maxNumber) << "A/C NO." << sep <<
        setw(maxName) << "NAME" << sep <<
        setw(typeSize) << "TYPE" << sep <<
        setw(maxMoney) << "BALANCE" << sep << endl <<
        sepLine << endl;
    while (inFile.read((char*)&call, sizeof(Bank))) {
        call.report();
    }
    inFile.close();
}

void Deposit_Withdraw(unsigned long long n, int option) {
    int amt;
    Bank call;
    bool found = false;
    fstream File;
    File.open("account.dat", ios::binary | ios::in | ios::out);
    if (!File) {
        cout << "An Error Occured. Please try again.";
        return;
    }
    while (!File.eof() && found == false) {
        File.read((char*)&call, sizeof(Bank));
        if (call.retacno() == n) {
            call.Show_account();
            if (option == 1) {
                cout << "\n\n===========DEPOSIT TO ACCOUNT===========";
                cout << "\n\nEnter the Amount: ";
                while (!getInput(amt) || call.retdeposit() + amt >= 1000000) {
                    cout << "Maximum deposit limit is 1000000/-.\n";
                }
                call.dep(amt);
            }
            if (option == 2) {
                cout << "\n\n===========WITHDRAW FROM ACCOUNT===========";
                cout << "\n\nEnter the Amount: ";
                while (!getInput(amt) || amt <= 0) {
                    cout << "Please enter a valid amount to withdraw.\n";
                }
                int bal = call.retdeposit() - amt;
                if ((bal < 500 && call.rettype() == 'S') || (bal < 1000 && call.rettype() == 'C')) {
                    cout << "\nInsufficient Balance. Please check your Balance.";
                } else {
                    call.draw(amt);
                }
            }
            int pos = (-1) * sizeof(call);
            File.seekp(pos, ios::cur);
            File.write((char*)&call, sizeof(Bank));
            cout << "\n\nAccount Records Updated Successfully.";
            found = true;
        }
    }
    File.close();
    if (found == false)
        cout << "\n\nAccount Records not Found.";
}

void Delete_Account(unsigned long long n) {
    Bank call;
    ifstream inFile;
    ofstream outFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile) {
        cout << "An Error Occurred. Please try again.";
        return;
    }
    outFile.open("account_temp.dat", ios::binary);
    inFile.seekg(0, ios::beg);
    while (inFile.read((char*)&call, sizeof(Bank))) {
        if (call.retacno() != n) {
            outFile.write((char*)&call, sizeof(Bank));
        }
    }
    inFile.close();
    outFile.close();
    remove("account.dat");
    rename("account_temp.dat", "account.dat");
    cout << "\n\nRecord has been Deleted.";
}

void Account_Modification(unsigned long long n) {
    Bank call;
    bool found = false;
    fstream File;
    File.open("account.dat", ios::binary | ios::in | ios::out);
    if (!File) {
        cout << "An Error Occurred. Please try again.";
        return;
    }
    while (!File.eof() && found == false) {
        File.read((char*)&call, sizeof(Bank));
        if (call.retacno() == n) {
            call.Show_account();
            cout << "\n\n===========MODIFY ACCOUNT===========";
            cout << "\nNew Details of the Account: " << endl;
            call.Modification_data();
            int pos = (-1) * sizeof(Bank);
            File.seekp(pos, ios::cur);
            File.write((char*)&call, sizeof(Bank));
            cout << "\n\nRecord Updated.";
            found = true;
        }
    }
    File.close();
    if (found == false)
        cout << "\n\n Record Not Found.";
}

void Credit() {
    system_clear();
    cout << "\n\nBanking Record System Project by Vinay." << "\nWritten in C++.";
}

int main() {
    char choice;
    unsigned long long account_number;
    Bank call;
    Credit();
    do {
        system_clear();
        cout << "\n===========================";
        cout << "\n  BANKING RECORD SYSTEM";
        cout << "\n===========================\n\n";
        cout << "01. CREATE NEW ACCOUNT";
        cout << "\n02. MODIFY AN ACCOUNT";
        cout << "\n03. BALANCE ENQUIRY OF ACCOUNT";
        cout << "\n04. DEPOSIT IN ACCOUNT";
        cout << "\n05. WITHDRAW FROM ACCOUNT";
        cout << "\n06. ALL ACCOUNT HOLDER LIST";
        cout << "\n07. CLOSE AN ACCOUNT";
        cout << "\n08. EXIT FROM PROGRAM";
        cout << "\n\nSELECT THE OPTION: ";
        cin >> choice;
        system_clear();
        switch (choice) {
            case '1':
                call.Write_Data();
                break;
            case '2':
                cout << "\n\nAccount No: ";
                cin >> account_number;
                Account_Modification(account_number);
                break;
            case '3':
                cout << "\n\nAccount No: ";
                cin >> account_number;
                call.Display_Individual_Records(account_number);
                break;
            case '4':
                cout << "\n\nAccount No: ";
                cin >> account_number;                               
                Deposit_Withdraw(account_number, 1);
                break;
            case '5':
                cout << "\n\nAccount No: ";
                cin >> account_number;
                Deposit_Withdraw(account_number, 2);
                break;
            case '6':
                Get_All_Data();
                break;
            case '7':
                cout << "\n\nAccount No: ";
                cin >> account_number;
                Delete_Account(account_number);
                break;
            case '8':
                cout << "\nThanks for using the Bank Record System.\n";
                cout << "For more cool stuff, visit https://github.com/imabhisht\n";
                break;
            default:
                cout << "\a";
        }
        cin.ignore();
        cin.get();
        system_clear();
    } while (choice != '8');

    return 0;
}

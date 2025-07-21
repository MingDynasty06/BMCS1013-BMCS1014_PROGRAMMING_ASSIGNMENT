// PROGRAMMING_ASSIGNMENT_ADMIN.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
using namespace std;

int main() {
    const string username = "beauty123";
    const string password = "admin";

    string admin_username;
    string admin_password;

    int choice;

    cout << "===================================" << endl;
    cout << "        🗝️  ADMIN LOGIN PAGE        " << endl;
    cout << "===================================" << endl;
    cout << "1. Forgot Password"<<"Testing123" << endl;
    cout << "2. Login" << endl;
    cout << "3. Exit" << endl;
    cout << "-----------------------------------" << endl;
    cout << "Please enter your choice (1-3): ";
    cin >> choice;

    cout << endl;

    switch (choice) {
    case 1:
        cout << "============================" << endl;
        cout << "      🔑 RECOVERY DETAILS     " << endl;
        cout << "============================" << endl;
        cout << "Your username is: " << username << endl;
        cout << "Your password is: " << password << endl;
        cout << "-----------------------------------" << endl;
        cout << "Redirecting you to login page..." << endl << endl;


    case 2:
        cout << "=========================" << endl;
        cout << "         🔐 LOGIN         " << endl;
        cout << "=========================" << endl;

        while (true) {
            cout << "Please enter username: ";
            cin >> admin_username;

            cout << "Please enter password: ";
            cin >> admin_password;

            if (admin_username == username && admin_password == password) {
                cout << endl;
                cout << "✅ Login successful! Welcome, adminsssss." << endl;
                break; // Exit loop 
            }
            else {
                cout << endl;
                cout << "❌ Login unsuccessful. Wrong username or password." << endl;


                char tryAgain;
                cout << "Do you want to try again? (Y/N): ";
                cin >> tryAgain;

                if (tryAgain == 'N' || tryAgain == 'n') {
                    cout << "Returning to main menu..." << endl;
                    break;
                }
            }
        }
        break;

    case 3:
        cout << "============================" << endl;
        cout << "     👋 Exiting system...     " << endl;
        cout << "============================" << endl;
        break;

    default:
        cout << "⚠️ Invalid choice. Please select 1 to 3." << endl;
    }

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

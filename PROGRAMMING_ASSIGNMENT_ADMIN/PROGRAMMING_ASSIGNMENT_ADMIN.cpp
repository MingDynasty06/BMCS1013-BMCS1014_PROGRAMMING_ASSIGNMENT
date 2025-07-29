#include <iostream>
#include <string>
using namespace std;

struct Expert {
    string name;
    string schedule[7]; // 7 days in a week
};

// Function to display a selected expert's schedule
void viewExpertSchedule(Expert experts[], int size) {
    cout << "\n===== 👩‍💼 View Individual Expert Schedule =====\n";
    cout << "Available Experts:\n";

    for (int i = 0; i < size; i++) {
        cout << i + 1 << ". " << experts[i].name << endl;
    }

    int choice;
    cout << "Select an expert (1-" << size << "): ";
    cin >> choice;

    if (choice < 1 || choice > size) {
        cout << "⚠️ Invalid choice!\n";
        return;
    }

    int index = choice - 1;
    cout << "\n📅 Schedule for " << experts[index].name << ":\n";
    cout << "--------------------------------------------\n";
    string days[7] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };

    for (int i = 0; i < 7; i++) {
        cout << days[i] << " : " << experts[index].schedule[i] << endl;
    }
    cout << "--------------------------------------------\n";
}

int main() {
    const string username = "beauty123";
    const string password = "admin";
    string admin_username, admin_password;
    int choice;

    // Dummy expert data
    Expert experts[3] = {
        {"Aina Tan", {"10AM-6PM (3 sessions)", "12PM-8PM (4 sessions)", "10AM-6PM (3 sessions)",
                      "10AM-6PM (3 sessions)", "1PM-9PM (4 sessions)", "9AM-3PM (2 sessions)", "OFF"}},
        {"Bryan Lee", {"9AM-5PM (3 sessions)", "11AM-7PM (3 sessions)", "9AM-5PM (3 sessions)",
                       "10AM-6PM (3 sessions)", "OFF", "10AM-4PM (2 sessions)", "OFF"}},
        {"Chloe Wong", {"OFF", "12PM-8PM (3 sessions)", "10AM-6PM (4 sessions)",
                        "10AM-6PM (4 sessions)", "12PM-8PM (3 sessions)", "9AM-1PM (1 session)", "OFF"}}
    };

    cout << "===================================\n";
    cout << "        🗝️  ADMIN LOGIN PAGE        \n";
    cout << "===================================\n";
    cout << "1. Forgot Password\n";
    cout << "2. Login\n";
    cout << "3. Exit\n";
    cout << "-----------------------------------\n";
    cout << "Please enter your choice (1-3): ";
    cin >> choice;

    if (choice == 1) {
        cout << "\n🔑 Your USERNAME is: " << username << "\n";
        cout << "🔑 Your PASSWORD is: " << password << "\n";
        cout << "Redirecting you to login page...\n\n";
        choice = 2; // Go to login
    }

    if (choice == 2) {
        bool loggedIn = false;

        while (!loggedIn) {
            cout << "\nUsername: ";
            cin >> admin_username;
            cout << "Password: ";
            cin >> admin_password;

            if (admin_username == username && admin_password == password) {
                cout << "\n✅ Login successful! Welcome, Admin.\n";

                int adminChoice;
                do {
                    cout << "\n====== 📋 ADMIN MENU ======\n";
                    cout << "1. View Individual Expert Schedule\n";
                    cout << "2. Logout\n";
                    cout << "Choose an option: ";
                    cin >> adminChoice;

                    if (adminChoice == 1) {
                        viewExpertSchedule(experts, 3);
                    }
                    else if (adminChoice == 2) {
                        cout << "\n👋 Logging out...\n";
                    }
                    else {
                        cout << "⚠️ Invalid choice.\n";
                    }
                } while (adminChoice != 2);

                loggedIn = true;
            }
            else {
                cout << "❌ Wrong username or password. Try again.\n";
            }
        }
    }
    else if (choice == 3) {
        cout << "\n👋 Exiting system...\n";
    }
    else {
        cout << "⚠️ Invalid choice. Please select 1-3.\n";
    }

    return 0;
}

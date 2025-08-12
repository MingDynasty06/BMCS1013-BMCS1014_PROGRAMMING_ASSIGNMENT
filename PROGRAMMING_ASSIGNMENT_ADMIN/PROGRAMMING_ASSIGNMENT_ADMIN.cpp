#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

struct Expert {
    string name;
    string schedule[7];// 7 days in a week
    string CustomerList[10]; // Placeholder for customer list, can be expanded
    int Bonus[3];//include treamentHours, consultationHours , serviceCharges ,bonusRate
};
struct Customer {
    string name;
    string tel;
    string paymentStatus;
    string expertName;
    string servicesType;
};

// Function to display a selected expert's schedule
void viewExpertSchedule(Expert experts[], int size) {
    cout << "\n===== 👩‍💼 View Individual Expert Schedule =====\n";
    cout << "Available Experts:\n";

    for (int i = 0; i < size; i++) {
        cout << i + 1 << "." << experts[i].name << endl;

    }

    int choice;
    cout << "Select an expert (1-" << size << "): ";
    cin >> choice;

    if (choice < 1 || choice > size) {
        cout << "⚠ Invalid choice!\n";
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

void viewCustomerList(Customer customer[], int range) {
    int selection, realrange;

    cout << "\n==== Customer List ====\n\n";

    for (int i = 0; i < range; i++) {
        cout << i + 1 << "." << customer[i].name << endl;
    }

    cout << "\nSelect a customer to show more details" << "(1 -" << range << ") : ";
    cin >> selection;

    if (selection < 1 || selection > range) {
        cout << "⚠ Invalid choice!\n";
        return;
    }

    realrange = selection - 1;
    cout << "--------------------------------------" << endl;
    cout << left << setw(20) << "Customer" << ":" << customer[realrange].name << endl;
    cout << left << setw(20) << "Telefon Number" << ":" << customer[realrange].tel << endl;
    cout << left << setw(20) << "Payment Status" << ":" << customer[realrange].paymentStatus << endl;
    cout << left << setw(20) << "Assigned Expert" << ":" << customer[realrange].expertName << endl;
    cout << left << setw(20) << "Service Type" << ":" << customer[realrange].servicesType << endl;
    cout << "--------------------------------------" << endl << endl;

}


void SalesReport(Expert experts[], int size) {
    cout << "\n===== 📈 Sales Report =====\n";
    cout << "Sales Report - December 2025\n\n";
    for (int i = 0; i < size; i++) {

    }
}

void viewExpertBonus(Expert experts[], int size) {
    int TotalHours, BonusAmount, BonusRate;
    string resultbonusrate;

    cout << "\n===== 📊 View Expert Bonus Entitlements =====\n";
    cout << "Bonus Report - December 2025\n\n";

    for (int i = 0; i < size; i++) {
        cout << "Expert : " << experts[i].name << endl;//Known the expert by according to our sequence
        cout << "--------------------------------------" << endl;
        TotalHours = experts[i].Bonus[0] + experts[i].Bonus[1];//TreatmentHours + ConsultationHours
        if (TotalHours >= 30) {
            BonusRate = 50;
            resultbonusrate = "50%";
        }
        else if (TotalHours >= 25 && TotalHours < 30) {
            BonusRate = 25;
            resultbonusrate = "25%";
        }
        else {
            BonusRate = 0;
            resultbonusrate = "0%";
        }
        BonusAmount = (experts[i].Bonus[2] * BonusRate) / 100; //ServiceCharge*BonusRate

        cout << left << setw(20) << "Treatment Hours" << ": " << experts[i].Bonus[0] << endl;
        cout << left << setw(20) << "Consultation Hours" << ": " << experts[i].Bonus[1] << endl;
        cout << left << setw(20) << "Total Hours" << ": " << TotalHours << endl;
        cout << left << setw(20) << "Service Charges" << ": RM" << experts[i].Bonus[2] << endl;
        cout << left << setw(20) << "Bonus Rate" << ": " << resultbonusrate << endl;
        cout << left << setw(20) << "Bonus Amount" << ": RM" << BonusAmount << endl;
        cout << "--------------------------------------" << endl << endl;
    }
}

int main() {
    const string username = "beauty123";
    const string password = "admin";
    string admin_username, admin_password;
    int choice;

    Customer customer[3] = {
        {"Caden Lim",{"011-55006235"},{"Online Transfer"},{"Aina Tan"},{"Pre-wedding Services"}},
        {"Jun hao",{"011-12279172"},{"Cash"},{"Bryan Lee"},{"Hair Styling Service"}},
        {"Yi Ming",{"010-2011238"},{"Cash"},{"Chloe Wong"},{"Nail Care Service (Manicure & Pedicure)"}}
    };

    // Dummy expert data
    Expert experts[3] = {
        {"Aina Tan", {"10AM-6PM (3 sessions)", "12PM-8PM (4 sessions)", "10AM-6PM (3 sessions)",
                      "10AM-6PM (3 sessions)", "1PM-9PM (4 sessions)", "9AM-3PM (2 sessions)", "OFF"},{}, { 24,6,2100 } },
        {"Bryan Lee", {"9AM-5PM (3 sessions)", "11AM-7PM (3 sessions)", "9AM-5PM (3 sessions)",
                       "10AM-6PM (3 sessions)", "OFF", "10AM-4PM (2 sessions)", "OFF"}, {}, { 20,2,1100 }},
        {"Chloe Wong", {"OFF", "12PM-8PM (3 sessions)", "10AM-6PM (4 sessions)",
                        "10AM-6PM (4 sessions)", "12PM-8PM (3 sessions)", "9AM-1PM (1 session)", "OFF"} ,{},{20,6,5000}}
    };

    cout << "===================================\n";
    cout << "        🗝  ADMIN LOGIN PAGE        \n";
    cout << "===================================\n";
    cout << "1. Forgot Password\n";
    cout << "2. Login\n";
    cout << "3. Exit\n";
    cout << "-----------------------------------\n";
    cout << "Please enter your choice (1-3): ";
    cin >> choice;

    while (choice < 1 || choice>3) {
        cout << "\n⚠ Invalid choice. Please select 1-3.\n";
        cout << "\n===================================\n";
        cout << "        🗝  ADMIN LOGIN PAGE        \n";
        cout << "===================================\n";
        cout << "1. Forgot Password\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "-----------------------------------\n";
        cout << "Please enter your choice (1-3): ";
        cin >> choice;
    }

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
                    cout << "2. View Overall Schedule\n";
                    cout << "3. View Customer List\n";
                    cout << "4. Generate Sales Reports\n";
                    cout << "5. View Expert Bonus Entitlements\n";
                    cout << "6. Logout\n";
                    cout << "Choose an option:\n";
                    cin >> adminChoice;

                    if (adminChoice == 1) {
                        viewExpertSchedule(experts, 3);
                    }
                    else if (adminChoice == 3) {
                        viewCustomerList(customer, 3);
                    }
                    else if (adminChoice == 4) {
                        SalesReport(experts, 3);
                    }
                    else if (adminChoice == 5) {
                        viewExpertBonus(experts, 3);
                    }
                    else if (adminChoice == 6) {
                        cout << "\n👋 Logging out...\n";
                    }
                    else {
                        cout << "⚠ Invalid choice.\n";
                    }
                } while (adminChoice != 6);

                loggedIn = true;
            }
            else {
                cout << "❌ Login failed.\n";

                // Show the login menu again
                cout << "\n===================================\n";
                cout << "        🗝  ADMIN LOGIN PAGE        \n";
                cout << "===================================\n";
                cout << "1. Forgot Password\n";
                cout << "2. Login\n";
                cout << "3. Exit\n";
                cout << "-----------------------------------\n";
                cout << "Please enter your choice (1-3): ";
                cin >> choice;

                while (choice < 1 || choice > 3) {
                    cout << "\n⚠ Invalid choice. Please select 1-3.\n";
                    cout << "Please enter your choice (1-3): ";
                    cin >> choice;
                }

                if (choice == 1) {
                    cout << "\n🔑 Your USERNAME is: " << username << "\n";
                    cout << "🔑 Your PASSWORD is: " << password << "\n";
                    cout << "Redirecting you to login page...\n\n";
                    choice = 2;
                }
                else if (choice == 3) {
                    cout << "\n👋 Exiting system...\n";
                    return 0;
                }
                // if choice == 2 → loop continues and asks username/password again
            }
        }
    }


    else if (choice == 3) {
        cout << "\n👋 Exiting system...\n";
    }

    return 0;
}

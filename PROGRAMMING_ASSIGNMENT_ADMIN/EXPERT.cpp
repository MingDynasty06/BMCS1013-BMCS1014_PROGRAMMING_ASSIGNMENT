

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

const int MAX_BOOKINGS = 500;

struct Booking {
    string customerName;
    string serviceName;
    int expertIndex;        // index 对应 experts[]
    int day;                // 1–31
    string weekday;         // "Monday", etc.
    string timeSlot;        // "10:00–11:00"
    int duration; // in hours (1 for consultation, 3 for treatment)
};




Booking bookings[MAX_BOOKINGS];
int bookingCount = 0;

const int NUM_EXPERTS = 15;

struct Expert {
    string name;
    string password;
    int Treat_hours;
    int Consult_hours;
    int services_charges;
};

Expert experts[NUM_EXPERTS] = {
    {"cham",{"c555"},{24},{6},{2100}},
    {"tan", {"t666"},{25},{1} ,{2000}},
    {"lim", {"l222"},{20},{2},{2500}},
    {"ming",{"m444"},{24},{6},{2100}}
};

string toLower(string str) {
    for (int i = 0; i < str.length(); i++) {
        str[i] = tolower(str[i]);
    }
    return str;
}

int loginExpert();
void viewSchedule(int);
void viewAssignedCustomers(int);
void viewBonus(int);
int forgetpassword(int);

int forgetpassword(int i) {
    int choice;
    cout << "1. Try Again" << endl;
    cout << "2. Forgot Password" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    if (choice == 1) {
        return loginExpert();
    }
    else if (choice == 2) {
        cout << "Your password is: " << experts[i].password << endl;
        return loginExpert();
    }
    else {
        cout << "The number is not in range! Please select again the number 1 or 2.";
        return forgetpassword(i);
    }
}


int loginExpert() {
    string inputName, inputPassword;
    cout << "\n=== Expert Login ===\n";

    cout << "Enter Expert Name: ";
    cin >> inputName;

    cout << "Enter Password: ";
    cin >> inputPassword;

    for (int i = 0; i < NUM_EXPERTS; i++) {
        if (toLower(experts[i].name) == toLower(inputName) && experts[i].password == inputPassword) {
            cout << "Login successful. Welcome, " << experts[i].name << "!" << endl;
            return i;
        }
        else if (toLower(experts[i].name) != toLower(inputName) && experts[i].password == inputPassword) {
            cout << "The expert name does not exist." << endl;
            return loginExpert();
        }

        else if (toLower(experts[i].name) == toLower(inputName) && experts[i].password != inputPassword) {
            cout << "The password is incorrect." << endl;
            return forgetpassword(i);
        }

    }

    cout << "Login failed. Invalid name and password." << endl;
    return loginExpert();
}




int main() {


    int expertIndex = loginExpert();
    int choice;
    do {
        cout << "\n=== Expert Dashboard ===" << endl;
        cout << "1. View My Schedule" << endl;
        cout << "2. View Assigned Customers" << endl;
        cout << "3. View Bonus Entitlement" << endl;
        cout << "4. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            viewSchedule(expertIndex);
            break;
        case 2:
            viewAssignedCustomers(expertIndex);
            break;
        case 3:
            viewBonus(expertIndex);
            break;
        case 4:
            cout << "Logging out..." << endl;
            break;
        default:
            cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 4);
    system("pause");

    return 0;
}
void viewSchedule(int expertIndex) {
    cout << "~~ Schedule for " << experts[expertIndex].name << " ~~" << endl << endl;
    string weeks[5][5] = {
        {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"},
        {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"},
        {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"},
        {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"},
        {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"}
    }; //这个意思是（week几，星期几）
    int weekStartDay[5] = { 1, 8, 15, 22, 29 }; //这个是每个week开始的date
    int totalHours = 0;
    cout << "        ====================================" << endl;
    cout << "        |          December  2025          |" << endl;
    cout << "        ====================================" << endl;
    cout << "        | Su | Mo | Tu | We | Th | Fr | Sa |" << endl;
    cout << "        |----|----|----|----|----|----|----|" << endl;
    cout << " Week 1 |    | 01 | 02 | 03 | 04 | 05 | 06 |" << endl;
    cout << "        |----|----|----|----|----|----|----|" << endl;
    cout << " Week 2 | 07 | 08 | 09 | 10 | 11 | 12 | 13 |" << endl;
    cout << "        |----|----|----|----|----|----|----|" << endl;
    cout << " Week 3 | 14 | 15 | 16 | 17 | 18 | 19 | 20 |" << endl;
    cout << "        |----|----|----|----|----|----|----|" << endl;
    cout << " Week 4 | 21 | 22 | 23 | 24 | 25 | 26 | 27 |" << endl;
    cout << "        |----|----|----|----|----|----|----|" << endl;
    cout << " Week 5 | 28 | 29 | 30 | 31 |    |    |    |" << endl;
    cout << "        |----|----|----|----|----|----|----|" << endl << endl;

    for (int w = 0; w < 5; w++) {
        cout << "\nWeek " << w + 1 << ":" << endl;
        cout << left << setw(12) << "Day" << setw(25) << "Time Slot" << setw(20) << "Service" << setw(12) << "Duration" << endl;
        cout << string(69, '-') << endl;
        for (int d = 0; d < 5; d++) {
            for (int i = 0; i < bookingCount; i++) {
                if (bookings[i].expertIndex == expertIndex && bookings[i].weekday == weeks[w][d] && bookings[i].day >= weekStartDay[w] && bookings[i].day < weekStartDay[w] + 7) {
                    cout << left << setw(12) << bookings[i].weekday
                        << setw(25) << bookings[i].timeSlot
                        << setw(20) << bookings[i].serviceName
                        << bookings[i].duration << " hr(s)" << endl;
                    totalHours += bookings[i].duration;
                }
            }
        }
    }

    cout << "\nTotal Hours Worked: " << totalHours << " hrs" << endl;
    cout << "Remaining Hours: " << (30 - totalHours) << " hrs (Limit: 30 hrs)" << endl;


}

void viewAssignedCustomers(int expertIndex) {
    cout << "[Assigned Customers Feature - to be implemented]" << endl;

}

void viewBonus(int expertIndex) {
    int choose,real_choose, Hours_complete, bonus_percentage, bonus_earned;
    string resultBonusPercentage;
	Hours_complete = experts[expertIndex].Treat_hours + experts[expertIndex].Consult_hours;
    

    if (Hours_complete >= 30) {
        bonus_percentage = 50;
		resultBonusPercentage = "50%";
        bonus_earned = experts[expertIndex].services_charges * 0.5;
    }
    else if (Hours_complete >= 25 && Hours_complete < 30) {
        bonus_percentage = 25;
		resultBonusPercentage = "25%";
        bonus_earned = experts[expertIndex].services_charges * 0.25;
    }
    else if (Hours_complete < 25) {
        bonus_percentage = 0;
		resultBonusPercentage = "0%";
        bonus_earned = experts[expertIndex].services_charges * 0;
        
    }
    cout << setw(82) << "Expert Bonus Report  -  December" << endl;
    cout << "----------------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "TotaL Treatment Hours   Total Consultation Hours   Total Hours Completed   Total Service Charges   Bonus Percentage   Bonus Earned" << endl;
    cout << "----------------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << setw(21) << experts[expertIndex].Treat_hours << setw(27) << experts[expertIndex].Consult_hours << setw(24) << Hours_complete << setw(24) << experts[expertIndex].services_charges << setw(19) << resultBonusPercentage << setw(15) << bonus_earned << endl;


}

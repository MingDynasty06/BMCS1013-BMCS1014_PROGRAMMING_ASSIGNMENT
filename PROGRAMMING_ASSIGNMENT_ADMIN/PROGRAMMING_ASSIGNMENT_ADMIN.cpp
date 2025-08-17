#include <iostream>
#include <iomanip>
#include <string>
#include <cctype> // for isdigit

using namespace std;

const int TOTAL_DAYS = 31;
const int SLOTS_PER_DAY = 3;
const int TOTAL_EXPERTS = 3;
const int TOTAL_SERVICES = 5;
const int MAX_CUSTOMERS = 5;
string loggedInUser = "";
// day: 1 to 31
// expertID: 0 to 14 (all experts)
// slot: 1 to 3
// 3D array to track bookings for each expert, on each day, in each slot
// bookings[expertID][day][slot] == true means that slot is booked
// All values are initialized to false (no bookings at the start)
//Just tracks whether a slot is booked or not
//true = booked false = free
bool bookings[TOTAL_EXPERTS][TOTAL_DAYS + 1][SLOTS_PER_DAY + 1] = { false }; //bookings[5][1][1] = false, means on day 5, expert 1’s slot 1 is free.
bool appoinmentavailable[TOTAL_DAYS + 1][SLOTS_PER_DAY + 1] = { false };

struct Expertdetails { //detailed info abt experts
    string name;
    int price;
    string password;
    int expertID;
};

struct Servicedetails { // container for expert
    string serviceName;
    Expertdetails experts[3]; // 3 experts provide this service. (array)
};


// array of 5 Service objects, name is services , [type][variablename][size]
Servicedetails services[5] = { //services is an array with 5 different services ( diff element)
 {"Make Up Service", {
         {"Allice Tan (Senior)", 300,"t666", 0},
         {"Bella Lim (Junior)", 500,"l222", 1},
         {"Chloe Ong (Bridal Specialist)", 400,"o000", 2}
     }},
{"Pre-wedding service", {
        {"Allice Tan (Senior)", 1500,"t666", 0},
        {"Bella Lim (Junior)", 1200,"l222", 1},
        {"Chloe Ong (Bridal Specialist)", 1800,"o000", 2}
    }},
{"Hair Styling service", {
        {"Allice Tan (Senior)", 350,"t666", 0},
        {"Bella Lim (Junior)", 300,"l222", 1},
        {"Chloe Ong (Bridal Specialist)", 450,"o000", 2}
    }},
{"Bridesmaid & family makeup service", {
        {"Allice Tan (Senior)", 750,"t666", 0},
        {"Bella Lim (Junior)", 600,"l222", 1},
        {"Chloe Ong (Bridal Specialist)", 700,"o000", 2}
    }},
{"Nail care service (manicure & pedicure)", {
        {"Allice Tan (Senior)", 480,"t666", 0},
        {"Bella Lim (Junior)", 300,"l222", 1},
        {"Chloe Ong (Bridal Specialist)", 550,"o000", 2}
    }}
};

struct BookingInfo {
    bool isBooked = false;
    string username;
    string serviceName;
    string expertName;
    int expertID;
    int day;
    int slot;
    string paymentMethod;
    double totalAmount;
};

// booking details per expert
// Store booking details ,know everything about the booking
//not same with bool booking
BookingInfo bookingDetails[TOTAL_EXPERTS + 1][TOTAL_DAYS + 1][SLOTS_PER_DAY + 1] = {};

struct Customerdetails {
    string username;
    string password;
};

Customerdetails customers[MAX_CUSTOMERS] = {
    {"yijia", "12345"},
    {"xinhui", "woshidameinv"},
    {"zhunzi", "hahahaha"},
    {"junhao", "iphone16ge"},
    {"yiming", "woshidashuaige"}
};

// Get day of the week (1 = Monday, ..., 7 = Sunday)
int getDayOfWeek(int day) {
    return ((day - 1) % 7) + 1; // Dec 1, 2025 is Monday. Modulo 7 works naturally when start at 0.
}

string slotTimes[SLOTS_PER_DAY + 1] = {
    "", // 0 unused (start from 0)
    "10:00 AM - 12:00 PM", // slot1
    "1:00 PM - 3:00 PM", // slot2
    "4:00 PM - 6:00 PM" // slot3
};


void showCalendar() {
    cout << "\n========== December 2025 Calendar ==========" << endl << endl;
    cout << " Mon | Tue | Wed | Thu | Fri | Sat | Sun " << endl;
    cout << "------------------------------------------" << endl;

    for (int day = 1; day <= TOTAL_DAYS; ++day) {
        int dayOfWeek = getDayOfWeek(day); // tell which day of the week

        int bookedSlots = 0;
        for (int slot = 1; slot <= SLOTS_PER_DAY; ++slot) {
            bool slotBooked = false; // assume free

            // Check all experts for this day and slot
            for (int expert = 0; expert < TOTAL_EXPERTS; expert++) {
                if (bookings[expert][day][slot]) {
                    slotBooked = true; // slot is booked
                    break; // no need to check remaining experts
                }
            }

            if (slotBooked)
                bookedSlots++; // increase count of booked slots
        }


        if (dayOfWeek <= 5 && bookedSlots == SLOTS_PER_DAY) {
            cout << "  X  |"; // fully booked
        }
        else {
            // Print day correctly with spacing
            cout << " " << setw(2) << setfill(' ') << day << "  |";

        }

        if (dayOfWeek == 7) cout << endl;
    }

    cout << endl << "------------------------------------------" << endl;
}

void appointmentAvailability() {
    int day;

    while (true) {
        showCalendar();
        cout << "\nEnter the day of December to book (1-31): ";
        cin >> day;

        if (cin.fail() || day < 1 || day > TOTAL_DAYS) {
            cin.clear(); cin.ignore(1000, '\n');
            cout << "Invalid day. Try again.\n";
            continue;
        }

        int dayOfWeek = getDayOfWeek(day);
        if (dayOfWeek >= 6) {
            cout << "Weekends closed.\n";
            continue;
        }

        int bookedCount = 0; // how many slots on that day already booked
        for (int slot = 1; slot <= SLOTS_PER_DAY; ++slot) {
            bool slotBooked = false; // assume free until we check all experts

            // Check all experts for this day and slot
            for (int expert = 0; expert < TOTAL_EXPERTS; expert++) {
                if (bookings[expert][day][slot]) {
                    slotBooked = true; // if any experts is booked, slotBooked becomes true
                    break; // no need to check remaining experts
                }
            }

            if (slotBooked) { //check whether slotBooked is true or not, slotBooked is true means is this slot is taken
                bookedCount++; // increase the count of booked slots
            }
        }

        if (bookedCount == SLOTS_PER_DAY) {
            cout << "That day is fully booked.\n";
            continue;
        }

        break;
    }

    cout << "\n=== Slots for " << day << " December 2025 ===\n";

    for (int s = 1; s <= SLOTS_PER_DAY; s++) {
        bool slotBooked = false;

        // Check all experts for this day and slot
        for (int expert = 0; expert < TOTAL_EXPERTS; expert++) {
            if (bookings[expert][day][s]) {
                slotBooked = true;
                break; // no need to check other experts
            }
        }

        if (slotBooked) { // check whether slotBooked is true or not, slotBooked = true, print [booked]
            cout << s << ". " << slotTimes[s] << " [BOOKED]\n";
        }
        else { // slotBooked = false
            cout << s << ". " << slotTimes[s] << " [AVAILABLE]\n";
        }
    }
    string confirm;
    cout << "\nPress any letter to back to customer menu : ";
    cin >> confirm;
    return;

}

bool isAllDigits(const string& str) {
    for (char c : str) {           // Loop through each character 'c' in the string 'str'
        if (!isdigit(c))           // Check if 'c' is NOT a digit
            return false;          // If any character is not a digit, return false immediately
    }
    return true;                   // If all characters are digits, return true
}

// Booking function after choosing expert
void bookSlot(const string& expertName, const string& serviceName, double serviceCost, int expertID, int day, int slot) {
    while (true) {
        // Confirm booking
        char confirm;
        cout << "\nConfirm booking for " << serviceName << " with " << expertName << " on December " << day << " (Slot " << slot << " - " << slotTimes[slot] << ")? (Y/N): ";
        cin >> confirm;
        if (confirm == 'Y' || confirm == 'y') {
            //Payment calculation
            const double SST_RATE = 0.06; // 6% service tax
            double serviceCharge = serviceCost * SST_RATE;
            double total = serviceCost + serviceCharge;
            cout << endl;
            cout << "========================\n";
            cout << "     PAYMENT SUMMARY   " << endl;
            cout << "========================\n";
            cout << "Service Cost : RM " << fixed << setprecision(2) << serviceCost << endl;
            cout << "SST (6%)     : RM " << fixed << setprecision(2) << serviceCharge << endl;
            cout << "========================\n";
            cout << "TOTAL        : RM " << fixed << setprecision(2) << total << endl;
            cout << "========================\n" << endl;

            int paymentMethod;
            string paymentMethodName;
            double cash, changeAmount = 0.0;
            while (true) {
                cout << "\n===== Select Payment Method =====\n";
                cout << "1. QR Code\n";
                cout << "2. Credit Card\n";
                cout << "3. Cash\n";
                cout << "4. Cancel Payment\n" << endl;
                cout << "Choose option (1-4): ";
                cin >> paymentMethod;

                if (cin.fail()) { // user typed letters or symbols
                    cin.clear(); // clear the error state
                    cin.ignore(1000, '\n'); // throw away the wrong input
                    cout << "Invalid input! Please enter numbers only.\n";
                    continue; // go back to the top of the loop
                }

                if (paymentMethod == 1) {
                    paymentMethodName = "QR Code";
                    cout << "\n[Displaying QR Code for payment...]" << endl;
                    cout << "\n===== QR CODE =====\n";
                    cout << ".............               ..  ..  .. ..  ..  ..   ..  .............      .  .............      \n";
                    cout << "   =************:              **  **  *= +*  **  **   +*  *************      *- =************.     \n";
                    cout << "   =*  ++++++ .*: **++  ++...+*++**..**++*++**..++** :*:.  ++**  ++***++**..***- =*  ++++++ :*.     \n";
                    cout << "   =*  ****** .*: **  **         **    ***. **  **  *= +*      **   +*  **  **   =*  *****+ :*.     \n";
                    cout << "   =*  ****** .*: ******     +***  **** :************=     ****  *= +***         =*  *****+ :*.     \n";
                    cout << "   =*  ****** .*: ******     +***  **** :************=     ****  *= +***         =*  *****+ :*.     \n";
                    cout << "   =*         .*: ****    *+ +*      ** :*. **      *******  **   :*.   ****     =*         :*.     \n";
                    cout << "   =*.        .*: ****    *+ +*      ** :*. **      *******  **   :*.   ****     =*         :*.     \n";
                    cout << "   =************: **  **  *+ +*  **  ** :*. **  **  *= +*  **  ** :*. **  **  *= =************.     \n";
                    cout << "                    *******=         ** :*****      ***. ****           *******-                    \n";
                    cout << "   =***    **   =*  ****  *******  **  ***. *********=   **  ****              :***         -*.     \n";
                    cout << "   =*. ****  *********  **       **       +*****  ***********    *- +*****    ***. ***********.     \n";
                    cout << "   =*****               *************  *=         *****.   ******     ****                          \n";
                    cout << "   :-****-----------    **-----**---:--::   ------***+-    **:--: .---****--  ----------------.     \n";
                    cout << "     **  **  *+ =*    ****     **  **  *******  **  *= +*******     +*    ****              :*.     \n";
                    cout << "         **   .*****  **  *+   **      *=       **** :*. +*  *****- +********+ :***  **  *+         \n";
                    cout << "   =***    ***+   **      *+ +*  ****** :*. **       :***  ****     +*  **    *=                    \n";
                    cout << "         ****           *****.   ****** .*. **       :*. **      ***********   -*.   *******=       \n";
                    cout << "   =*****     .***  **       +***  **********************        *= =*****    ************+         \n";
                    cout << "                  **  *****+   +*****     +***      *=   +*      ***.   ****  *-     **             \n";
                    cout << "    ............  **  +++++= ..+*++**  .. =+**  ..  *= ..**      ***-...****..*- ..  **    ...      \n";
                    cout << "   =************: **         +***  **  *=   **  **  *= +***      **************- =*  **    ***.     \n";
                    cout << "   =*         .*: **         +*      ** :*. **      *= +*******             ***-     **             \n";
                    cout << "   =*  ++++++ .*:     +*   .+**++++  ** :*. **++++++***. **  **+++++. ++++++****++*++**++  *-       \n";
                    cout << "   =*  ****** .*:     **   .*******  ** :*. ***********. **  *******. *******************  *=       \n";
                    cout << "   =*  ****** .*:   **  ***+ +*      ***= +*  **  ** :*****      ***.   **  ** :*****  **           \n";
                    cout << "   =*  ****** .*: +**********. **  **  *=           *=   **  *****-   **    *************  ***.     \n";
                    cout << "   =*         .*:   **     .*******  ***=     *********.   ****** :*.     ****       ****  *-       \n";
                    cout << "   =*         .*:   **     .*******  ***=     *********.   ****** :*.     ****       ****  *-       \n";
                    cout << "   =************:     **  *+     ****       **  **  *= +***    ** :*. *****************    ***.     \n";
                    cout << endl << endl;
                    cout << "Scan this QR code with your banking app to pay RM " << fixed << setprecision(2) << total << "\n";
                    string confirm;
                    cout << "\nPress any letter and Enter after you have completed the payment: ";
                    cin >> confirm;
                    break; // exit loop after valid payment
                }
                else if (paymentMethod == 2) {
                    string cardholderName, cardNumber, expiryDate, cvv;
                    paymentMethodName = "Credit Card";

                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                    cout << "Enter cardholder name: ";
                    getline(cin, cardholderName); // Allows spaces in name

                    // Validate card number
                    while (true) {
                        cout << "Enter 16-digit card number: ";
                        cin >> cardNumber;

                        if (cardNumber.length() == 16 && isAllDigits(cardNumber)) {
                            break;
                        }
                        else {
                            cout << "Invalid card number. Please enter exactly 16 digits.\n";
                        }
                    }
                    // Validate expiry date (MM/YY)
                    while (true) {
                        cout << "Enter expiry date (MM/YY): ";
                        cin >> expiryDate;

                        if (expiryDate.length() == 5 && expiryDate[2] == '/' && //check third letter is /
                            isdigit(expiryDate[0]) && isdigit(expiryDate[1]) && //check 1,2,4,5letter is number
                            isdigit(expiryDate[3]) && isdigit(expiryDate[4])) {

                            int month = stoi(expiryDate.substr(0, 2)); //convert month(string) to integer
                            if (month >= 1 && month <= 12) {
                                break;
                            }
                        }
                        cout << "Invalid expiry date. Please use format MM/YY.\n";
                    }

                    // Validate CVV
                    while (true) {
                        cout << "Enter 3-digit CVV: ";
                        cin >> cvv;

                        if (cvv.length() == 3 && isAllDigits(cvv)) {
                            break;
                        }
                        else {
                            cout << "Invalid CVV. Please enter exactly 3 digits.\n";
                        }
                    }
                    break; // exit loop after valid payment
                }
                else if (paymentMethod == 3) {
                    paymentMethodName = "Cash";

                    while (true) {
                        cout << "\nEnter Payment Amount (RM): ";
                        cin >> cash;

                        if (cin.fail()) { // user entered invalid value
                            cin.clear();
                            cin.ignore(1000, '\n');
                            cout << "Invalid input! Please enter a numeric amount.\n";
                            continue;
                        }

                        if (cash < total) {
                            cout << "Insufficient payment. You still owe RM "
                                << fixed << setprecision(2) << (total - cash) << ".\n";
                        }
                        else {
                            if (cash > total) {
                                changeAmount = cash - total;
                            }
                            break; // payment accepted
                        }
                    }
                    break;
                }
                else if (paymentMethod == 4) {
                    cout << "\nPayment cancelled. Returning to customer menu...\n";
                    return; // or break and handle returning to menu outside
                }
                else {
                    cout << "Invalid payment method. Please choose again.\n";
                }
            }
            cout << setfill(' ');
            // Mark booking as successful after payment
            cout << "\n=====================================\n";
            cout << "            PAYMENT RECEIPT          \n";
            cout << "=====================================\n";
            cout << left << setw(20) << "Service" << ": " << serviceName << "\n";
            cout << left << setw(20) << "Expert" << ": " << expertName << "\n";
            cout << left << setw(20) << "Date (December)" << ": " << day << "\n";
            cout << left << setw(20) << "Slot" << ": Slot " << slot << " (" << slotTimes[slot] << ")\n";
            cout << left << setw(20) << "Payment Method" << ": " << paymentMethodName << "\n";
            cout << "-----------------------------------------\n";
            cout << left << setw(20) << "Service Cost" << ": RM " << fixed << setprecision(2) << serviceCost << "\n";
            cout << left << setw(20) << "Service Charge" << ": RM " << fixed << setprecision(2) << serviceCharge << "\n";
            cout << left << setw(20) << "Total Amount" << ": RM " << fixed << setprecision(2) << total << "\n";
            if (paymentMethodName == "Cash") {
                cout << left << setw(20) << "Amount Paid" << ": RM " << fixed << setprecision(2) << cash << "\n";
                cout << left << setw(20) << "Change" << ": RM " << fixed << setprecision(2) << changeAmount << "\n";
            }
            cout << "-----------------------------------------\n";
            cout << left << setw(20) << "Status" << ": Payment Successful\n";
            cout << "=====================================\n";
            cout << "         Booking Confirmed!          \n";
            cout << "      Thank you for your payment!    \n";
            cout << "       Please come again soon! :D    \n";
            cout << "=====================================\n";
            cout << endl << endl;
            char choice;
            while (true) {
                cout << "\nWould you like an invoice? (Y/N): ";
                cin >> choice;
                if (choice == 'Y' || choice == 'y') {
                    cout << "\n=====================================\n";
                    cout << "               INVOICE               \n";
                    cout << "=====================================\n";
                    cout << left << setw(20) << "Service" << ": " << serviceName << "\n";
                    cout << left << setw(20) << "Expert" << ": " << expertName << "\n";
                    cout << left << setw(20) << "Date (December)" << ": " << day << "\n";
                    cout << left << setw(20) << "Slot" << ": Slot " << slot << " (" << slotTimes[slot] << ")\n";
                    cout << left << setw(20) << "Payment Method" << ": " << paymentMethodName << "\n";
                    cout << "-------------------------------------\n";
                    cout << left << setw(20) << "Service Cost" << ": RM " << fixed << setprecision(2) << serviceCost << "\n";
                    cout << left << setw(20) << "Service Charge" << ": RM " << fixed << setprecision(2) << serviceCharge << "\n";
                    cout << left << setw(20) << "TOTAL" << ": RM " << fixed << setprecision(2) << total << "\n";
                    if (paymentMethodName == "Cash") {
                        cout << left << setw(20) << "Amount Paid" << ": RM " << fixed << setprecision(2) << cash << "\n";
                        cout << left << setw(20) << "Change" << ": RM " << fixed << setprecision(2) << changeAmount << "\n";
                    }
                    cout << "-----------------------------------------\n";
                    cout << left << setw(20) << "Status" << ": Payment Successful\n";
                    cout << "=====================================\n";
                    cout << "         Thank You for Visiting!     \n";
                    cout << "=====================================\n";
                    break;
                }
                else if (choice == 'N' || choice == 'n') {
                    break;
                }
                else {
                    cout << "Invalid choice! Please enter Y or N.\n";
                }
            }
            // After successful payment
            bookings[expertID][day][slot] = true; //***means ths slot is been booking
            bookingDetails[expertID][day][slot] = {
            true, //change to true
            loggedInUser,  // username who booked
            serviceName,
            expertName,
            expertID,
            day,
            slot,
            paymentMethodName,
            total
            };
            string confirm;
            cout << "\nPress any letter to back to customer menu : ";
            cin >> confirm;
            return;
        }

        else if (confirm == 'N' || confirm == 'n') {
            cout << "Booking cancelled.\n";
            return;
        }
        else {
            cout << "Invalid input. Please enter 'Y' or 'N'.\n";
        }
    }
}


// ===== View Booking =====
void viewMyBookings() {
    bool found = false;
    int counter = 0; // for table numbering
    cout << setfill(' ');
    cout << "\n=== YOUR BOOKINGS ===\n";
    cout << string(150, '-') << "\n";
    cout << left << setw(5) << "No"
        << setw(40) << "Service"
        << setw(40) << "Expert"
        << setw(10) << "Date"
        << setw(25) << "Slot"
        << setw(15) << "Payment"
        << setw(10) << "Amount" << "\n";
    cout << string(150, '-') << "\n";

    //loop every experts and every days and every slots
    for (int e = 0; e < TOTAL_EXPERTS; e++) {
        for (int d = 1; d <= TOTAL_DAYS; d++) {
            for (int s = 1; s <= SLOTS_PER_DAY; s++) {
                if (bookingDetails[e][d][s].isBooked && bookingDetails[e][d][s].username == loggedInUser) { //different data between logged in user
                    counter++;
                    cout << left << setw(5) << counter << setw(40) << bookingDetails[e][d][s].serviceName
                        << setw(40) << bookingDetails[e][d][s].expertName
                        << setw(10) << ("Dec " + to_string(d))
                        << setw(25) << slotTimes[bookingDetails[e][d][s].slot]
                        << setw(15) << bookingDetails[e][d][s].paymentMethod
                        << "RM " << fixed << setprecision(2) << bookingDetails[e][d][s].totalAmount << "\n";
                    found = true;
                }
            }
        }
    }
    if (!found) {
        cout << "No bookings found for this account.\n" << endl;
    }
    else {
        cout << string(150, '-') << "\n";
        cout << "Total Records: " << counter << "\n";
        cout << string(150, '-') << "\n";
    }
    string confirm;
    cout << "\nPress any letter to back to customer menu : ";
    cin >> confirm;
    return;
}

bool customerlogin() {
    string username, password;
    cout << endl;
    cout << "===== Customer Login ======" << endl << endl;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    int customerCount = 5;
    for (int i = 0; i < customerCount; i++) {
        if (customers[i].username == username && customers[i].password == password) {
            loggedInUser = username;
            return true;
        }
    }
    return false;
}

string showCustomerMenu(bool isLoggedIn) { // can return value, if void cannot , just can pass value
    string menuoption;
    do {
        cout << "" << endl;
        //cout << setw(120) << setfill("-") << endl;
        cout << "                 _         _" << endl;
        cout << "              .-~' '~-. .-~' '~-." << endl;
        cout << "            __ ... . -^-- ,- -- - - -^ ,._   ." << endl;
        cout << "   _. - ~v                          ( ,  ,=')---.-." << endl;
        cout << " '           .      ROSELLE    .'   \'   ;.'~- ._ ))" << endl;
        cout << " .            ._           _.'           {      )'~-," << endl;
        cout << "                  -.     .-'               -  /'( >~" << endl;
        cout << "                     . .'                    (_.-'" << endl;
        cout << "                       v" << endl;
        cout << "" << endl;
        cout << "" << endl;
        cout << "" << endl;
        cout << "========== Option ==========" << endl << endl;
        if (!isLoggedIn) { //not logged in //!isLoggedIn = true !=flips the boolean value
            cout << "1. View Beauty Centre Information\n";
            cout << "2. View Services and Experts\n";
            cout << "3. Check Appointment Availability\n";
            cout << "4. Login for Booking and View Booking\n";
            cout << "5. Back to Main Menu\n" << endl;
            cout << "Enter your choice : ";
            cin >> menuoption;
            if (menuoption != "1" && menuoption != "2" && menuoption != "3" &&
                menuoption != "4" && menuoption != "5") {
                cout << "Invalid input! Please enter 1/2/3/4/5.\n\n";
            }
        }
        else {
            cout << "1. View Beauty Centre Information\n";
            cout << "2. View Services and Experts\n";
            cout << "3. Check Appointment Availability\n";
            cout << "4. Book a Service\n";
            cout << "5. View My Bookings\n";
            cout << "6. Logout\n" << endl;
            cout << "Enter your choice : ";
            cin >> menuoption;
            if (menuoption != "1" && menuoption != "2" && menuoption != "3" &&
                menuoption != "4" && menuoption != "5" && menuoption != "6") {
                cout << "Invalid input! Please enter 1/2/3/4/5/6.\n\n";
            }
        }

    } while ((!isLoggedIn &&
        menuoption != "1" && menuoption != "2" && menuoption != "3" &&
        menuoption != "4" && menuoption != "5") ||
        (isLoggedIn &&
            menuoption != "1" && menuoption != "2" && menuoption != "3" &&
            menuoption != "4" && menuoption != "5" && menuoption != "6"));
    return menuoption;
}

void ROSELLE() {
    cout << endl;
    cout << "========== About ROSELLE ==========" << endl;
    cout << "" << endl;
    cout << "At Roselle, our vision is to be the most trusted and sought-after bridal beauty service, helping every bride feel \nconfident, radiant, and truly beautiful on one of the most important days of her life." << endl;
    cout << "" << endl;
    cout << "Our mission at Roselle is to provide high-quality, personalized beauty services that enhance each bride's natural \nbeauty. We are dedicated to creating a calm, professional, and enjoyable experience from the first consultation to the \nfinal touch-up, making every moment special." << endl;
    cout << "" << endl;
    cout << "Operating hours (Monday - Friday) : 10am - 7pm." << endl;
    cout << "Contact number : 018-6739021" << endl;
    cout << "Address : 22, Jalan Roselle, Kota Tinggi, 42000, Kuala Lumpur, Malaysia";
    cout << "" << endl;
    string confirm;
    cout << "\nPress any letter to back to customer menu : ";
    cin >> confirm;
    return;
}

void viewServicesandExperts() {
    cout << "========== Services & Experts ==========" << endl;
    cout << "" << endl;
    cout << "========================================" << endl;
    cout << "             Make Up Service            " << endl;
    cout << "========================================" << endl;
    cout << left << setw(40) << setfill('-') << "1. Allice Tan (Senior) " << "RM 400" << endl;
    cout << left << setw(40) << setfill('-') << "2. Bella Lim (Junior) " << "RM 300" << endl;
    cout << left << setw(40) << setfill('-') << "3. Chloe Ong (Bridal Specialist)" << "RM 500" << endl << endl;
    cout << "========================================" << endl;
    cout << "            Pre-wedding Service         " << endl;
    cout << "========================================" << endl;
    cout << left << setw(40) << setfill('-') << "1. Allice Tan (Senior) " << "RM 1200" << endl;
    cout << left << setw(40) << setfill('-') << "2. Bella Lim (Junior) " << "RM 1500" << endl;
    cout << left << setw(40) << setfill('-') << "3. Chloe Ong (Bridal Specialist)" << "RM 1800" << endl << endl;
    cout << "========================================" << endl;
    cout << "           Hair Styling Service         " << endl;
    cout << "========================================" << endl;
    cout << left << setw(40) << setfill('-') << "1. Allice Tan (Senior) " << "RM 250" << endl;
    cout << left << setw(40) << setfill('-') << "2. Bella Lim (Junior) " << "RM 300" << endl;
    cout << left << setw(40) << setfill('-') << "3. Chloe Ong (Bridal Specialist)" << "RM 350" << endl << endl;
    cout << "========================================================" << endl;
    cout << "            Bridesmaid & family makeup service          " << endl;
    cout << "========================================================" << endl;
    cout << left << setw(45) << setfill('-') << "1. Allice Tan (Senior) " << "RM 750" << endl;
    cout << left << setw(45) << setfill('-') << "2. Bella Lim (Junior) " << "RM 600" << endl;
    cout << left << setw(45) << setfill('-') << "3. Chloe Ong (Bridal Specialist)" << "RM 700" << endl << endl;
    cout << "=============================================================" << endl;
    cout << "          Nail care service (manicure & pedicure)            " << endl;
    cout << "=============================================================" << endl;
    cout << left << setw(45) << setfill('-') << "1. Allice Tan (Senior) " << "RM 380" << endl;
    cout << left << setw(45) << setfill('-') << "2. Bella Lim (Junior) " << "RM 300" << endl;
    cout << left << setw(45) << setfill('-') << "3. Chloe Ong (Bridal Specialist)" << "RM 350" << endl << endl;
    string confirm;
    cout << "\nPress any letter to back to customer menu : ";
    cin >> confirm;
    return;
}

void bookingServicesandExperts() {
    //view appointment function
    int day;

    while (true) {
        showCalendar();
        cout << "\nEnter the day of December to book (1-31): ";
        cin >> day;

        if (cin.fail() || day < 1 || day > TOTAL_DAYS) {
            cin.clear(); cin.ignore(1000, '\n');
            cout << "Invalid day. Try again.\n";
            continue;
        }

        int dayOfWeek = getDayOfWeek(day);
        if (dayOfWeek >= 6) {
            cout << "Weekends closed.\n";
            continue;
        }

        int bookedCount = 0; // how many slots on that day already booked
        for (int slot = 1; slot <= SLOTS_PER_DAY; ++slot) {
            bool slotBooked = false; // assume free until we check all experts

            // Check all experts for this day and slot
            for (int expert = 0; expert < TOTAL_EXPERTS; expert++) {
                if (bookings[expert][day][slot]) {
                    slotBooked = true; // if any experts is booked, slotBooked becomes true
                    break; // no need to check remaining experts
                }
            }

            if (slotBooked) { //check whether slotBooked is true or not, slotBooked is true means is this slot is taken
                bookedCount++; // increase the count of booked slots
            }
        }

        if (bookedCount == SLOTS_PER_DAY) {
            cout << "That day is fully booked.\n";
            continue;
        }
        break;
    }

    cout << "\n=== Slots for " << day << " December 2025 ===\n";

    for (int s = 1; s <= SLOTS_PER_DAY; s++) {
        bool slotBooked = false;

        // Check all experts for this day and slot
        for (int expert = 0; expert < TOTAL_EXPERTS; expert++) {
            if (bookings[expert][day][s]) {
                slotBooked = true;
                break; // no need to check other experts
            }
        }

        if (slotBooked) { // check whether slotBooked is true or not, slotBooked = true, print [booked]
            cout << s << ". " << slotTimes[s] << " [BOOKED]\n";
        }
        else { // slotBooked = false
            cout << s << ". " << slotTimes[s] << " [AVAILABLE]\n";
        }
    }
    int slot;
    while (true) {
        cout << "\nChoose your preferred slot (1-3): ";
        cin >> slot;
        if (cin.fail()) { // user typed letters or symbols
            cin.clear(); // clear the error state
            cin.ignore(1000, '\n'); // throw away the wrong input
            cout << "Invalid input! Please enter numbers only.\n";
            continue; // go back to the top of the loop
        }

        if (slot < 1 || slot > 3) {
            cout << "Invalid slot. Choose 1, 2, or 3.\n";
            continue;
        }
        // Check if slot already taken by any expert
        bool slotTaken = false;
        for (int expert = 0; expert < TOTAL_EXPERTS; expert++) {
            if (bookings[expert][day][slot]) {
                slotTaken = true;
                break;
            }
        }

        if (slotTaken) {
            cout << "Sorry, slot " << slot << " is already fully booked for day " << day << ".\n";
            continue; // re-prompt
        }
        break;
    }
    cout << endl;
    cout << "========== Services ==========" << endl;
    for (int s = 0; s < 5; s++) {
        cout << s + 1 << ". " // prints numbering starting from 1
            << services[s].serviceName << endl;
    }
    cout << endl;

    while (true) {
        int serviceOption;
        cout << "Choose a service (1-5): ";
        cin >> serviceOption;
        cout << endl;
        if (cin.fail()) { // user typed letters or symbols
            cin.clear(); // clear the error state
            cin.ignore(1000, '\n'); // throw away the wrong input
            cout << "Invalid input! Please enter numbers only.\n";
            continue; // go back to the top of the loop
        }

        if (serviceOption < 1 || serviceOption > 5) {
            cout << "Invalid service option. Please choose again!" << endl;
            continue;
        }

        int serviceIndex = serviceOption - 1;
        cout << "========== Experts ==========" << endl;
        for (int j = 0; j < 3; j++) {
            cout << (j + 1) << ". " << services[serviceIndex].experts[j].name
                << "    RM " << services[serviceIndex].experts[j].price << endl;
        }

        while (true) {
            int expertOption;
            cout << "\nEnter your preferred expert (1-3) to view available time slot: ";
            cin >> expertOption;
            cout << endl;

            if (cin.fail()) { // user typed letters or symbols
                cin.clear(); // clear the error state
                cin.ignore(1000, '\n'); // throw away the wrong input
                cout << "Invalid input! Please enter numbers only.\n";
                continue; // go back to the top of the loop
            }

            if (expertOption < 1 || expertOption > 3) {
                cout << "Invalid expert option. Please choose again!" << endl;
                continue;
            }

            int expertIndex = expertOption - 1;
            const Expertdetails& chosenExpert = services[serviceIndex].experts[expertIndex]; // reference to the selected expert for the chosen service.

            bookSlot(chosenExpert.name, services[serviceIndex].serviceName, chosenExpert.price, chosenExpert.expertID, day, slot);
            break; // Exit expert selection loop
        }
        break; // Exit service selection loop
    }
}

string mainmenu() {
    string mainmenuoption;
    do {
        cout << endl;
        cout << "===========================" << endl;
        cout << "     WELCOME TO ROSELLE" << endl;
        cout << "===========================" << endl;
        cout << endl;
        cout << "1. Customer " << endl;
        cout << "2. Experts" << endl;
        cout << "3. Admin" << endl;
        cout << "4. Exiting Program" << endl << endl;
        cout << "Enter your choice : ";
        cin >> mainmenuoption;
        if (cin.fail()) { // user typed letters or symbols
            cin.clear(); // clear the error state
            cin.ignore(1000, '\n'); // throw away the wrong input
            cout << "Invalid input! Please enter numbers only.\n";
            continue; // go back to the top of the loop
        }

        if (mainmenuoption != "1" && mainmenuoption != "2" && mainmenuoption != "3" && mainmenuoption != "4") {
            cout << endl << "Invalid input! Please enter 1/2/3/4." << endl;
        }
    } while (mainmenuoption != "1" && mainmenuoption != "2" && mainmenuoption != "3" && mainmenuoption != "4");
    return mainmenuoption;
}

int loginExpert();
int forgetpassword(int expertID);
void viewSchedule(int);
void viewAssignedCustomers(int);
void viewBonus(int);


int forgetpassword(int expertID) {
    string input;
    int choice;

    while (true) {
        cout << "\nSelect a number to continue." << endl;
        cout << "1. Try Again" << endl;
        cout << "2. Forgot Password" << endl;
        cout << "Enter your choice: ";
        cin >> input;

        bool isNumber = true;
        for (char c : input) {
            if (!isdigit(c)) {
                isNumber = false;
                break;
            }
        }
        if (!isNumber) {
            cout << "\nInvalid input! Please enter 1 or 2." << endl;
            continue;
        }

        choice = stoi(input);

        if (choice == 1) {
            return loginExpert();
        }
        else if (choice == 2) {
            // search all services to find matching expertID
            for (int si = 0; si < 5; si++) {
                for (int ej = 0; ej < 3; ej++) {
                    if (services[si].experts[ej].expertID == expertID) {
                        cout << "\nYour password is: "
                            << services[si].experts[ej].password << endl;
                        return loginExpert();
                    }
                }
            }
            cout << "\nExpert not found." << endl;
            return loginExpert();
        }
        else {
            cout << "\nThe number is not in range! Please enter 1 or 2." << endl;
        }
    }
}

int loginExpert() {
    string inputName, inputPassword;
    cout << "\n=== Expert Login ===\n";

    cout << "Enter Expert Name: ";
    getline(cin >> ws, inputName); // allows spaces

    cout << "Enter Password: ";
    cin >> inputPassword;

    // loop through all services and all experts
    for (int si = 0; si < 5; si++) {
        for (int ej = 0; ej < 3; ej++) {
            if (services[si].experts[ej].name == inputName &&
                services[si].experts[ej].password == inputPassword) {
                cout << "\nLogin successful. Welcome, "
                    << services[si].experts[ej].name << "!" << endl;
                return services[si].experts[ej].expertID; // return unique ID
            }
            else if (services[si].experts[ej].name == inputName &&
                services[si].experts[ej].password != inputPassword) {
                cout << "\nThe password is incorrect." << endl;
                return forgetpassword(services[si].experts[ej].expertID);
            }
        }
    }

    cout << "\nLogin failed. Invalid name and password." << endl;
    return loginExpert(); // retry
}


void viewSchedule(int expertIndex) {
    for (int si = 0; si < 5; si++) {
        for (int ej = 0; ej < 3; ej++) {
            if (services[si].experts[ej].expertID == expertIndex) {
                cout << "~~ Schedule for " << services[si].experts[ej].name << " ~~" << endl << endl;

                string weeks[5][5] = {
                    {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"},
                    {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"},
                    {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"},
                    {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"},
                    {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"}
                };
                int weekStartDay[6] = { 0, 1, 8, 15, 22, 29 };

                while (true) {
                    string weekss;
                    cout << "Which week you want to view (1-5) : ";
                    cin >> weekss;

                    bool valid = true;
                    for (char c : weekss) {
                        if (!isdigit(c)) { valid = false; break; }
                    }
                    if (!valid) {
                        cout << "Invalid input! Please enter a number between 1 and 5.\n";
                        continue;
                    }

                    int week = stoi(weekss);
                    if (week < 1 || week > 5) {
                        cout << "\nPlease number in range 1 to 5!!" << endl;
                        continue;
                    }

                    bool found = false;
                    int totalHours = 0;

                    cout << "\nExpert Schedule ~ " << services[si].experts[ej].name
                        << " (week " << week << "):" << endl << endl;
                    cout << string(130, '=') << endl;
                    cout << left << setw(13) << "Date" << setw(12) << "Day"
                        << setw(25) << "Time Slot" << setw(40) << "Service" << setw(30) << "Customer" << endl;
                    cout << string(130, '=') << endl << endl;

                    // 找记录
                    for (int e = 0; e < TOTAL_EXPERTS; e++) {
                        for (int d = 1; d <= TOTAL_DAYS; d++) {
                            for (int s = 1; s <= SLOTS_PER_DAY; s++) {
                                if (bookingDetails[e][d][s].isBooked && bookingDetails[e][d][s].expertID == expertIndex) {
                                    int dayNumber = bookingDetails[e][d][s].day;
                                    int weekDay = getDayOfWeek(dayNumber);
                                    string dayNames[] = { "", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };

                                    // week-1 是因为数组从 0 开始
                                    if (dayNames[weekDay] == weeks[week - 1][weekDay - 1] &&
                                        dayNumber >= weekStartDay[week] &&
                                        dayNumber < weekStartDay[week] + 7)
                                    {
                                        found = true;
                                        string date = "Dec " + to_string(dayNumber);
                                        cout << left << setw(13) << date
                                            << setw(12) << dayNames[weekDay]
                                            << setw(25) << slotTimes[bookingDetails[e][d][s].slot]
                                            << setw(40) << bookingDetails[e][d][s].serviceName
                                            << setw(30) << bookingDetails[e][d][s].username << endl;
                                        totalHours += 2;
                                    }
                                }
                            }
                        }
                    }

                    if (!found) {
                        cout << "(No records found for this week)" << endl;
                    }

                    cout << endl << string(115, '-') << endl << endl;
                    cout << "\nTotal Hours Worked For This Week: " << totalHours << " hrs" << endl;
                    cout << "Remaining Hours For This Week: " << (30 - totalHours) << " hrs (Limit: 30 hrs)" << endl;

                    string choice;
                    while (true) {
                        cout << "\nDo you want to view another week? (Y/N): ";
                        cin >> choice;
                        for (auto& ch : choice) ch = toupper(ch);

                        if (choice == "Y") break;
                        else if (choice == "N") return;
                        else cout << "Invalid input! Please enter Y or N only.\n";
                    }
                }
            }
        }
    }
}


int getTotalBookingsExpert(int expertIndex) {
    int count = 0;
    for (int expert = 0; expert < TOTAL_EXPERTS; expert++) {
        for (int day = 1; day <= TOTAL_DAYS; day++) {
            for (int slot = 1; slot <= SLOTS_PER_DAY; slot++) {
                if (bookingDetails[expert][day][slot].isBooked && bookingDetails[expert][day][slot].expertID == expertIndex) {
                    count++;
                }
            }
        }

    }



    return count;
}

void viewAssignedCustomers(int expertIndex) {


    int list = 1;
    bool found = false;

    // 表头只打印一次
    for (int e = 0; e < TOTAL_EXPERTS; e++) {
        for (int d = 1; d <= TOTAL_DAYS; d++) {
            for (int s = 1; s <= SLOTS_PER_DAY; s++) {
                if (bookingDetails[e][d][s].isBooked &&
                    bookingDetails[e][d][s].expertID == expertIndex) {

                    if (!found) { // 第一次找到才打印表头
                        cout << "\n~~ Assigned Customers for "
                            << bookingDetails[e][d][s].expertName << " ~~" << endl << endl;
                        cout << left << setw(6) << "No."
                            << setw(15) << "Customer Name"
                            << setw(20) << "Service" << endl;
                        cout << string(35, '-') << endl;
                        found = true;
                    }

                    string list_no = to_string(list) + ".";
                    cout << left << setw(6) << list_no
                        << setw(15) << bookingDetails[e][d][s].username
                        << setw(20) << bookingDetails[e][d][s].serviceName << endl;

                    list++;
                }
            }
        }
    }

    if (!found) {
        cout << "No assigned customers yet." << endl;
    }

    cout << "\nNumber of Customers : " << list - 1 << endl;



}
void viewBonus(int expertIndex) {
    int choose, real_choose, bonus_percentage;
    string resultBonusPercentage;

    double bonus_earned = 0, services_charges = 0, Hours_complete = 0;

    for (int e = 0; e < TOTAL_EXPERTS; e++) {
        for (int d = 1; d <= TOTAL_DAYS; d++) {
            for (int s = 1; s <= SLOTS_PER_DAY; s++) {
                if (bookingDetails[e][d][s].isBooked &&
                    bookingDetails[e][d][s].expertID == expertIndex) {
                    services_charges += bookingDetails[e][d][s].totalAmount;


                }
            }
        }
    }
    int bookingCount = getTotalBookingsExpert(expertIndex);
    Hours_complete = bookingCount * 2;

    if (Hours_complete >= 30) {
        bonus_percentage = 50;
        resultBonusPercentage = "50%";
        bonus_earned = services_charges * 0.5;
    }
    else if (Hours_complete >= 25 && Hours_complete < 30) {
        bonus_percentage = 25;
        resultBonusPercentage = "25%";
        bonus_earned = services_charges * 0.25;
    }
    else if (Hours_complete < 25) {
        bonus_percentage = 0;
        resultBonusPercentage = "0%";
        bonus_earned = services_charges * 0;

    }
    cout << setw(34) << "Expert Bonus Report  -  December" << endl;
    cout << "-------------------------------------------------------------------------------------" << endl;
    cout << "   Total Hours Completed   Total Service Charges   Bonus Percentage   Bonus Earned" << endl;
    cout << "-------------------------------------------------------------------------------------" << endl;
    cout << setw(24) << Hours_complete << setw(24) << services_charges << setw(19) << resultBonusPercentage << setw(15) << bonus_earned << endl;


}




/*这里开始我们的admin page functions*/
/*这个是viewIndividualExpertSchedule*/

void viewIndividualExpertSchedule() {
    cout << "\n=====  View Individual Expert Schedule =====\n";
    cout << "Available Experts:\n";
    cout << "1. Allice Tan (Senior)\n";
    cout << "2. Bella Lim (Junior)\n";
    cout << "3. Chloe Ong (Bridal Specialist)\n";

    int choice;
    cout << "Select an expert (1-3): ";
    cin >> choice;

    // Clear input buffer to prevent issues
    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << " Invalid input! Please enter a number.\n";
        return;
    }

    if (choice < 1 || choice > 3) {
        cout << " Invalid choice!\n";
        return;
    }

    // Get expert name based on choice
    string expertName;
    int expertID = choice - 1; // Convert to 0-based index

    if (choice == 1) expertName = "Allice Tan (Senior)";
    else if (choice == 2) expertName = "Bella Lim (Junior)";
    else if (choice == 3) expertName = "Chloe Ong (Bridal Specialist)";

    cout << "\n Schedule for " << expertName << ":\n";
    cout << "========================================================================\n";
    cout << left << setw(12) << "Date" << setw(20) << "Time"
        << setw(30) << "Service" << setw(15) << "Customer" << endl;
    cout << "------------------------------------------------------------------------\n";

    bool found = false;
    int totalHours = 0;
    int totalSessions = 0;

    // Loop through all bookings for this expert
    for (int d = 1; d <= TOTAL_DAYS; d++) {
        for (int s = 1; s <= SLOTS_PER_DAY; s++) {
            if (bookingDetails[expertID][d][s].isBooked &&
                bookingDetails[expertID][d][s].expertName == expertName) {

                found = true;
                totalSessions++;
                totalHours += 2; // Each slot is 2 hours

                string date = "Dec " + to_string(d);
                cout << left << setw(12) << date
                    << setw(20) << slotTimes[s]
                    << setw(30) << bookingDetails[expertID][d][s].serviceName
                    << setw(15) << bookingDetails[expertID][d][s].username << endl;
            }
        }
    }

    if (!found) {
        cout << "No bookings found for this expert.\n";
    }
    else {
        cout << "------------------------------------------------------------------------\n";
        cout << "Total Sessions: " << totalSessions << "\n";
        cout << "Total Hours: " << totalHours << " hrs\n";
    }
    cout << "========================================================================\n";

    // Ensure proper return to admin menu
    return;
}


/*这个是view overall schedule*/
void viewOverallSchedule() {
    cout << "\n=====  Overall Expert Schedule =====\n";
    cout << "Combined schedule of all experts for December 2025\n";
    cout << "===================================================================================\n";
    cout << left << setw(12) << "Date" << setw(20) << "Time"
        << setw(25) << "Expert" << setw(25) << "Service" << setw(15) << "Customer" << endl;
    cout << "-----------------------------------------------------------------------------------\n";

    bool found = false;
    int totalBookings = 0;

    // Arrays to track each expert's hours
    int expertHours[3] = { 0, 0, 0 };
    string expertNames[3] = { "Allice Tan (Senior)", "Bella Lim (Junior)", "Chloe Ong (Bridal Specialist)" };

    // Loop through all days and slots
    for (int d = 1; d <= TOTAL_DAYS; d++) {
        for (int s = 1; s <= SLOTS_PER_DAY; s++) {
            // Check all experts for this day and slot
            for (int e = 0; e < TOTAL_EXPERTS; e++) {
                if (bookingDetails[e][d][s].isBooked) {
                    found = true;
                    totalBookings++;
                    expertHours[e] += 2; // Each slot is 2 hours

                    string date = "Dec " + to_string(d);
                    cout << left << setw(12) << date
                        << setw(20) << slotTimes[s]
                        << setw(25) << bookingDetails[e][d][s].expertName
                        << setw(25) << bookingDetails[e][d][s].serviceName
                        << setw(15) << bookingDetails[e][d][s].username << endl;
                }
            }
        }
    }

    if (!found) {
        cout << "No bookings found in the system.\n";
    }
    else {
        cout << "-----------------------------------------------------------------------------------\n";
        cout << "\n=== Workload Distribution Summary ===\n";
        for (int i = 0; i < 3; i++) {
            cout << expertNames[i] << ": " << expertHours[i] << " hours\n";
        }
        cout << "\nTotal Bookings: " << totalBookings << "\n";
        cout << "Total Working Hours: " << (expertHours[0] + expertHours[1] + expertHours[2]) << " hours\n";
    }
    cout << "===================================================================================\n";
}


/*这个是view customer list*/
void viewCustomerList() {
    bool hasRecord = false;
    int selection, realrange;
    string targetUser, servicesname, expertname, customername;
    char searchYN, lowersearchYN;
    cout << "\nAll Registered Customers : " << endl;
    cout << "---------------------------------------------------------------------------" << endl;
    cout << left << setw(20) << "Name" << " | " << left << setw(20) << "Service Booked" << " | " << left << setw(20) << "Assigned Expert" << endl;
    cout << "---------------------------------------------------------------------------" << endl;



    for (int i = 0; i < MAX_CUSTOMERS; i++) {

        targetUser = customers[i].username;
        for (int e = 0; e < TOTAL_EXPERTS; e++) {
            for (int d = 0; d < TOTAL_DAYS; d++) {
                for (int s = 0; s < SLOTS_PER_DAY; s++) {
                    servicesname = bookingDetails[e][d][s].serviceName;
                    expertname = bookingDetails[e][d][s].expertName;
                    if (bookingDetails[e][d][s].isBooked && bookingDetails[e][d][s].username == targetUser) {
                        cout << left << setw(20) << bookingDetails[e][d][s].username
                            << " | " << left << setw(20) << servicesname
                            << " | " << left << setw(20) << expertname << endl;

                        hasRecord = true;
                    }
                }
            }
        }
    }
    if (!hasRecord) {
        cout << "No customer records found." << endl;
    }
}


/*这个是view generate sales report*/
void generateSalesReport() {
    int filterChoice;

    cout << "\n===== 📈 Generate Sales Report =====\n";
    cout << "1. View by Date Range (Day 1-31)\n";
    cout << "2. View by Service Category\n";
    cout << "3. View by Expert\n";
    cout << "4. View All Data\n";
    cout << "Choose option: ";
    cin >> filterChoice;

    double totalSales = 0.0;
    int makeupServices = 0, preweddingServices = 0, hairstylingServices = 0,
        bridesmaidServices = 0, nailcareServices = 0;

    // Add individual sales tracking
    double makeupSales = 0, preweddingSales = 0, hairstylingSales = 0,
        bridesmaidSales = 0, nailcareSales = 0;

    if (filterChoice == 1) {
        int startDay, endDay;
        cout << "Enter start day (1-31): ";
        cin >> startDay;
        cout << "Enter end day (1-31): ";
        cin >> endDay;

        if (startDay < 1 || startDay > 31 || endDay < 1 || endDay > 31 || startDay > endDay) {
            cout << "Invalid date range!\n";
            return;
        }

        // Loop through actual booking data
        for (int e = 0; e < TOTAL_EXPERTS; e++) {
            for (int d = startDay; d <= endDay; d++) {
                for (int s = 1; s <= SLOTS_PER_DAY; s++) {
                    if (bookingDetails[e][d][s].isBooked) {
                        totalSales += bookingDetails[e][d][s].totalAmount;

                        // Count service types AND track individual sales
                        if (bookingDetails[e][d][s].serviceName == "Make Up Service") {
                            makeupServices++;
                            makeupSales += bookingDetails[e][d][s].totalAmount;
                        }
                        else if (bookingDetails[e][d][s].serviceName == "Pre-wedding service") {
                            preweddingServices++;
                            preweddingSales += bookingDetails[e][d][s].totalAmount;
                        }
                        else if (bookingDetails[e][d][s].serviceName == "Hair Styling service") {
                            hairstylingServices++;
                            hairstylingSales += bookingDetails[e][d][s].totalAmount;
                        }
                        else if (bookingDetails[e][d][s].serviceName == "Bridesmaid & family makeup service") {
                            bridesmaidServices++;
                            bridesmaidSales += bookingDetails[e][d][s].totalAmount;
                        }
                        else if (bookingDetails[e][d][s].serviceName == "Nail care service (manicure & pedicure)") {
                            nailcareServices++;
                            nailcareSales += bookingDetails[e][d][s].totalAmount;
                        }
                    }
                }
            }
        }
    }
    else if (filterChoice == 2) {
        string category;
        cout << "\nAvailable Service Categories:\n";
        cout << "1. Make Up Service\n";
        cout << "2. Pre-wedding service\n";
        cout << "3. Hair Styling service\n";
        cout << "4. Bridesmaid & family makeup service\n";
        cout << "5. Nail care service (manicure & pedicure)\n";
        cout << "Enter service name: ";
        cin.ignore();
        getline(cin, category);

        for (int e = 0; e < TOTAL_EXPERTS; e++) {
            for (int d = 1; d <= TOTAL_DAYS; d++) {
                for (int s = 1; s <= SLOTS_PER_DAY; s++) {
                    if (bookingDetails[e][d][s].isBooked &&
                        bookingDetails[e][d][s].serviceName == category) {
                        totalSales += bookingDetails[e][d][s].totalAmount;

                        // Count the specific category AND track sales
                        if (category == "Make Up Service") {
                            makeupServices++;
                            makeupSales += bookingDetails[e][d][s].totalAmount;
                        }
                        else if (category == "Pre-wedding service") {
                            preweddingServices++;
                            preweddingSales += bookingDetails[e][d][s].totalAmount;
                        }
                        else if (category == "Hair Styling service") {
                            hairstylingServices++;
                            hairstylingSales += bookingDetails[e][d][s].totalAmount;
                        }
                        else if (category == "Bridesmaid & family makeup service") {
                            bridesmaidServices++;
                            bridesmaidSales += bookingDetails[e][d][s].totalAmount;
                        }
                        else if (category == "Nail care service (manicure & pedicure)") {
                            nailcareServices++;
                            nailcareSales += bookingDetails[e][d][s].totalAmount;
                        }
                    }
                }
            }
        }
    }
    else if (filterChoice == 3) {
        string expert;
        cout << "\nAvailable Experts:\n";
        cout << "1. Allice Tan (Senior)\n";
        cout << "2. Bella Lim (Junior)\n";
        cout << "3. Chloe Ong (Bridal Specialist)\n";
        cout << "Enter expert name: ";
        cin.ignore();
        getline(cin, expert);

        for (int e = 0; e < TOTAL_EXPERTS; e++) {
            for (int d = 1; d <= TOTAL_DAYS; d++) {
                for (int s = 1; s <= SLOTS_PER_DAY; s++) {
                    if (bookingDetails[e][d][s].isBooked &&
                        bookingDetails[e][d][s].expertName == expert) {
                        totalSales += bookingDetails[e][d][s].totalAmount;

                        // Count service types for this expert AND track sales
                        if (bookingDetails[e][d][s].serviceName == "Make Up Service") {
                            makeupServices++;
                            makeupSales += bookingDetails[e][d][s].totalAmount;
                        }
                        else if (bookingDetails[e][d][s].serviceName == "Pre-wedding service") {
                            preweddingServices++;
                            preweddingSales += bookingDetails[e][d][s].totalAmount;
                        }
                        else if (bookingDetails[e][d][s].serviceName == "Hair Styling service") {
                            hairstylingServices++;
                            hairstylingSales += bookingDetails[e][d][s].totalAmount;
                        }
                        else if (bookingDetails[e][d][s].serviceName == "Bridesmaid & family makeup service") {
                            bridesmaidServices++;
                            bridesmaidSales += bookingDetails[e][d][s].totalAmount;
                        }
                        else if (bookingDetails[e][d][s].serviceName == "Nail care service (manicure & pedicure)") {
                            nailcareServices++;
                            nailcareSales += bookingDetails[e][d][s].totalAmount;
                        }
                    }
                }
            }
        }
    }
    else if (filterChoice == 4) {
        // Show all data (Days 1-31)
        for (int e = 0; e < TOTAL_EXPERTS; e++) {
            for (int d = 1; d <= TOTAL_DAYS; d++) {
                for (int s = 1; s <= SLOTS_PER_DAY; s++) {
                    if (bookingDetails[e][d][s].isBooked) {
                        totalSales += bookingDetails[e][d][s].totalAmount;

                        if (bookingDetails[e][d][s].serviceName == "Make Up Service") {
                            makeupServices++;
                            makeupSales += bookingDetails[e][d][s].totalAmount;
                        }
                        else if (bookingDetails[e][d][s].serviceName == "Pre-wedding service") {
                            preweddingServices++;
                            preweddingSales += bookingDetails[e][d][s].totalAmount;
                        }
                        else if (bookingDetails[e][d][s].serviceName == "Hair Styling service") {
                            hairstylingServices++;
                            hairstylingSales += bookingDetails[e][d][s].totalAmount;
                        }
                        else if (bookingDetails[e][d][s].serviceName == "Bridesmaid & family makeup service") {
                            bridesmaidServices++;
                            bridesmaidSales += bookingDetails[e][d][s].totalAmount;
                        }
                        else if (bookingDetails[e][d][s].serviceName == "Nail care service (manicure & pedicure)") {
                            nailcareServices++;
                            nailcareSales += bookingDetails[e][d][s].totalAmount;
                        }
                    }
                }
            }
        }
    }
    else {
        cout << "⚠ Invalid option!\n";
        return;
    }

    // Professional Sales Report - Matching your example format
    cout << "\nSales Report - December 2025\n\n";
    cout << left << setw(25) << "Service Type"
        << setw(20) << "Total Bookings"
        << setw(20) << "Total Sales (RM)" << endl;
    cout << string(65, '-') << "\n";

    // Display data with proper formatting
    cout << fixed << setprecision(0); // No decimal places for whole numbers

    if (makeupServices > 0) {
        cout << left << setw(25) << "Make Up Service"
            << setw(20) << makeupServices
            << "RM" << (int)makeupSales << endl;
    }
    if (preweddingServices > 0) {
        cout << left << setw(25) << "Pre-wedding Service"
            << setw(20) << preweddingServices
            << "RM" << (int)preweddingSales << endl;
    }
    if (hairstylingServices > 0) {
        cout << left << setw(25) << "Hair Styling Service"
            << setw(20) << hairstylingServices
            << "RM" << (int)hairstylingSales << endl;
    }
    if (bridesmaidServices > 0) {
        cout << left << setw(25) << "Bridesmaid Service"
            << setw(20) << bridesmaidServices
            << "RM" << (int)bridesmaidSales << endl;
    }
    if (nailcareServices > 0) {
        cout << left << setw(25) << "Nail Care Service"
            << setw(20) << nailcareServices
            << "RM" << (int)nailcareSales << endl;
    }

    cout << "\nTotal Revenue: RM" << (int)totalSales << endl;

    return;
}




/*这个是view expert bonus*/
// Replace the declaration and initialization of expertamount, expertslot, bonus_earned, etc. at the top of viewExpertBonus() with the following:
void viewExpertBonus() {
    bool found = false;
    cout << setw(34) << "Expert Bonus Report  -  December" << endl;
    cout << "--------------------------------------------------------------------------------------------------------------" << endl;
    cout << setw(24) << "Expert Name" << "|" << setw(24) << "Total Hours Completed" << "|" << setw(24) << "Total Service Charges" << "|" << setw(24) << "Bonus Percentage" << "|" << setw(24) << "Bonus Earned" << endl;
    cout << "--------------------------------------------------------------------------------------------------------------" << endl;

    for (int e = 0; e <= TOTAL_EXPERTS; e++) {
        string expertname = "";
        double expertamount = 0.0;
        string resultBonusPercentage = "0%";
        double bonus_earned = 0.0;
        int expertslot = 0;
        for (int d = 0; d <= TOTAL_DAYS; d++) {
            for (int s = 0; s <= SLOTS_PER_DAY; s++) {
                if (bookingDetails[e][d][s].isBooked) {
                    expertname = bookingDetails[e][d][s].expertName;
                    expertslot += 2;
                    expertamount += bookingDetails[e][d][s].totalAmount;
                    found = true; // Found at least one booking for this expert    
                }
            }
        }
        if (expertslot == 0 && expertamount == 0)continue;//expert no information will direct past  
        if (expertslot >= 30) {
            resultBonusPercentage = "50%";
            bonus_earned = expertamount * 0.5;
        }
        else if (expertslot >= 25) {
            resultBonusPercentage = "25%";
            bonus_earned = expertamount * 0.25;
        }
        else {
            resultBonusPercentage = "0%";
            bonus_earned = 0;
        }
        cout << setw(24) << expertname << "|" << setw(24) << expertslot << "|" << setw(24) << expertamount << "|" << setw(24) << resultBonusPercentage << "|" << setw(24) << bonus_earned << endl;


    }
    if (!found) {
        cout << "No expert bonus records found." << endl;
    }
}






int main() {
    bool isLoggedIn = false;
    string customermenuoption, mainmenuoption;
    do {
        mainmenuoption = mainmenu();
        if (mainmenuoption == "1") {

            do {
                customermenuoption = showCustomerMenu(isLoggedIn); // return option to the function

                if (!isLoggedIn) {
                    if (customermenuoption == "1") {
                        ROSELLE();
                    }
                    else if (customermenuoption == "2") {
                        viewServicesandExperts();
                    }
                    else if (customermenuoption == "3") {
                        appointmentAvailability();
                    }
                    else if (customermenuoption == "4") {
                        if (customerlogin()) {
                            isLoggedIn = true;
                            cout << endl << "Login successful.\n";
                            string confirm;
                            cout << "\nPress any letter to back to customer menu : ";
                            cin >> confirm;
                        }
                        else {
                            cout << endl << "Login failed. Incorect Username or Password\n";
                        }
                    }
                    else if (customermenuoption == "5") {
                        break;
                    }
                }
                else { // Logged-in menu
                    if (customermenuoption == "1") {
                        ROSELLE();
                    }
                    else if (customermenuoption == "2") {
                        viewServicesandExperts();
                    }
                    else if (customermenuoption == "3") {
                        appointmentAvailability();
                    }
                    else if (customermenuoption == "4") {
                        bookingServicesandExperts();
                    }
                    else if (customermenuoption == "5") {
                        viewMyBookings();
                    }
                    else if (customermenuoption == "6") {
                        isLoggedIn = false;
                        cout << endl << "Logged out successfully.\n";
                        string confirm;
                        cout << "\nPress any letter to back to customer menu : ";
                        cin >> confirm;
                    }
                }
            } while (true);
        }

        else if (mainmenuoption == "2") {
            int expertIndex = loginExpert();
            string input;
            int choice;

            while (true) { // 一直循环
                cout << "\n=== Expert Dashboard ===" << endl;
                cout << "1. View My Schedule" << endl;
                cout << "2. View Assigned Customers" << endl;
                cout << "3. View Bonus Entitlement" << endl;
                cout << "4. Logout" << endl;
                cout << "Enter your choice: ";
                cin >> input;

                bool valid = true;
                for (char c : input) {
                    if (!isdigit(c)) {
                        valid = false;
                        break; //退出循环
                    }
                }

                if (!valid) {
                    cout << "Invalid input! Please enter a number between 1 and 4.\n";
                    continue;
                }

                choice = stoi(input); // convert int

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
                    return main();
                    break;
                default:
                    cout << "Invalid choice. Try again." << endl;
                }
            } while (choice != 4);

            system("pause");
        }


        /*这是我们的admin的options page和login page*/
        else if (mainmenuoption == "3") {
            const string username = "beauty123";
            const string password = "admin";
            string admin_username, admin_password;
            int choice;

            cout << "===================================\n";
            cout << "          ADMIN LOGIN PAGE        \n";
            cout << "===================================\n";
            cout << "1. Forgot Password\n";
            cout << "2. Login\n";
            cout << "3. Exit\n";
            cout << "-----------------------------------\n";
            cout << "Please enter your choice (1-3): ";
            cin >> choice;

            while (choice < 1 || choice > 3) {
                cout << "\n Invalid choice. Please select 1-3.\n";
                cout << "\n===================================\n";
                cout << "          ADMIN LOGIN PAGE        \n";
                cout << "===================================\n";
                cout << "1. Forgot Password\n";
                cout << "2. Login\n";
                cout << "3. Exit\n";
                cout << "-----------------------------------\n";
                cout << "Please enter your choice (1-3): ";
                cin >> choice;
            }

            if (choice == 1) {
                cout << "\n Your USERNAME is: " << username << "\n";
                cout << " Your PASSWORD is: " << password << "\n";
                cout << "Redirecting you to login page...\n\n";
                choice = 2; // Go to login
            }

            if (choice == 2) {
                bool loggedIn = false;

                // LOGIN VERIFICATION LOOP - This was missing!
                while (!loggedIn) {
                    cout << "\n===== ADMIN LOGIN =====\n";
                    cout << "Username: ";
                    cin >> admin_username;
                    cout << "Password: ";
                    cin >> admin_password;

                    if (admin_username == username && admin_password == password) {
                        cout << "\n Login successful! Welcome, Admin.\n";
                        loggedIn = true; // Exit login loop and proceed to admin dashboard
                    }
                    else {
                        cout << " Login failed. Incorrect username or password.\n";
                        cout << "1. Try Again\n";
                        cout << "2. Back to Main Menu\n";
                        cout << "Choose option: ";
                        int retry;
                        cin >> retry;

                        if (retry == 2) {
                            cout << "Returning to main menu...\n";
                            return main(); // Go back to main menu
                        }
                        // If retry == 1 or any other input, loop continues (try again)
                    }
                }

                // ADMIN DASHBOARD - login过后才能看见
                int adminChoice;
                do {
                    cout << "\n=====  ADMIN DASHBOARD =====\n";
                    cout << "Welcome to Admin Panel!\n";
                    cout << "=========================================\n";
                    cout << "1. View Individual Expert Schedule\n";
                    cout << "2. View Overall Schedule\n";
                    cout << "3. View Customer List\n";
                    cout << "4. Generate Sales Reports\n";
                    cout << "5. View Expert Bonus Entitlements\n";
                    cout << "6. Logout\n";
                    cout << "=========================================\n";
                    cout << "Choose an option: ";
                    cin >> adminChoice;

                    switch (adminChoice) {
                    case 1:
                        viewIndividualExpertSchedule();
                        break;
                    case 2:
                        viewOverallSchedule();
                        break;
                    case 3:
                        viewCustomerList();
                        break;
                    case 4:
                        generateSalesReport();
                        break;
                    case 5:
                        viewExpertBonus();
                        break;
                    case 6:
                        cout << "\n Logging out from Admin Panel...\n";
                        break;
                    default:
                        cout << " Invalid choice. Please select 1-6.\n";
                    }

                    if (adminChoice != 6 && adminChoice >= 1 && adminChoice <= 5) {
                        string confirm;
                        cout << "\nPress any letter to return to admin menu: ";
                        cin >> confirm;
                    }
                } while (adminChoice != 6);
            }

            else if (choice == 3) {
                cout << "\n Exiting admin system...\n";
            }




            else if (choice == 3) {
                cout << "\n Exiting system...\n";
            }
        }



        else if (mainmenuoption == "4") {
            cout << endl << "Exiting program. Goodbye!" << endl;
            break;
        }

    } while (mainmenuoption != "4");

    return 0;
}

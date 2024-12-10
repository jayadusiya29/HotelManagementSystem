#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Guest class to manage guest details
class Guest {
public:
    string name;
    int roomNumber;
    double totalBill;
    int nightsStayed;

    Guest(string guestName, int roomNum) 
    {
        name = guestName;
        roomNumber = roomNum;
        totalBill = 0;
        nightsStayed = 0;
    }
};

// FoodItem class
class FoodItem {
public:
    string name;
    double price;

    FoodItem(string n, double p)   
    {
       name=n;
       price=p;
    }
};

// Room class to manage room details
class Room {
public:
    int roomNumber;
    string type;
    bool isAvailable;
    double pricePerNight;

    Room(int number, string t, double price) 
    {
        roomNumber = number;
        type = t;
        isAvailable = true;
        pricePerNight = price;
    }

    void setAvailability(bool availability) 
    {
        isAvailable = availability;
    }
};

// Employee class to manage employee details
class Employee {
public:
    string id;
    string name;
    double salary;

    Employee(string empId, string empName, double empSalary) 
    {
        id=empId;
        name=empName;
        salary=empSalary;
    }

    void displayEmployee()  {
        cout << "ID: " << id << ", Name: " << name << ", Salary: Rs" << salary << endl;
    }
};

// Lounge class to manage lounge seating
class Lounge {
public:
    struct Seat {
        int seatNumber;
        bool isReserved;
        vector<string> orders; // Store the names of the orders
        double totalBill; // Store the total bill for this seat

        Seat(int number)   
        {
          seatNumber=number;  
          isReserved=false;
          totalBill=0.0;
        }
    };
    vector<Seat> seats;

    Lounge(int totalSeats) 
    {
        for (int i = 1; i <= totalSeats; ++i) 
            seats.push_back(Seat(i));
    }

    bool reserveSeat(int seatNumber) {
    for (int i = 0; i < seats.size(); ++i) {
        if (seats[i].seatNumber == seatNumber) {
            if (!seats[i].isReserved) {
                seats[i].isReserved = true;
                cout << "Seat " << seatNumber << " reserved.\n";
                return true;
            } 
            else {
                cout << "Seat " << seatNumber << " is already reserved.\n";
                return false;
            }
        }
    }
    cout << "Seat " << seatNumber << " does not exist.\n";
    return false;
}

    bool releaseSeat(int seatNumber) {
    for (int i = 0; i < seats.size(); ++i) {
        if (seats[i].seatNumber == seatNumber) {
            if (seats[i].isReserved) {
                seats[i].isReserved = false;
                seats[i].orders.clear(); // Clear orders when released
                cout << "Seat " << seatNumber << " released.\n";
                return true;
            } 
            else {
                cout << "Seat " << seatNumber << " is not reserved.\n";
                return false;
            }
        }
    }
    cout << "Seat " << seatNumber << " does not exist.\n";
    return false;
}

    void displayAvailableSeats() {
    cout << "Available Seats: ";
    bool found = false;
    for (int i = 0; i < seats.size(); ++i) {
        if (!seats[i].isReserved) {
            cout << seats[i].seatNumber << " ";
            found = true;
        }
    }
    if (!found) {
        cout << "None"; // No available seats
    }
    cout << endl;
}

    void orderFoodForSeat(int seatNumber, string foodName, vector<FoodItem> menu) {
    // Iterate over seats using indexing
    for (int i = 0; i < seats.size(); ++i) {
        if (seats[i].seatNumber == seatNumber) {
            if (seats[i].isReserved) {
                // Check if the food item is on the menu
                bool found = false;
                for (int j = 0; j < menu.size(); ++j) {
                    if (menu[j].name == foodName) {
                        seats[i].orders.push_back(foodName); // Add the food to orders
                        seats[i].totalBill += menu[j].price; // Increment the bill
                        cout << "Food " << foodName << " ordered for seat " << seatNumber << ".\n";
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "Food item " << foodName << " is not on the menu.\n";
                }
                return;
            } else {
                cout << "Seat " << seatNumber << " is not reserved.\n";
                return;
            }
        }
    }
    cout << "Seat " << seatNumber << " does not exist.\n";
}

    void displayOrdersForSeat(int seatNumber) {
    // Iterate over seats using indexing
    for (int i = 0; i < seats.size(); ++i) {
        if (seats[i].seatNumber == seatNumber) {
            cout << "Orders for seat " << seatNumber << ": ";
            if (seats[i].orders.empty()) {
                cout << "None";
            } else {
                // Iterate over orders using indexing
                for (int j = 0; j < seats[i].orders.size(); ++j) {
                    cout << seats[i].orders[j] << " "; // Access order using indexing
                }
                cout << "\nTotal Bill: Rs" << seats[i].totalBill; // Display total bill
            }
            cout << endl;
            return;
        }
    }
    cout << "Seat " << seatNumber << " does not exist.\n";
}

   double getTotalBillForSeat(int seatNumber) {
    // Iterate over seats using indexing
    for (int i = 0; i < seats.size(); ++i) {
        if (seats[i].seatNumber == seatNumber) {
            return seats[i].totalBill; // Return the total bill for that seat
        }
    }
    cout << "Seat " << seatNumber << " does not exist.\n";
    return 0.0; // Default return if seat not found
}

    bool handlePaymentForSeat(int seatNumber, string paymentMode) {
    for (int i = 0; i < seats.size(); ++i) {
        if (seats[i].seatNumber == seatNumber) {
            if (seats[i].totalBill > 0) {
                cout << "Payment of Rs" << seats[i].totalBill << " received for seat " 
                     << seatNumber << " via " << paymentMode << ".\n";
                seats[i].totalBill = 0;  // Reset the total bill after payment
                seats[i].orders.clear(); // Clear the orders after payment
                return true; // Payment handled successfully
            } else {
                cout << "No outstanding bills for seat " << seatNumber << ".\n";
                return false;
            }
        }
    }
    cout << "Seat " << seatNumber << " does not exist or has no orders.\n";
    return false; 
}
};

// Hotel class with properties and methods
class Hotel {
public:
    string hotel_name;
    int room_num; 
    int lon_num;  
    vector<Room> rooms;          
    vector<Guest> guests;         
    vector<Employee> employees;   
    vector<FoodItem> menu;       
    Lounge lounge;               
   Hotel():lounge(lon_num)  { 
        cout << "Enter Hotel Name: ";
        cin >> hotel_name;
        cout << "Enter Total Number of Rooms Available: ";
        cin >> room_num;
        cout << "Enter Total Number of Lounges Available: ";
        cin >> lon_num;

        // Initialize rooms for the hotel
        for (int i = 1; i <= room_num; i++) {
            rooms.push_back(Room(i, "Single", 500)); 
        }

        // Initialize employees for demo purposes
        employees.push_back(Employee("E001", "Japji ", 40000));
        employees.push_back(Employee("E002", "Rinku", 45000));
        employees.push_back(Employee("E003", "Jaspreet", 38000));

        // Initialize food menu
        menu.push_back(FoodItem("Pizza", 200));
        menu.push_back(FoodItem("Burger", 150));
        menu.push_back(FoodItem("Pasta", 200));


        // Initialize lounge, 
        lounge = Lounge(lon_num);
    }

    // Display method
    void displayHotelInfo() {
        cout << "\nHotel Name: " << hotel_name << endl;
        cout << "Rooms Available: " << room_num << endl;
        cout << "Lounge Seats Available: " << lon_num << endl;
    }
};

// HotelManager class
class HotelManager : public Hotel {
public:
    void displayMenu() {
        cout << "Restaurant Menu:\n";
        for (int i = 0; i < menu.size(); i++) {
            cout << menu[i].name << " - Rs" << menu[i].price << endl;
        }
    }

    void displayGuests() {
        cout << "Registered Guests:\n";
        for (int i = 0; i < guests.size(); i++) {
            cout << "Name: " << guests[i].name 
                 << ", Room Number: " << guests[i].roomNumber 
                 << ", Total Bill: Rs" << guests[i].totalBill 
                 << ", Nights Stayed: " << guests[i].nightsStayed << "\n";
        }
    }

    void orderFood(int roomNumber, string foodName) {
        for (int i = 0; i < rooms.size(); i++) {
            if (rooms[i].roomNumber == roomNumber) {
                if (!rooms[i].isAvailable) {
                    bool found = false;
                    for (int j = 0; j < menu.size(); j++) {
                        if (menu[j].name == foodName) {
                            for (int k = 0; k < guests.size(); k++) {
                                if (guests[k].roomNumber == roomNumber) {
                                    guests[k].totalBill += menu[j].price;
                                    cout << "Order placed for " << foodName << " to room " << roomNumber << ".\n";
                                    found = true;
                                    break;
                                }
                            }
                            break;
                        }
                    }
                    if (!found) {
                        cout << "Food item " << foodName << " is not on the menu.\n";
                    }
                } else {
                    cout << "Room " << roomNumber << " is not occupied.\n";
                }
                return;
            }
        }
        cout << "Room " << roomNumber << " does not exist.\n";
    }

    void checkIn(string guestName, int roomNumber, int nights) {
        for (int i = 0; i < rooms.size(); i++) {
            if (rooms[i].roomNumber == roomNumber) {
                if (rooms[i].isAvailable) {
                    rooms[i].setAvailability(false);
                    Guest newGuest(guestName, roomNumber);
                    newGuest.nightsStayed = nights;
                    newGuest.totalBill += rooms[i].pricePerNight * nights;
                    guests.push_back(newGuest);
                    cout << "Guest " << guestName << " checked in to room " << roomNumber << " for " << nights << " nights.\n";
                } else {
                    cout << "Room " << roomNumber << " is not available.\n";
                }
                return;
            }
        }
        cout << "Room " << roomNumber << " does not exist.\n";
    }

    void checkOut(int roomNumber) {
        for (int i = 0; i < rooms.size(); i++) {
            if (rooms[i].roomNumber == roomNumber) {
                if (!rooms[i].isAvailable) {
                    rooms[i].setAvailability(true);
                    for (int j = 0; j < guests.size(); j++) {
                        if (guests[j].roomNumber == roomNumber) {
                            cout << "Guest " << guests[j].name << " checked out from room " 
                                 << roomNumber << ". Total Bill: Rs" << guests[j].totalBill << "\n";
                            guests.erase(guests.begin() + j);
                            return;
                        }
                    }
                } else {
                    cout << "Room " << roomNumber << " is already available.\n";
                }
                return;
            }
        }
        cout << "Room " << roomNumber << " does not exist.\n";
    }

    void handlePayment(int roomNumber,string paymentMode) {
        for (int i = 0; i < guests.size(); i++) {
            if (guests[i].roomNumber == roomNumber) {
                if (guests[i].totalBill > 0) {
                    cout << "Payment of Rs" << guests[i].totalBill << " received from " 
                         << guests[i].name << " via " << paymentMode << ".\n";
                    guests[i].totalBill = 0;  // Reset the total bill after payment
                } else {
                    cout << "No outstanding bills for " << guests[i].name << ".\n";
                }
                return;
            }
        }
        cout << "Room " << roomNumber << " does not exist or has no guest.\n";
    }

    void displayEmployees() {
        cout << "Employees:\n";
        for (int i = 0; i < employees.size(); i++) {
            employees[i].displayEmployee();
        }
    }

    void reserveLoungeSeat(int seatNumber) {
        lounge.reserveSeat(seatNumber);
    }

    void releaseLoungeSeat(int seatNumber) {
        lounge.releaseSeat(seatNumber);
    }

    void displayAvailableSeats() {
        lounge.displayAvailableSeats();
    }
   void orderFoodForLounge(int seatNumber,  string foodName) {
        lounge.orderFoodForSeat(seatNumber, foodName, menu); // Pass the menu to calculate the price
    }
    void displayOrdersForLoungeSeat(int seatNumber) {
        lounge.displayOrdersForSeat(seatNumber);
    }
    void getTotalBillForLoungeSeat(int seatNumber) {
        double totalBill = lounge.getTotalBillForSeat(seatNumber);
        if (totalBill > 0) {
            cout << "Total Bill for Seat " << seatNumber << ": Rs" << totalBill << endl;
        }
    }
    void handleLoungePayment(int seatNumber,string paymentMode) {
        if (lounge.handlePaymentForSeat(seatNumber, paymentMode)) {
            cout << "Payment processed successfully for seat " << seatNumber << ".\n";
        } else {
            cout << "Failed to process payment for seat " << seatNumber << ".\n";
        }
    }
};

// Main function
int main() {
    HotelManager hotel; // Create an instance of HotelManager

    int choice;
    do {
        cout << "\nHotel Management System\n";
        cout << "1. Check In\n";
        cout << "2. Check Out\n";
        cout << "3. Display Rooms\n";
        cout << "4. Display Guests\n";
        cout << "5. Order Food\n";
        cout << "6. Display Menu\n";
        cout << "7. Reserve Lounge Seat\n";
        cout << "8. Release Lounge Seat\n";
        cout << "9. Order Food for Lounge Seat\n"; 
        cout << "10. Display Orders for Lounge Seat\n"; 
        cout << "11. Get Total Bill for Lounge Seat\n"; 
        cout << "12. Handle Payment for Lounge Seat\n"; 
        cout << "13. Display Employees\n";
        cout << "14. Display Available Lounge Seats\n";
        cout << "15. Handle Payment for Room\n";
        cout << "16. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;


        switch (choice) {
            case 1: { // Check In
                string name;
                int roomNumber, nights;
                cout << "Enter guest name: ";
                cin >> name;
                cout << "Enter room number to check in: ";
                cin >> roomNumber;
                cout << "Enter number of nights: ";
                cin >> nights;
                hotel.checkIn(name, roomNumber, nights);
                break;
            }
            case 2: { // Check Out
                int roomNumber;
                cout << "Enter room number to check out: ";
                cin >> roomNumber;
                hotel.checkOut(roomNumber);
                break;
            }
            case 3: { // Display Rooms
                cout << "Displaying rooms:\n";
                for (int i = 0; i < hotel.rooms.size(); i++) {
                    cout << "Room Number: " << hotel.rooms[i].roomNumber 
                         << ", Type: " << hotel.rooms[i].type 
                         << ", Price/Night: Rs" << hotel.rooms[i].pricePerNight
                         << ", Availability: " << (hotel.rooms[i].isAvailable ? "Available" : "Occupied") << endl;
                }
                break;
            }
            case 4: // Display Guests
                hotel.displayGuests();
                break;
            case 5: { // Order Food
                int roomNumber;
                string foodName;
                cout << "Enter room number to order food: ";
                cin >> roomNumber;
                cout << "Enter food item name: ";
                cin >> foodName;
                hotel.orderFood(roomNumber, foodName);
                break;
            }
            case 6: // Display Menu
                hotel.displayMenu();
                break;
            case 7: { // Reserve Lounge Seat
                int seatNumber;
                cout << "Enter lounge seat number to reserve: ";
                cin >> seatNumber;
                hotel.reserveLoungeSeat(seatNumber);
                break;
            }
            case 8: { // Release Lounge Seat
                int seatNumber;
                cout << "Enter lounge seat number to release: ";
                cin >> seatNumber;
                hotel.releaseLoungeSeat(seatNumber);
                break;
            }
            case 9: { // Order Food for Lounge Seat
                int seatNumber;
                string foodName;
                cout << "Enter lounge seat number to order food: ";
                cin >> seatNumber;
                cout << "Enter food item name: ";
                cin >> foodName;
                hotel.orderFoodForLounge(seatNumber, foodName);
                break;
            }
            case 10: { // Display Orders for Lounge Seat
                int seatNumber;
                cout << "Enter lounge seat number to display orders: ";
                cin >> seatNumber;
                hotel.displayOrdersForLoungeSeat(seatNumber);
                break;
            }
            case 11: { // Get Total Bill for Lounge Seat
                int seatNumber;
                cout << "Enter lounge seat number to get total bill: ";
                cin >> seatNumber;
                hotel.getTotalBillForLoungeSeat(seatNumber);
                break;
            }
             case 12: { // Handle Payment for Lounge Seat
                int seatNumber;
                string paymentMode;
                cout << "Enter lounge seat number to handle payment: ";
                cin >> seatNumber;
                cout << "Enter payment mode (Cash/Credit Card): ";
                cin >> paymentMode;
                hotel.handleLoungePayment(seatNumber, paymentMode);
                break;
            }
            case 13: // Display Employees
                hotel.displayEmployees();
                break;
            case 14: // Display Available Lounge Seats
                hotel.displayAvailableSeats();
                break;
                
            case 15: { // Handle Payment
                int roomNumber;
                string paymentMode;
                cout << "Enter room number to handle payment: ";
                cin >> roomNumber;
                cout << "Enter payment mode (Cash/Credit Card): ";
                cin >> paymentMode;
                hotel.handlePayment(roomNumber, paymentMode);
                break;
            }
            case 16: // Exit
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 16);

    return 0;
}
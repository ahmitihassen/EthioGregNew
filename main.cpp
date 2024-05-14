#include <iostream>
#include <cstdint>
#include <limits>
#include <string>

using namespace std;

///Structures
struct Date {
    int16_t year;
    uint16_t month;
    uint16_t day;
};

struct EthioDate {
    int16_t year;
    uint16_t month;
    uint16_t day;
};

///Function Declarations

Date getDate();
//precondition: user is prepared to enter the correct data.
//postcondition: the year variable is poplulated with user input and day and month are set with value 1.


int main() {
    Date date = getDate();

    cout << date.day;
    cout << date.month;
    cout << date.year;
}

///Function Definitions
Date getDate() {
	Date date;

    //Set day and month to 1 because printing starts from the first day of the first month.
    date.day = +1;
    date.month = 1;

    cout << "Characters and floating point numbers after the integer will be ignored\n";

    cout << "Enter Year: ";
    cin >> date.year;
   
    while (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Incorrect input. Please enter the year again: ";
        cin >> date.year;
    }
   
    return date;
}

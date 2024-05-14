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

///Constants
const int monthCode[12] = { 0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5 };

///Function Declarations

Date getDate();
//precondition: user is prepared to enter the correct data.
//postcondition: the year variable is poplulated with user input and day and month are set with value 1.

int getWeekDay(Date date);
//precondition: date has its year,month and day values set.
//postcondition: returns an integer that represents a week day.

int getYearCode(int year);
//precondition: year has its value set.
//postcondition: returns an integer that represents the year code.

int getMonthCode(int month);
//precondition: month has its value set.
//postcondition: returns an integer that represents the code for the month.

int getCenturyCode(int year);
//precondition: year has its value set.
//postcondition: returns an integer that represents the code for the century in which the year is in.

int getFirstTwoDigits(int number);
//precondition: number has its value set.
//postcondition: returns a maximum of two digit integer exracted from the given number.

int getLeapYearCode(int year);
//precondition: year has its value set.
//postcondition: returns an integer that represents leap year code (1 if leap year or 0 if not).

bool isLeapYear(int year);
//precondition: year has its value set.
//postcondition: returns true if the year is leap year or false it's not.

bool isGregYear(int year);
//precondition: year has its value set.
//postcondition: returns true if the year is gregorian or false if it's a julian year.


int main() {
    Date date = getDate();
    cout << getWeekDay(date);
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

int getWeekDay(Date date) {
    //magic formula to get weekday
    return (getYearCode(date.year) + getMonthCode(date.month) + getCenturyCode(date.year) + date.day - getLeapYearCode(date.year)) % 7;
}

int getYearCode(int year) {
    int lastTwoDigits = year % 100;
    return (lastTwoDigits + (lastTwoDigits / 4) % 7);
}

int getMonthCode(int month) {
    return monthCode[month - 1];
}

int getCenturyCode(int year) {
    //ftd is first two digits
    int ftd = getFirstTwoDigits(year);

    //If the year is a gregorian year
    if (isGregYear(year)) {
        if ((ftd - 17) % 4 == 0)
            //all centuries occurring in multiple of 4 centuries after 1700 (eg: 2100, 2500 and so on)
            return 4;
        else if ((ftd - 18) % 4 == 0)
            return 2;
        else if ((ftd - 19) % 4 == 0)
            return 0;
        else if ((ftd - 20) % 4 == 0)
            return 6;
    }
    //If the year is a julian year
    else {
        return (18 - year / 100) % 7;
    }
    return 0;
}

int getFirstTwoDigits(int number) {
    if (number < 100)
        return number;
    else {
        return getFirstTwoDigits(number / 10);
    }
}

int getLeapYearCode(int year) {
    if (isLeapYear(year))
        return 1;
    return 0;
}

bool isLeapYear(int year) {
    if (isGregYear(year))
        return (year % 4 == 0 && year % 100 != 0) || ((year % 400) == 0);
    else
        return ((year % 4) == 0);
}

bool isGregYear(int year) {
    if (year > 1752)
        return true;
    return false;
}
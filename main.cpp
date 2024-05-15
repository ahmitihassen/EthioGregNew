#include <iostream>
#include <cstdint>
#include <limits>
#include <string>

using namespace std;

///Structures
struct Date {
    uint16_t year;
    uint16_t month;
    uint16_t day;
};

struct EthioDate {
    uint16_t year;
    uint16_t month;
    uint16_t day;
};

///Constants
const int monthCode[12] = {0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5};

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

void printCalendar(Date date);
//precondition: date has its day year and month value set.
//postcondition: prints the calendar for the given year.

bool isEthioLeapYear(int eyear);
//precondition: edate has it's year month and day value set.
//postcondition: returns true if the year is Ethiopian leap year or false if it's not.

EthioDate getEthioStartDate(Date date);
//precondition: date has correct year month and day values set.
//postcondition: returns EthioDate variable with correct values set.

void decrementEthioDate(EthioDate& edate);
//precondition: edate has it's values set.
//postcondition: decrements the Ethiopian date by one day.


int main() {
    Date date = getDate();
    cout << getWeekDay(date)<<endl;
    printCalendar(date);
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
    return (getYearCode(date.year) + getMonthCode(date.month) + getCenturyCode(date.year) + date.day -
            getLeapYearCode(date.year)) % 7;
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

void printCalendar(Date date) {
    int weekDay = getWeekDay(date);
    EthioDate eStartDate = getEthioStartDate(date);
    cout<<date.year<<" "<<date.month<<" "<<date.day<<endl;
    cout<<eStartDate.year<<" "<<eStartDate.month<<" "<<eStartDate.day<<endl;
}

EthioDate getEthioStartDate(Date date) {
    EthioDate edate;
    edate.year = date.year - 8;
    if (date.year < 1753) {
        edate.month = 5;
        edate.day = 6;
    } else {
        edate.day = 25;
        edate.month = 4;
        if(date.year > 1799) {
            int ftd = getFirstTwoDigits(date.year);
            int startCent = 18;
            while (startCent < ftd) {
                startCent++;
            }
            for (int i = 18; i <= startCent; i++) {
                int nextCent = i * 100;
                if (nextCent != date.year) {
                    if (!(isLeapYear(nextCent)))
                        decrementEthioDate(edate);
                }
            }
        }
        if (isEthioLeapYear(edate.year - 1))
            decrementEthioDate(edate);
    }
    return edate;
}

bool isEthioLeapYear(int eyear){
    if (eyear % 4 == 3)
        return true;
    return false;
}

void decrementEthioDate(EthioDate& edate){
    if (edate.month == 1) {
        if (edate.day == 1) {
            edate.year--;
            edate.month = 13;
            if (isEthioLeapYear(edate.year)) {
                edate.day = 6;
            } else
                edate.day = 5;
        } else
            edate.day--;
    } else {
        if (edate.day == 1) {
            edate.month--;
            edate.day = 30;
        } else
            edate.day--;
    }
}
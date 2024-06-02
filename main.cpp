#include <iostream>
#include <cstdlib>
#include <limits>
#include <string>
#include <iomanip>

using namespace std;

///Global Variables
int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

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

const string gregMonthNames[12] = {"January", "February", "March", "April", "May", "June", "July", "August",
                                   "September",
                                   "October", "November", "December"};

const string ethioMonthNames[13] = {"Meskerem", "Tikimt", "Hidar", "Tahisas", "Tir", "Yekatit", "Megabit", "Miyaza",
                                    "Ginbot", "Sene", "Hamle", "Nehase", "Pagume"};

const string weekDays[7] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

const int NumberOfHyphens = 50;

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

int getLeapYearCode(int year,int month);
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

void decrementEthioDate(EthioDate &edate);
//precondition: edate has it's values set.
//postcondition: decrements the Ethiopian date by one day.

void incrementEthioDate(EthioDate &edate);
//precondition: edate has it's values set.
//postcondition: increments the Ethiopian date by one day.

void incrementGregDate(Date& date);
//precondition: date has it's values set.
//postcondition: increments the date by one day.

void printMonthName(Date date, EthioDate edate, int monthCounter);
//precondition: date and edate has their values set.
//postcondition: prints the gregorian month and the ethiopian month(s) within the gregorian month.

int *getEthioMonthInGregMonth(int month, EthioDate edate);
//precondition: month and edate has their values set.
//postcondition: returns a pointer that points to an array of integers that represent the ethiopian months.

void adjustMonthDays(int year);
//precondition: year has it's value set.
//postcondition: changes february month day to 29 if it's a leap year.

void printMonth(Date& date, EthioDate& edate, int monthCounter);
//precondition: values are set.
//postcondition: prints days in a given gregorian month.

void printWeekDays();
//prints week days from Sunday to Saturday.

void printHyphens();
//prints hyphens to draw calendar.

bool hasEthioStarted(int date);
//precondition: date has been populated
//returns true if date is greater than 7 8 29(m,d,y)


int main() {
    char cont = 'y';
    while (cont == 'y') {
        system("cls");
        Date date = getDate();
        //cout << getWeekDay(date) << endl;
        printCalendar(date);
        cout << endl;
        cout << "Continue? ";
        cin >> cont;
    }
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
            getLeapYearCode(date.year,date.month)) % 7;
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

int getLeapYearCode(int year,int month) {
    if (isLeapYear(year) && month < 3)
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
    EthioDate eStartDate = getEthioStartDate(date);
    adjustMonthDays(date.year);
    for (int i = 0; i < 12; i++) {
        cout << endl;
        printMonthName(date, eStartDate,i);
        cout << endl;
        printHyphens();
        printWeekDays();
        printHyphens();
        printMonth(date, eStartDate, i);
    }
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
        if (date.year > 1799) {
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
    if (date.year == 7) {
        edate.year = 1;
        edate.month = 1;
        edate.day = 1;
    }
    return edate;
}

bool isEthioLeapYear(int eyear) {
    if (eyear % 4 == 3)
        return true;
    return false;
}

void decrementEthioDate(EthioDate &edate) {
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

void printMonthName(Date date, EthioDate edate, int monthCounter) {
    int* ethioMonth = getEthioMonthInGregMonth(monthCounter, edate);

    cout << date.year;
    cout << "   ";
    cout << gregMonthNames[monthCounter];
    cout << "           ";
    cout <<  edate.year;
    cout << "   ";
    for (int i = 0; i < 3; i++) {
        if (ethioMonth[i] != 99)
            cout << ethioMonthNames[ethioMonth[i]-1] << "   ";
        else
            cout << " ";
    }

    cout << endl;

}

int *getEthioMonthInGregMonth(int month, EthioDate edate) {
    int firstMonth = edate.month;
    static int months[3];
    int index = 1;
    months[0] = firstMonth;
    months[1] = 99;
    months[2] = 99;

    for (int i = 1; i < monthDays[month]; i++) {
        incrementEthioDate(edate);
        if (edate.month != firstMonth) {
            months[index] = edate.month;
            firstMonth = edate.month;
            index++;
        }
    }

    return months;
}

void incrementEthioDate(EthioDate &edate) {
    if (edate.month == 13) {
        if (isEthioLeapYear(edate.year)) {
            if (edate.day == 6) {
                edate.year++;
                edate.month = 1;
                edate.day = 1;
            } else {
                edate.day++;
            }
        } else {
            if (edate.day == 5) {
                edate.year++;
                edate.month = 1;
                edate.day = 1;
            } else edate.day++;
        }
    } else {
        if (edate.day == 30) {
            edate.month++;
            edate.day = 1;
        } else
            edate.day++;
    }
}

void adjustMonthDays(int year) {
    if (isLeapYear(year))
        monthDays[1] = 29;
    else
        monthDays[1] = 28;
}

void printWeekDays() {
    cout << "|";
    for (int i = 0; i < 7; i++) {
        cout << weekDays[i] << setw(4) << "|";
    }
    cout << endl;
}

void printHyphens() {
    cout << "|" << string(NumberOfHyphens - 2, '-') << "|";
    cout << endl;
}

void incrementGregDate(Date& date) {
    if (date.month == 12) {
        if (date.day == monthDays[date.month-1]) {
            date.month = 1;
            date.day = 1;
            date.year++;
        }
        else {
            date.day++;
        }
    }
    else {
        if (date.day == monthDays[date.month - 1]) {
            date.month++;
            date.day = 1;
        }
        else
            date.day++;
    }
}

bool hasEthioStarted(Date date) {
    /*cout << endl;
    cout << "debug output" << endl;
    cout << date.year << " " << date.month << " " << date.day << endl;*/
    if (date.year > 7)
        return true;
    if (date.year > 6 && date.month > 8)
        return true;
    if (date.year > 6 && date.month > 7 && date.day > 29)
        return true;
    return false;
}

void printMonth(Date& date, EthioDate& edate, int monthCounter) {
    cout << date.year << " " << date.month << " " << date.day << endl;
    int weekDay = getWeekDay(date);
    int noOfDays = monthDays[monthCounter];
    int dayCounter = 1;
    bool isFirstLine = true;
    int lastDay = weekDay;
    bool startException = true;
    while (dayCounter <= noOfDays + 1) {

        if (dayCounter <= noOfDays) {
            cout << "|";
            for (int i = 0; i < 7; i++) {
                if (monthCounter == 8 && date.year == 1752 && dayCounter == 3) {
                    dayCounter += 11;
                    date.day += 10;
                }
                if ((i < weekDay && isFirstLine) || (dayCounter > noOfDays))
                    cout << setw(7) << "|";
                else {
                    cout << setw(6) << date.day << "|";
                    dayCounter++;
                    lastDay++;
                    if (lastDay > 6)
                        lastDay = 0;
                    incrementGregDate(date);
                }
            }
            cout << endl;
        }

        if (hasEthioStarted(date)) {
            for (int i = 0; i < 7; i++) {
                if (i < weekDay && isFirstLine || (i > (lastDay > 0 ? lastDay - 1 : 6) && dayCounter > noOfDays))
                    cout << "|" << setw(7);
                else {
                    if (date.year ==7 && date.month == 9 && date.day == 1 && startException) {
                        cout << "|" << setw(7);
                        startException = false;
                        continue;
                    }
                    if (edate.day > 9)
                        cout << "|" << edate.day << setw(5);
                    else
                        cout << "|" << edate.day << setw(6);
                    incrementEthioDate(edate);
                }
            }
        }

        isFirstLine = false;
        if (dayCounter > noOfDays) {
            dayCounter++;
        }
        cout << "|" << setw(0) << endl;
        printHyphens();
    }
}


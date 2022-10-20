// ----------------------------- Implementation --- Time.cpp

#include "Time.h"
using namespace std;

// default constructor - set the value to 0 minutes
Time::Time() { 
    this->minutes = 0;
}

// initalizes Time value to given number of minutes 
Time::Time(double m) {
    this->minutes = m;
}

// increase this Time's minute count by miute value from given otherTimeObj
void Time::add(const Time& otherTimeObj) {
    //this->minutes = this->minutes + otherTimeObj.minutes;
    //-----------OR---------------
    this->minutes = this->minutes + otherTimeObj.getTime();
}

// get or return minute value of this Time object
double Time::getTime() const {
    return this->minutes;
}

void Time::print() const {
    cout << this->minutes << "minutes" << endl;
}

Time operator+ (const Time& a, const Time& b) {
    Time result(a.getTime());
    result.add(b);
    return result;
}

// Make it so our Main can say cout << a << endl where a is a Time object we printed output 5 miniutes 
ostream& operator<< (ostream& os, const Time& T) {
    os << T.getTime() << " minutes";
    return os;
}
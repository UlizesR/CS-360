//----------------------- Interface --- Time.h
#include <iostream>
using namespace std;

class Time{

    private:
        // declare attribute data
        double minutes;

    public:
        Time(); // default constructor - set the value to 0 minutes

        Time(double m); // initalizes 

        void add(const Time& otherTimeObj);

        // get or return minute value of this Time object
        double getTime() const;
        
        void print() const;

        //
        friend Time operator+ (const Time& a, const Time& b); 

        // Make it so our Main can say cout << a << endl where a is a Time object we printed output 5 miniutes 
        friend ostream& operator<< (ostream& os, const Time& T);

};


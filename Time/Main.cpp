//------------- Main ---------------

#include "Time.h"

int main() {
    Time first; // default Time object, expect minutes to be 0
    Time second(30); // initialze Time object with minutes 30
    Time third(55);

    // Have each Time objecy print its value
    //first.print();  // expect 0 minutes
    //second.print(); // expect 30 minutes
    //third.print();  // expect 55 minutes
    cout << "first is " << first << endl;
    cout << "second is " << second << endl;
    cout << "third is " << third << endl; 
    // Have second Time add its value to third
    //third.add(second);

    third = third + second;

    // print now updated value of third
    //third.print();  // expect 85 minutes
    cout << "third is " << third << endl;

    return 0;
}
#include "Tuple.h"

int main() {
    Tuple def;
    Tuple A(10, 2, 3, 1); // create point (10, 2, 3), last value is w set to 1 for points
    Tuple B(-5, 2, 4, 1); // create point (-5, 2, 4)
    Tuple step(0,3,0);  // create vector (0,3,0); // its w value will be 0

    Tuple vec(3, 5, 10);
    Tuple vec2(4, 2, 11);

    cout << "default Tuple is " << def << endl;
    
    Tuple C(A); // Create point C that is a copy of point A that is (10, 2, 3, 1

    // A.add(step); // Changes point A to be result of taking step (0,3,0).
    //             // We expect A to be the point (10, 5, 3)
    // cout << "A is " << A << endl;

    // cout << "C is a copy of A " << C << endl; // Expect to see (10, 2, 3, 1)

    // C.sub(B); // Compute vector that represents direction and magnitude of stepping
    //           // from point B to point C.
    //           // C = C - B
    //           // (10, 2, 3) - (-5, 2, 4) = (15, 0, -1)

    // cout << "C is " << C << endl;
    // // We expect to see a vector output of (15, 0, -1, 0)
    // // Notice that the w value changed to 0 since subtracting two points
    // // gives a displacement vector

    C = C - B;
    cout << "C is " << C << endl; //Expected Value (15, 0, -1, 0)
    A = A + step;
    cout << "A is " << A << endl; //Expected Value (10, 5, 3, 1)
    cout << "A is a point: " << A.isPoint() << endl; //Expected value 1
    cout << "A is a vector: " << A.isVector() << endl; //Expected value 0
    cout << "vec is a vector: " << vec.isVector() << endl;//Expected value 1
    cout << "vec is a point: " << vec.isPoint() << endl; //Expected value 0
    cout << "The magnitude of A is " << A.magnitude() << endl; //Expected value is 11.5758
    
    cout << "vec2 multiplied by 5 gives: " << vec2*5 << endl; //Expected value (20, 10, 55)
    vec2.normalize();
    cout << "A normalized vector " << vec2 << endl;                            // Expected Value (0.9978, 0, -0.0665)
    cout << "The dot product of vec and vec2 is " << vec.dot(vec2) << endl; // expected value is 132

}
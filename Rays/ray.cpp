#include "ray.h"


Ray::Ray() {
    
    this->direction = Tuple(0, 0, 1, 0);
    this->origin = Tuple(0, 0, 0, 1);
}

// Ray::Ray(Tuple origin, Tuple end) {
//     this->origin = origin;
//     this->direction = end - origin;
//     this->direction.normalize();
// }



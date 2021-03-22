#ifndef _READING_H_
#define _READING_H_

#include <vector>
#include "Shape.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Cone.h"
#include "Cuboid.h"

std::vector<Shape*> *readFrom(std::string);

#endif

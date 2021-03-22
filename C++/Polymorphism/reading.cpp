/* Author: Stephen Sottosanti */
#include "reading.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

vector<Shape*> *readFrom(string shapes_file){
    vector<Shape*> *shapes = new vector<Shape*>;
    string line, name, type, radius, length, width, height; // A string to store the string for each iteration for each shape

    ifstream shapes_stream;
    shapes_stream.open(shapes_file, ios::in);

    while(getline(shapes_stream, line)){
        stringstream str_strm(line);
        str_strm >> name;
        str_strm >> type;

        if(type.compare("sphere") == 0){
            Sphere *sphere = new Sphere(name);
            str_strm >> radius;
            sphere->setRadius(stod(radius));
            shapes->push_back(sphere);
        }
        else if(type.compare("cylinder") == 0){
            Cylinder *cylinder = new Cylinder(name);
            str_strm >> radius;
            str_strm >> height;
            cylinder->setCylinder(stod(radius), stod(height));
            shapes->push_back(cylinder);
        }
        else if(type.compare("cone") == 0){
            Cone *cone = new Cone(name);
            str_strm >> radius;
            str_strm >> height;
            cone->setCone(stod(radius), stod(height));
            shapes->push_back(cone);    
        }
        else if(type.compare("cuboid") == 0){
            Cuboid *cuboid = new Cuboid(name);
            str_strm >> length;
            str_strm >> width;
            str_strm >> height;
            cuboid->setCuboid(stod(length), stod(width), stod(height));
            shapes->push_back(cuboid);
        }
    }

    return shapes;
};
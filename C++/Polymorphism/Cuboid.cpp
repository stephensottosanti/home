/* Author: Stephen Sottosanti */
#include "Cuboid.h"

Cuboid::Cuboid(const std::string& name) : Shape(name) {
    this->length = 0.0; 
    this->width = 0.0;
    this->height = 0.0;
}


void Cuboid::setCuboid(const double& length, const double& width, const double& height) { 
    this->length = length; 
    this->width = width;
    this->height = height;
}

double Cuboid::getArea() { return ((2.0 * width * length) + (2.0 * length * height) + (2.0 * height * width)); }

double Cuboid::getVolume() { return (length * width * height); }

bool Cuboid::test(const std::vector<std::string>& cond) { 
      bool test = true;
      std::string c1, c2, c3;
      std::string type = "cuboid";
      int loops = cond.size();
      int i = 0;

      while(loops--){
         c1 = cond.at(i);
         loops--;
         c2 = cond.at(i+1);
         loops--;
         c3 = cond.at(i+2);

         if(c1 == "type"){
               if(c2 == "=="){
                  if(type == c3){}
                  else test = false;
               }
               else if(c2 == "!="){
                  if(type != c3){}
                  else test = false;
               }
               else if(c2 == ">="){
                  if(type >= c3){}
                  else test = false;
               }
               else if(c2 == "<="){
                  if(type <= c3){}
                  else test = false;
               }
               else if(c2 == ">"){
                  if(type > c3){}
                  else test = false;
               }
               else{ // <
                  if(type < c3){}
                  else test = false;
               }
         }
         else if(c1 == "area"){
               double area = getArea();
               if(c2 == "=="){
                  if(area == stod(c3)){}
                  else test = false;
               }
               else if(c2 == "!="){
                  if(area != stod(c3)){}
                  else test = false;
               }
               else if(c2 == ">="){
                  if(area >= stod(c3)){}
                  else test = false;
               }
               else if(c2 == "<="){
                  if(area <= stod(c3)){}
                  else test = false;
               }
               else if(c2 == ">"){
                  if(area > stod(c3)){}
                  else test = false;
               }
               else{ // <
                  if(area < stod(c3)){}
                  else test = false;
               }
         }
         else{ // volume
               double volume = getVolume(); 
               if(c2 == "=="){
                  if(volume == stod(c3)){}
                  else test = false;
               }
               else if(c2 == "!="){
                  if(volume != stod(c3)){}
                  else test = false;
               }
               else if(c2 == ">="){
                  if(volume >= stod(c3)){}
                  else test = false;
               }
               else if(c2 == "<="){
                  if(volume <= stod(c3)){}
                  else test = false;
               }
               else if(c2 == ">"){
                  if(volume > stod(c3)){}
                  else test = false;
               }
               else{ // <
                  if(volume < stod(c3)){}
                  else test = false;
               }
         }

         i += 3;
      }    

      return test;
   } // test if the conditions are statisfied

std::string Cuboid::getInfo() {
   std::stringstream str_stream;

   str_stream << "Cuboid: " << Shape::getName();
   str_stream << ", Length=" << std::fixed << std::setprecision(2) << length;
   str_stream << ", Width=" << std::fixed << std::setprecision(2) << width;
   str_stream << ", Height=" << std::fixed << std::setprecision(2) << height;
   str_stream << "\n\tSurface Area: " << std::fixed << std::setprecision(2) << getArea();
   str_stream << ", Volume: " << std::fixed << std::setprecision(2) << getVolume() << std::endl;

   return str_stream.str();
   } 
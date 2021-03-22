# *****************************************************
# Variables to control Makefile operation
 
CC = g++
CFLAGS = -Wall -std=c++11 -g
 
# ****************************************************
# Targets needed to bring the executable up to date

a.out:
	$(CC) $(CFLAGS) main.cpp reading.cpp Cylinder.cpp Cone.cpp Cuboid.cpp Shape.cpp Sphere.cpp
 
reading.o: reading.h

Cylinder.o: Cylinder.h

Cone.o: Cone.h

Cuboid.o: Cuboid.h

Shape.o: Shape.h

Sphere.o: Sphere.h


.PHONY : clean
clean :
	-rm a.out
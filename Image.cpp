/*******************************************************************************************************************************************
Filename: Image.cpp
Version: 1.0
Author: Xingyi Wu
Student No: 040 887 028
Course Name/Number: CST8219 C++ Programming
Lab Sect: 304
Assignment #: 3
Assignment name: RasterGraphic Project in C++ using Polymorphic Inheritance and RTTI
Due Date: Sat 01 December 2018
Submission Date: Sat 01 December 2018
Professor: Andrew Tyler
Purpose: to instantial an image object contains pixels(x, y), screen time (duration) and name and print images by overloading operator
*******************************************************************************************************************************************/
#include <iostream>
using namespace std;
#include "Image.h"
#include "SystemMemoryImage.h"
#include "GPUMemoryImage.h"

/*******************************************************************************
Function Name: Image
Purpose: default constructor to initialize each member of an image
In parameters: int x, int y, int duration, char* name
Out parameters: none
Version: 1.0
Author: Xingyi Wu
********************************************************************************/
Image::Image(int x, int y, int duration, char* name) {
	this->pixel_x = x;
	this->pixel_y = y;
	this->duration = duration;
	this->name = new char[strlen(name) + 1];
	strcpy_s(this->name, strlen(name) + 1, name);
}

/******************************************************************************
Function Name: Image
Purpose: copy constructor to pass the image in parameter to make a deep copy
In parameters: const Image&
Out parameters: none
Version: 1.0
Author: Xingyi Wu
*******************************************************************************/
Image::Image(const Image& ob) {
	pixel_x = ob.pixel_x;
	pixel_y = ob.pixel_y;
	duration = ob.duration;
	name = new char[strlen(ob.name) + 1];
	strcpy_s(name, strlen(ob.name) + 1, ob.name);
}

/**************************************************************************************************
Function Name: operator<<
Purpose: to return the reference of ostream for the reference of image
to print Image in a certain formate
In parameters: ostream& , Image&
Out parameters: ostream& os
Version: 1.0
Author: Xingyi Wu
***************************************************************************************************/
ostream& operator<<(ostream& os, Image& ob) {
	
	os << "\tImage name = " << ob.name << "; pixel_x = " << ob.pixel_x << "; pixel_y = " << ob.pixel_y << "; duration = " << ob.duration << endl;
	os << "\tCounting the seconds for this Image: ";
	for (int i = 1; i <= ob.duration; i++)
	{
		os << i << ", ";
	}
	return os;
}
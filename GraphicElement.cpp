/*******************************************************************************************************************************************
Filename: GraphicElement.cpp
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
Purpose: A GraphicElement has set of Image* pointers that are the addresses of the Image objects that are actually SystemMemoryImage or GPUMemoryImage objects
         associated with it by using vector<> and print each element.
*******************************************************************************************************************************************/
#include <iostream>
#include <string>
#include <vector>
using namespace std;
#include "Image.h"
#include "SystemMemoryImage.h"
#include "GPUMemoryImage.h"
#include "GraphicElement.h"

/**************************************************************************************************
Function Name: GraphicElement
Purpose: copy constructor
In parameters: GraphicElement&
Out parameters: 
Version: 1.0
Author: Xingyi Wu
***************************************************************************************************/
GraphicElement::GraphicElement(const GraphicElement& ob) {
	fileName = ob.fileName;
	/* deep copy */
	for (int i = 0; i < ob.Images.size(); i++) {
		Images.emplace_back(ob.Images[i]); 
	}
}

/**************************************************************************************************
Function Name: operator<<
Purpose: to print each element of the GraphicElement object by using overloading operator
In parameters: ostream&, GraphicElement&
Out parameters: ostream& os
Version: 1.0
Author: Xingyi Wu
***************************************************************************************************/
ostream& operator<<(ostream& os, GraphicElement& ob) {
	int counter = 0;
	os << "\tfileName = ";
	os << ob.fileName;
	for (vector<Image*> ::iterator it = ob.Images.begin(); it != ob.Images.end(); it++) {
		os << endl << "\tImage #" << counter << ": ";
		
		/* identify the images by dynamic_cast<>() */
		GPUMemoryImage* temp = dynamic_cast<GPUMemoryImage*>(*it);
		if (temp != nullptr) {
			os << "GPU Memory Image. Shader = " << temp->GetShader() << "\n";
		}
		else {
			os << "System Memory Image \n" ;
		}
		os << **it;
		os << "\n\tMemory requirements = " << (*it)->BufferSize() << " bytes" << endl;
		counter++;
	}
	os << endl;
	return os;
}
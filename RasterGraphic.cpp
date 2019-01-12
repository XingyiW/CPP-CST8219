/*******************************************************************************************************************************************
Filename: RasterGraphic.cpp
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
Purpose: Using foward_list in dynamic memory for its data that allow users to manipulate the list (insert, remove), and displays
the details of each GraphicElement at intervals of 1 second using the system clock
*******************************************************************************************************************************************/
#include <iostream>
#include <string>
#include <forward_list>
#include <vector>
using namespace std;
#include "Image.h"
#include "SystemMemoryImage.h"
#include "GPUMemoryImage.h"
#include "GraphicElement.h"
#include "RasterGraphic.h"

/***************************************************************************************************************************
Function Name: InsertGraphicElement
Purpose: insert element to the forward list in any location as users want
In parameters: none
Out parameters: none
Version: 1.0
Author: Xingyi Wu
***************************************************************************************************************************/
void RasterGraphic::InsertGraphicElement() {
	string str; // input file name
	int num_image;
	int x;
	int y;
	int time;
	int type;
	string name_shader;
	char name_image[128]; // a pointer to char for dynamic memory allocated for input str_nameImage
	vector<Image*> temp; // temporary vector to store a new image*
	int counter; // forward_list distance
	int index; // insert position

	cout << "Insert a GraphicElement in the RasterGraphic \n";
	cout << "Please enter the GraphicElement filename: ";
	cin >> str;

	// input valid image number
	cout << "Entering the GraphicElement Images (the sets of dimensions and durations) \n";
	do {
		cout << "Please enter the number of Images: ";
	} while (!(cin >> num_image) || num_image<0);

	// input valid image body
	for (int i = 0; i < num_image; i++) {
		do {
			cout << "Please enter pixel x-width for Image #" << i << " pixel_x: ";
		} while (!(cin >> x) || x<0);

		do {
			cout << "Please enter pixel y-width for Image #" << i << " pixel_y: ";
		} while (!(cin >> y) || y<0);

		do {
			cout << "Please enter the duration sec for this Image: ";
		} while (!(cin >> time) || time<0);

		cout << "Please enter the name for this Image: ";
		cin >> name_image;

		do {
			cout << "Please enter the type for this Image (1 = SystemMemoryImage, 2 = GPUMemoryImage): ";
		} while (!(cin >> type) || (type!=1 && type !=2));

		/* store images by identifying the type */
		if (type == 1) {
			temp.emplace_back(new SystemMemoryImage(x, y, time, name_image));
			cout << endl;
		}
		else {
			cout << "Please enter the file name of the associated GPU Shader: ";
			cin >> name_shader;
			temp.emplace_back(new GPUMemoryImage(x, y, time, name_image, name_shader));
			cout << endl;
		}
	}

	// check empty list to identify the first element
	if (GraphicElements.empty()) {
		GraphicElements.emplace_front(str, temp);
		cout << "This is the first GraphicElement in the list\n\n";
	}
	else {
		// create iterator to insert a new element
		
		forward_list<GraphicElement>::iterator GE = GraphicElements.begin();
	
		counter = distance(GraphicElements.begin(), GraphicElements.end());

		// insert after 1st element
		if (counter == 1) {
			GraphicElements.emplace_after(GE, str, temp);
			cout << endl;
		}
		else {
			cout << "There are " << counter << " GraphicElement(s) in the list \n";
			do {
				cout << "Please specify the position, between 0 " << " and " << counter - 1 << " to insert after : ";
			} while (!(cin >> index) || index<0 || index >counter - 1);

			// insert indicated position
			advance(GE, index);
			GraphicElements.emplace_after(GE, str, temp);
			cout << endl;
		}
	}
}

/*******************************************************************************************
Function Name:  DeleteGraphicElement
Purpose: delete first element of the forward list
In parameters: none
Out parameters: none
Version: 1.0
Author: Xingyi Wu
*******************************************************************************************/
void RasterGraphic::DeleteGraphicElement() {
	//check empty list
	if (GraphicElements.empty()) {
		cout << "There is nothing to remove.\n";
	}
	else {
		cout << " Delete the first GraphicElement from the RasterGraphic\n";
		GraphicElements.pop_front();
		cout << " GraphicElement deleted\n\n";
	}
}

/**************************************************************************************************
Function Name: operator<<
Purpose: to return the reference of ostream for the reference of RasterGraphic
to print RasterGraphic in a certain formate
In parameters: ostream& , RasterGraphic&
Out parameters: ostream& os
Version: 1.0
Author: Xingyi Wu
***************************************************************************************************/
ostream& operator<<(ostream& os, RasterGraphic& ob) {
	int counter = 0;
	os << "RasterGraphic " << ob.name << endl;
	os << "Run the RasterGraphic" << endl;
	for (forward_list<GraphicElement> ::iterator it = ob.GraphicElements.begin(); it != ob.GraphicElements.end(); it++) {
		os << "GraphicElement #" << counter;
		os << *it;
		counter++;
	}
	os << endl;
	os << "Output finished" << endl;
	return os;
}

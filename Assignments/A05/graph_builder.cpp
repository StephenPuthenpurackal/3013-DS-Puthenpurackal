///////////////////////////////////////////////////////////////////////////////
//
// Date:             28 October 2019
// Title:            Program 3 - Graphs
// Semester:         Spring 2018
// Course:           CMPS 3013 
// Assignment:       A05
// Author:           Stephen Puthenpurackal
// Email:            datfoosteve@gmail.com
// Files:            (list of source files)
// Description:
//       describe program here thoroughly
//
/////////////////////////////////////////////////////////////////////////////////


#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "JsonFacade.hpp"
#include "json.hpp"
#include "Geo.hpp"
#include "cityClass.hpp"
#include "cities.json"
#include "Heap.hpp"

using namespace std;
using json = nlohmann::json;


int main() {
ofstream outfile;
outfile.open("output.txt");

string CitiesInput = "cities.json";
json object;
JsonFacade JF(CitiesInput);

Cities **CityPointer;
Cities *ReadCity;

int SizeOfJsonFile = JF.getSize();
Heap<Cities> H(SizeOfJsonFile + 1,false);

CityPointer = new Cities *[SizeOfJsonFile];
for(int i = 0; i < SizeOfJsonFile; i++){
    object = JF.getNext();
    CityPointer[i] = new Cities(object);
}







return 0;  
}
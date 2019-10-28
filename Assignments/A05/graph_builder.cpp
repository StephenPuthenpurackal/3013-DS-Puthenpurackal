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
#include "Heap.hpp"

using namespace std;
using json = nlohmann::json;

struct City{
        string Name;
        int Population;
        double Longitude;
        double Latitude;
        int Rank;
        string State;
        double Priority;
        City(){
            Name = "";
            Population = 0;
            Longitude = 0.0;
            Latitude = 0.0;
            Rank = 0.0;
            State = "";
            Priority = 0.0;
        }
        City(json obj){
            Name = obj["city"];
            Population = obj["population"];
            Longitude = obj["longitude"];
            Latitude = obj["latitude"];
            Rank = obj["rank"];
            State = obj["state"];
            Priority = 0.0;            
        }
       // City(int P,string N, double Long,double Lat, int R, string St, double Pri):
      //  Population(P), Name(N), Longitude(Long), Latitude(Lat), Rank(R), State(St), Priority(Pri){}
    };

int main() {
// using Fstream library to open a text file called output.txt
ofstream outfile;
outfile.open("output.txt");

int count = 0;
double HaversineDistanceValue = 0;

// Creating instance of Json Class
// instantiating a Json Object
// And using a string with the name of the cities input json file in conjunction to
//                  instantiating an JsonFacade object.
string CitiesInput = "cities.json";
json object;
JsonFacade JF(CitiesInput);

// Creating 2 pointers of struct city
City **CityPointer;
City *ReadCity;

// Using the cities.json files size for the instantiation of SizeOfJsonfile
int SizeOfJsonFile = JF.getSize();
Heap<City> H(SizeOfJsonFile + 1,false);

// Creating an Array of pointers using the size of the json Cities file
CityPointer = new City *[SizeOfJsonFile];

// Iterating through every pointer and dynamically assigning new son struct objects on every pointer
for(int i = 0; i < SizeOfJsonFile; i++){
    object = JF.getNext();
    CityPointer[i] = new City(object);
    //outfile << i+1 << ": " << CityPointer[i]->Name << endl;

}

for(int i = 0; i < SizeOfJsonFile; i++){



if( i < 10 || i >= (SizeOfJsonFile - 10)){
    outfile << i+1 << ": " << CityPointer[i]->Name << endl;
}

for(int j = 0; j < SizeOfJsonFile; j++){

    Coordinate A(CityPointer[i]->Latitude, CityPointer[i]->Longitude);
    Coordinate B(CityPointer[j]->Latitude,CityPointer[j]->Longitude);

    HaversineDistanceValue = HaversineDistance(A,B);

    CityPointer[j]->Priority = HaversineDistanceValue;

    H.Insert(CityPointer[j]);
}

while (count < SizeOfJsonFile){

ReadCity = H.Extract();

if( i < 10 || i >= (SizeOfJsonFile - 10)){
    if(count <= 3){

        if(count == 1){
            if(ReadCity->Name != CityPointer[i]->Name){
            outfile << "\t" << count  << ")" << " " << ReadCity->Name << " (" << ReadCity->Priority << ") " << endl;
        }
        }

         if(count != 1){
        if(ReadCity->Name != CityPointer[i]->Name){
            outfile << "\t" << "\t" << count << ") " << ReadCity->Name << " (" << ReadCity->Priority << ") " << endl;
        }
        }
    }
}
count++;
ReadCity = NULL;
}
count = 0;
}

return 0;  
}
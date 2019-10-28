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
//#include "cityClass.hpp"
#include "cities.json"
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
            Population = 0;
            Name = "";
            Longitude = 0.0;
            Latitude = 0.0;
            Rank = 0.0;
            State = "";
            Priority = 0.0;
        }
        City(json obj){
            Name = obj["name"];
            Population = obj["population"];
            Longitude = obj["longitude"];
            Latitude = obj["latitude"];
            Rank = obj["rank"];
            State = obj["state"];
            Priority = 0.0;            
        }
        City(int P,string N, double Long,double Lat, int R, string St, double Pri):
        Population(P), Name(N), Longitude(Long), Latitude(Lat), Rank(R), State(St), Priority(Pri){}
    };

int main() {
ofstream outfile;
outfile.open("output.txt");

string CitiesInput = "cities.json";
json object;
JsonFacade JF(CitiesInput);

City **CityPointer;
City *ReadCity;

int SizeOfJsonFile = JF.getSize();
Heap<City> H(SizeOfJsonFile + 1,false);

CityPointer = new City *[SizeOfJsonFile];
for(int i = 0; i < SizeOfJsonFile; i++){
    object = JF.getNext();
    CityPointer[i] = new City(object);
}

//send in city pointer to class Cities C <-- the object function load cities






return 0;  
}
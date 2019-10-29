///////////////////////////////////////////////////////////////////////////////
//
// Date:             28 October 2019
// Title:            Program 3 - Graphs
// Semester:         Spring 2018
// Course:           CMPS 3013 
// Assignment:       A05
// Author:           Stephen Puthenpurackal
// Email:            datfoosteve@gmail.com
// Files:            Geo.hpp,Heap.hpp,json.hpp,JsonFacade.hpp,cities.json
// Description:
//       This program gives the user information on the distances between cities by
//       the use of Json files, heaps, loops, structs, classes, and algorithms
//       The distance is calculated by gathering 2 coordinates from 2 difference cities
//       and then inputed in the distance formula, known as the Haversine Formula.
//       As instructed, the program only uses the first 10 and the last 10 of the
//       json cities input as the decided output. Creating an array of pointers,
//       which point to json struct objects, the user can organize all information
//       easily by the use of heaps and the city objects priority. The information is then
//       printed in an output file. 
//
/////////////////////////////////////////////////////////////////////////////////


#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include "JsonFacade.hpp"
#include "json.hpp"
#include "Geo.hpp"
#include "Heap.hpp"

using namespace std;
using json = nlohmann::json;

//struct that is used to organize all city information used in the entire program
struct City{
        string Name;
        int Population;
        double Longitude;
        double Latitude;
        int Rank;
        string State;
        double Priority;
        // default constructor
        City(){
            Name = "";
            Population = 0;
            Longitude = 0.0;
            Latitude = 0.0;
            Rank = 0.0;
            State = "";
            Priority = 0.0;
        }
        // parameterized constructor using json file
        City(json obj){
            Name = obj["city"];
            Population = obj["population"];
            Longitude = obj["longitude"];
            Latitude = obj["latitude"];
            Rank = obj["rank"];
            State = obj["state"];
            Priority = 0.0;            
        }
        // user defined parameterized constructor, for easy access of all struct variables
        City(int P,string N, double Long,double Lat, int R, string St, double Pri):
        Population(P), Name(N), Longitude(Long), Latitude(Lat), Rank(R), State(St), Priority(Pri){}
    };

int main() {
// using Fstream library to open a text file called output.txt
ofstream outfile;
outfile.open("output.txt");

int count = 0;
// user can change how many cities that they want printed
int howManyCities = 3;
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
City *temp;

// Using the cities.json files size for the instantiation of SizeOfJsonfile
int SizeOfJsonFile = JF.getSize();
Heap<City> H(SizeOfJsonFile + 1,false);

// Creating an Array of pointers using the size of the json Cities file
CityPointer = new City *[SizeOfJsonFile];

// Iterating through every pointer and dynamically assigning new son struct objects on every pointer
for(int i = 0; i < SizeOfJsonFile; i++){
    object = JF.getNext();
    CityPointer[i] = new City(object);

}

// test code
/*H.Heapify(CityPointer,SizeOfJsonFile);
int b = 0;
while(!H.Empty()){
        temp = H.Extract();
        outfile <<b<<" "<<temp->Name<< " " <<temp->Priority << endl;
        b++;
}
*/

//Main loop that loops the size of the JsonFile , in this case 1000, 
// and has the abllity to change dynamically due to the size of the file
for(int i = 0; i < SizeOfJsonFile; i++){

// Prints the first 10 cities and last 10 cities that are first used to compare coordinate A
if( i < 10 || i >= (SizeOfJsonFile - 10)){
    outfile << setfill('0') << setw(4);
    outfile << i+1 << ": " << CityPointer[i]->Name << endl;
}

for(int j = 0; j < SizeOfJsonFile; j++){
    // Both coordinates used to evetually be inputed into Haversine Formula
    Coordinate A(CityPointer[i]->Latitude, CityPointer[i]->Longitude);
    Coordinate B(CityPointer[j]->Latitude,CityPointer[j]->Longitude);

    HaversineDistanceValue = HaversineDistance(A,B);

    // Priority is decided and struct objects priority is recorded
    CityPointer[j]->Priority = HaversineDistanceValue;
    // Inserts all needed objects into the heap
    H.Insert(CityPointer[j]);
}

// loop that runs until heap is empty by the size of the input json file
while (count < SizeOfJsonFile){

ReadCity = H.Extract();

// Another comparison that makes sure only the first 10 and the last 10 cities information is printed
if( i < 10 || i >= (SizeOfJsonFile - 10)){
    if(count <= howManyCities){
        // Use of iomanip and other forms of output manipulation to print neatly, the first city being different
        // then the second and third city output
        if(count == 1){
            if(ReadCity->Name != CityPointer[i]->Name){
            outfile << "\t" << count  << ")" << " " << ReadCity->Name << " (" << ReadCity->Priority << ") " << endl;
        }
        }
        // the rest print normally
         if(count != 1){
        if(ReadCity->Name != CityPointer[i]->Name){
            outfile << "\t" << "\t" << count << ") " << ReadCity->Name << " (" << ReadCity->Priority << ") " << endl;
        }
        }
    }
}
// incrementation and makes sure pointers go back to being null
count++;
ReadCity = NULL;
}
count = 0;
}

return 0;  
}
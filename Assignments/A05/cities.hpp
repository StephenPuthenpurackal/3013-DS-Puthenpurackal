#pragma once
#include <iostream>
#include <vector>
#include <string>

#include "JsonFacade.hpp"
#include "Geo.hpp"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

class Cities{
    private:
    struct City{
        int Population;
        string Name;
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
        City(int P,string N, double Long,double Lat, int R, string St, double Pri):
        Population(P), Name(N), Longitude(Long), Latitude(Lat), Rank(R), State(St), Priority(Pri){}
        
        City(json obj){
            Name = obj["Name"];
            Population = obj["Population"];
            Longitude = obj["Longitude"];
            Latitude = obj["Latitude"];
            Rank = obj["Rank"];
            State = obj["State"];
            Priority = 0.0;
        }
    };
    public:





};
#pragma once
#include <iostream>
#include <vector>
#include <string>

#include "JsonFacade.hpp"
#include "Geo.hpp"
#include "json.hpp"
#include "cities.json"

using namespace std;
using json = nlohmann::json;


class Cities{
    private:
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
        City(json &obj){
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
    public:





};
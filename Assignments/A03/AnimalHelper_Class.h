#include "json_helper.cpp"
#include <fstream>
#include <iostream>

#define _USE_MATH_DEFINES

#include <math.h>

using namespace std;

const static double EarthRadiusKm = 6372.8;

inline double DegreeToRadian(double angle) {
    return M_PI * angle / 180.0;
}

struct Animal {
    string animal_name;
    long date;
    double latitude;
    double longitude;
    float priority;
    bool validated;
    string version;

    Animal() {
        animal_name = "";
        date = 0;
        latitude = 0.0;
        longitude = 0.0;
        priority = 0.0;
        validated = 0;
        version = "";
    }

    Animal(string name, long _date, double lat, double lon, float pri, bool val, string ver) {
        animal_name = name;
        date = _date;
        latitude = lat;
        longitude = lon;
        priority = pri;
        validated = val;
        version = ver;
    }

    Animal(json j) {
        animal_name = j["animal_name"];
        date = j["date"];
        latitude = j["latitude"];
        longitude = j["longitude"];
        priority = j["priority"];
        validated = j["validated"];
        version = j["version"];
    }
};

class AnimalHelper {
private:
    Animal **Animals;
    JsonHelper *J;
    json obj;
    int size;

public:
    AnimalHelper(string filename) {
        J = new JsonHelper(filename);
        size = J->getSize();
        Animals = new Animal *[size];
        for (int i = 0; i < size; i++) {
            obj = J->getNext();
            Animals[i] = new Animal(obj);
        }
    }

    void PrintAnimals() {

        for (int i = 0; i < size; i++) {

            cout << Animals[i]->animal_name << " " 
            << Animals[i]->latitude << " " 
            << Animals[i]->longitude << " " 
            << Animals[i]->date << " " 
            << Animals[i]->priority << " " 
            << Animals[i]->validated << " " 
            << Animals[i]->version << endl;

        }
    }
};
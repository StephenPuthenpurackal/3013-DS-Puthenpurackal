//https://stackoverflow.com/questions/55116344/how-to-setup-vs-code-for-c-14-c-17
//https://github.com/nlohmann/json

#include "json_helper.cpp"
#include <fstream>
#include <iostream>
#include "AnimalHelper_Class.h"

#define _USE_MATH_DEFINES

#include <math.h>

using namespace std;

const static double EarthRadiusKm = 6372.8;

inline double DegreeToRadian(double angle) {
    return M_PI * angle / 180.0;
}


int main(int argc, char **argv) {

    AnimalHelper AH("animals.json");

    AH.PrintAnimals();

    return 0;
}
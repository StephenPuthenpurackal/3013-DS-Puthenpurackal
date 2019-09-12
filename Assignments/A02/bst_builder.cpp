#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "BST.h"

//http://www.webgraphviz.com/

using namespace std;



int main()
{
    srand(2342);

    BSTree B;

    B.AuxInsert(38);
    B.AuxInsert(10);
    B.AuxInsert(29);

    /*B.insert(27);
    B.insert(5);
    B.insert(43);
    B.insert(36);
    B.insert(3);
    B.printLevelOrder();
    B.GraphVizOut("before.txt");
    */
    return 0;
}
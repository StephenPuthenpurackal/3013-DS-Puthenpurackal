#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


class BSTree
{

vector<int> valueList;	// Holds the values presently in tree.
int size;

struct node
{
    int data;
    node*  left;
    node*  right;
    node(int dataa) : data(dataa),left(nullptr),right(nullptr){}
};
    node*  root;

    int count(node* r);
    void insert(node *&root, node *&temp);
    void print_node(node* n,string label = "");
    node* minValueNode(node* root);
    bool CheckBalance(node* root);
    int height(node* root);
    void printGivenLevel(node* root, int level);
    void GraphVizGetIds(node* nodePtr, ofstream &VizOut);
    void GraphVizMakeConnections(node* nodePtr, ofstream &VizOut);
public:

    BSTree();
    ~BSTree();
    int AuxCount();
    void AuxInsert(int x);
    void minValue();
    int AuxHeight();
    int top();
    void printLevelOrder();
    void GraphVizOut(string filename);



   
};
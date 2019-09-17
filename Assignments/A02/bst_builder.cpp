#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <time.h>
#include <set>

//http://www.webgraphviz.com/

using namespace std;

//************************************************************************
//  Node Structure which contains a data space, a left pointer space,
//  and a right pointer space. This struct also includesa parameterized
//  and unparameterized node constructor for easy or accessibility.
//
//************************************************************************

//************************************************************************
//  Binary Search tree class, which is used as a template for the entire.
//  Contains methods that calculates everything relating to a binary search
//  tree.
//
//************************************************************************
class BSTree
{
private:
    struct node
    {
        int data;
        node *left;
        node *right;
        node()
        {
            data = -1;
            left = NULL;
            right = NULL;
        }
        node(int x)
        {
            data = x;
            left = NULL;
            right = NULL;
        }
    };

    node *root;

    //************************************************************************
    //  Private node count function in which uses a recursive call on the
    //  root data to see how many nodes are in the entire list, traversing
    //  every single note. Example of the traveral is going left all the way
    //  until it does not reach a node , and then all the way to the right
    //  until the next value is null as well. Doing so returns the number one
    //  iteratively for every node. Adding these numbers will allow students to
    //  use this information to predict the count
    //************************************************************************
    int count(node *root)
    {
        if (!root)
        {
            return 0;
        }
        else
        {
            return 1 + count(root->left) + count(root->right);
        }
    }

    //************************************************************************
    //`insert function that inserts the value , depending what root is
    // , to the correct area of the Binary search tree
    //
    //
    //************************************************************************
    void insert(node *&root, node *&temp)
    {
        if (!root)
        {
            root = temp;
        }
        else
        {
            if (temp->data < root->data)
            {
                insert(root->left, temp);
            }
            else
            {
                insert(root->right, temp);
            }
        }
    }

    //************************************************************************
    //  Binary Search tree maker, uses recursive function to traverse and
    //  to organize data in a BST
    //
    //************************************************************************
    void BSTmake(vector<int> vec, int L, int R)
    {
        if (L > R)
        {
            return;
        }
        else
        {
            int mid = ((R + L)) / (2);
            insert(vec[mid]);
            BSTmake(vec, L, (mid - 1));
            BSTmake(vec, (mid + 1), R);
        }
    }

    //************************************************************************
    //  Print function that goes through the entire BST to print all data in
    //  order.
    //
    //
    //************************************************************************
    void print_node(node *n, string label = "")
    {
        if (label != "")
        {
            cout << "[" << label << "]";
        }
        cout << "[[" << n << "][" << n->data << "]]\n";
        if (n->left)
        {
            cout << "\t|-->[L][[" << n->left << "][" << n->left->data << "]]\n";
        }
        else
        {
            cout << "\t\\-->[L][null]\n";
        }
        if (n->right)
        {
            cout << "\t\\-->[R][[" << n->right << "][" << n->right->data << "]]\n";
        }
        else
        {
            cout << "\t\\-->[R][null]\n";
        }
    }

    /**
     * type = ['predecessor','successor']
     */
    //************************************************************************
    //This function basically uses an extra pointer to traverse all the way
    //through the BST until it hits a null, in which then the pointer that
    //was trailing can now be considered the lowest value and is
    //then printed as the minimum value of the entire tree
    //************************************************************************
    node *minValueNode(node *root)
    {
        node *current = root;

        if (root->right)
        {
            current = root->right;
            while (current->left != NULL)
            {
                current = current->left;
            }
        }
        else if (root->left)
        {
            current = root->left;
            while (current->right != NULL)
            {
                current = current->right;
            }
        }

        return current;
    }

    //************************************************************************
    // recursive diagnostic function which checks whether if the entire tree
    // is considered balanced by subtracting the height value of the
    // leftSubtree and the rightSubtree. This calculation is performed
    // in a absolute value function, and in doing so, helps calculate the
    // distance between the root node and the value being compared, whether
    // if it is in the left side or the right side. Having a value that larger
    // then 2 goes to show that the tree is not balanced on each side
    //************************************************************************
    bool CheckBalance(node *root)
    {

        int leftSubtree;
        int rightSubtree;

        if (!root)
        {
            return 1;
        }
        leftSubtree = height(root->left);
        rightSubtree = height(root->right);

        if (abs(leftSubtree - rightSubtree) <= 1 && CheckBalance(root->left) && CheckBalance(root->right))
        {
            return 1;
        }

        return 0;
    }

    //************************************************************************
    // Height function that returns the height value of the node in the tree
    // by recursively going through the tree as far bottom as you can, and
    // returning increments per level to reach maximum height of node.
    //************************************************************************
    int height(node *root)
    {
        if (!root)
        {
            return 0;
        }
        else
        {
            int left = height(root->left);
            int right = height(root->right);
            if (left > right)
            {
                return left + 1;
            }
            else
            {
                return right + 1;
            }
        }
    }

    //************************************************************************
    //  recursive depth function, which is very similiar to height , but
    //  can be used in a different way
    //************************************************************************
    int Depth(node *root, int value, int depth)
    {
        if (root == nullptr)
        {
            return -1;
        }
        if (value < root->data)
        {
            return Depth(root->left, value, depth + 1);
        }
        else
        {
            return Depth(root->right, value, depth + 1);
        }
        if (value == root->data)
        {
            return depth;
        }
    }

    //************************************************************************
    //  Checks whether the tree is complete,full, and/or balanced.
    //  Being able to understand that the max number of nodes in a tree with
    //  a certain height, can be used in the calculation ((2^height+1)-1)
    // which gives the total number of nodes to make a full tree.
    // we then check if that equals the number of nodes given,checked to see
    // whether if its balanced, and in by doing so , we are able to know
    // whether what the tree is.
    //************************************************************************
    void completeFULLorBALANCED(node *root)
    {
        bool completeTree = false;
        bool fullTree = false;
        bool balancedTree = false;

        int NumberOfNodes, AproxNumOfNodes;
        double AproxLevel;
        AproxLevel = (height(root));
        NumberOfNodes = count(root);
        AproxNumOfNodes = (pow(2.0, AproxLevel) - 1);
        if ((CheckleftSubtree(root) == false) && (CheckRightSubtree(root) == false))
        {
            // Comparisons of left subtrees to see whether if they are larger then each , if they are not
            // we can assume that the subtree counts are equal and say the tree is balanced.
            if (CheckBalance(root) == true)
            {
                balancedTree = true;
            }
        }

        if (NumberOfNodes == AproxNumOfNodes)
        {
            fullTree = true;
        }
        if ((CheckleftSubtree(root) == false) && (CheckRightSubtree(root) == false) && (fullTree))
        {
            //If left subtree and right subtree are not larger then each other, and if its a full tree
            // then we can assume the tree is a complete
            completeTree = true;
        }
        if (balancedTree == 1 && completeTree == 1 && fullTree == 1)
        {
            cout << "This Tree is considered Balanced,Complete, and full" << endl;
        }
        else if (completeTree == 1 && balancedTree == 1)
        {
            cout << "This Tree is considered Balanced,Complete, and full" << endl;
        }
        else if (fullTree == 1)
        {
            cout << "This Tree is considered only full" << endl;
        }
        else if (completeTree == 1)
        {
            cout << "This Tree is considered complete" << endl;
        }
        else if (balancedTree == 1)
        {
            cout << "This Tree is considered only balanced" << endl;
        }
        else
        {
            cout << "This tree is not considered balanced,full,or complete." << endl;
        }
    }

    //************************************************************************
    // Successor Delete function.
    //
    //************************************************************************
    void SDelete(node *root, int v)
    {
        // Case 0: Finding the Node that = v
        // Case 0:A
        // Check whether if the root is pointing to a node
        // If it is, we jump out of function
        if (root == nullptr)
        {
            return;
        }
        // Case 0:B
        // Check whether the value is either less than or greater than
        // the key, if it is , we must go further left or right
        // until we reach a node that is not greater nor less
        // then the value we passed in, meaning value must equal node value.
        if (v < root->data)
        {
            SDelete(root->left, v);
        }
        else if (v > root->data)
        {
            SDelete(root->right, v);
        }

        ///////////////////////// CASE 1:///////////////////////////////////////
        // The start of our first case. This represents that we have
        // found the value passed in this function.
        // We must check first whether if this node has no children.
        // if it has both children, we delete that node and return.
        // No need to replace value
        else
        {
            if (root->left == nullptr && root->right == nullptr)
            {
                delete root;
                root = nullptr;
                return;
            }
            else
            {
                /////////////////////////////// Case 2://///////////////////////
                // This case means the node that was found equal to
                // our value has one child. We must delete that node
                // while making parent nodes pointers point in the right
                // direction. We do this by having multiple trailing pointers
                node *ptr = nullptr;
                node *follower = nullptr;
                // Case 2:Option 1
                if (root->left == nullptr)
                {
                    node *temp = root->right;
                    delete root;
                    root = temp;
                    return;
                }
                // Case 2:Option 2
                else if (root->right == nullptr)
                {
                    node *temp = root->left;
                    delete root;
                    root = temp;
                    return;
                }
                else
                {
                    ///////////////////////////////// Case 3:////////////////////
                    // Last and Final Case, must check to see whether
                    // the node we found has both kids, left and right.
                    // This requires us to splice out a node.
                    ptr = root->right;
                    follower = ptr;

                    // Case 3:Option A
                    // Splicing Node
                    if (ptr->left == nullptr)
                    {

                        root->right = ptr->right; //<---- Shows how we are replacing
                        root->data = ptr->data;   //<------- this node by trailing ptr

                        delete ptr;
                        ptr = nullptr;
                        return;
                    }
                    // If we have both children and still not hit a nullptr,
                    // we keep going left until we do.
                    // Note:: Successor delete
                    // Go right once, then left all the way down
                    // Note:: Predessor delete ->
                    // Go left once, then right all the way down
                    while (ptr->left != nullptr)
                    {

                        follower = ptr;
                        ptr = ptr->left;
                    }

                    // Case B:Option B
                    root->data = ptr->data;
                    if (ptr->right != nullptr)
                    {
                        follower->left = ptr->right;
                        delete ptr;
                        ptr = nullptr;
                    }
                    else
                    {
                        follower->left = nullptr;
                        delete ptr;
                        ptr = nullptr;
                    }
                }
            }
        }
    }

    //************************************************************************
    // Predecessor Delete function.
    //
    //************************************************************************
    void PDelete(node *&root, int v)
    {
        // Case 0: Finding the Node that = v
        // Case 0:A
        // Check whether if the root is pointing to a node
        // If it is, we jump out of function
        if (root == nullptr)
        {
            return;
        }
        // Case 0:B
        // Check whether the value is either less than or greater than
        // the key, if it is , we must go further left or right
        // until we reach a node that is not greater nor less
        // then the value we passed in, meaning value must equal node value.
        if (v < root->data)
        {
            PDelete(root->left, v);
        }
        else if (v > root->data)
        {
            PDelete(root->right, v);
        }

        ///////////////////////// CASE 1:///////////////////////////////////////
        // The start of our first case. This represents that we have
        // found the value passed in this function.
        // We must check first whether if this node has no children.
        // if it has both children, we delete that node and return.
        // No need to replace value
        else
        {
            if (root->left == nullptr && root->right == nullptr)
            {
                delete root;
                root = nullptr;
                return;
            }

            /////////////////////////////// Case 2://///////////////////////////
            // This case means the node that was found equal to
            // our value has one child. We must delete that node
            // while making parent nodes pointers point in the right
            // direction. We do this by having multiple trailing pointers
            node *ptr = nullptr;
            node *follower = nullptr;
            // Case 2:Option 1
            if (root->left == nullptr)
            {
                node *temp = root->right;
                delete root;
                root = temp;
                return;
            }
            // Case 2:Option 2
            else if (root->right == nullptr)
            {
                node *temp = root->left;
                delete root;
                root = temp;
                return;
            }
            else
            {
                ///////////////////////////////// Case 3:///////////////////////////////////
                // Last and Final Case, must check to see whether
                // the node we found has both kids, left and right.
                // This requires us to splice out a node.
                ptr = root->left;
                follower = ptr;

                // Case 3:Option A
                // Splicing Node
                if (ptr->right == nullptr)
                {

                    root->left = ptr->left; //<---- Shows how we are replacing
                    root->data = ptr->data; //<------- this node by trailing ptr

                    delete ptr;
                    ptr = nullptr;
                    return;
                }
                // If we have both children and still not hit a nullptr,
                // we keep going left until we do.
                // Note:: Successor delete
                // Go right once, then left all the way down
                // Note:: Predessor delete ->
                // Go left once, then right all the way down
                while (ptr->right != nullptr)
                {

                    follower = ptr;
                    ptr = ptr->right;
                }

                // Case B:Option B
                root->data = ptr->data;
                if (ptr->left != nullptr)
                {
                    follower->right = ptr->left;
                    delete ptr;
                    ptr = nullptr;
                }
                else
                {
                    follower->right = nullptr;
                    delete ptr;
                    ptr = nullptr;
                }
            }
        }
    }

    /* Print nodes at a given level */
    //************************************************************************
    // Recursive Function that prints the values depending what level it is.
    // Useful to check values of certain rows instead of traversing entire
    // BST.
    //************************************************************************
    void printGivenLevel(node *root, int level)
    {
        if (root == NULL)
            return;
        if (level == 1)
        {
            print_node(root);
        }
        else if (level > 1)
        {
            printGivenLevel(root->left, level - 1);
            printGivenLevel(root->right, level - 1);
        }
    }
    //************************************************************************
    // Method to help create GraphViz code so the expression tree can
    // be visualized. This method prints out all the unique node id's
    // by traversing the tree.
    // Recivies a node pointer to root and performs a simple recursive
    // tree traversal.
    //************************************************************************
    void GraphVizGetIds(node *nodePtr, ofstream &VizOut)
    {
        static int NullCount = 0;
        if (nodePtr)
        {
            GraphVizGetIds(nodePtr->left, VizOut);
            VizOut << "node" << nodePtr->data
                   << "[label=\"" << nodePtr->data << "\\n"
                   //<<"Add:"<<nodePtr<<"\\n"
                   //<<"Par:"<<nodePtr->parent<<"\\n"
                   //<<"Rt:"<<nodePtr->right<<"\\n"
                   //<<"Lt:"<<nodePtr->left<<"\\n"
                   << "\"]" << endl;
            if (!nodePtr->left)
            {
                NullCount++;
                VizOut << "nnode" << NullCount << "[label=\"X\",shape=point,width=.15]" << endl;
            }
            GraphVizGetIds(nodePtr->right, VizOut);
            if (!nodePtr->right)
            {
                NullCount++;
                VizOut << "nnode" << NullCount << "[label=\"X\",shape=point,width=.15]" << endl;
            }
        }
    }

    //************************************************************************
    // This method is partnered with the above method, but on this pass it
    // writes out the actual data from each node.
    // Don't worry about what this method and the above method do, just
    // use the output as your told:)
    //************************************************************************
    void GraphVizMakeConnections(node *nodePtr, ofstream &VizOut)
    {
        static int NullCount = 0;
        if (nodePtr)
        {
            GraphVizMakeConnections(nodePtr->left, VizOut);
            if (nodePtr->left)
                VizOut << "node" << nodePtr->data << "->"
                       << "node" << nodePtr->left->data << endl;
            else
            {
                NullCount++;
                VizOut << "node" << nodePtr->data << "->"
                       << "nnode" << NullCount << endl;
            }

            if (nodePtr->right)
                VizOut << "node" << nodePtr->data << "->"
                       << "node" << nodePtr->right->data << endl;
            else
            {
                NullCount++;
                VizOut << "node" << nodePtr->data << "->"
                       << "nnode" << NullCount << endl;
            }

            GraphVizMakeConnections(nodePtr->right, VizOut);
        }
    }

public:
    //************************************************************************
    //Binary Search tree constructor, just initilizes the root to null
    //without having any nodes in the list
    //
    //************************************************************************
    BSTree()
    {
        root = NULL;
    }

    //************************************************************************
    //Binary Search Tree Destructor, which deallocates all BST memory.
    //************************************************************************
    ~BSTree()
    {
        DestroyTree(root);
    }

    //************************************************************************
    //  auxiliary count function which sends in root information to Actual
    //  Count function
    //
    //************************************************************************
    int count()
    {
        return count(root);
    }

    //************************************************************************
    //  auxiliary insert function which sends in root information to Actual
    //  insert function
    //
    //************************************************************************
    void insert(int x)
    {
        node *temp = new node(x);
        insert(root, temp);
    }

    //************************************************************************
    //
    //
    //
    //************************************************************************
    void DestroyTree(node *r)
    {
        if (r == nullptr)
        {
            return;
        }
        else
        {
            DestroyTree(r->left);
            DestroyTree(r->right);
            delete r;
            r = nullptr;
        }
    }

    //************************************************************************
    //  auxiliary makrBalanced function which sends in root information to Actual
    //  balance function
    //
    //************************************************************************
    void makeBalanced(vector<int> vec)
    {
        int L = 0;
        int R = vec.size() - 1;
        BSTmake(vec, L, R);
    }
    //************************************************************************
    //  auxiliary minValue function which sends in root information to Actual
    //  minValue function
    //
    //************************************************************************
    void minValue()
    {
        print_node(minValueNode(root), "minVal");
    }

    //************************************************************************
    //  auxiliary Diagnostic check functions that makes sure the
    //  tree is complete,full,or balanced, by sending root information
    //  to the actual completeFUllorBalanced function, which is parameterized.
    //************************************************************************
    void completeFULLorBALANCED()
    {
        return completeFULLorBALANCED(root);
    }

    //************************************************************************
    //  auxiliary Diagnostic check functions that makes sure the
    //  tree is balanced by sending root information to the actual
    //  checkBalance function, which is parameterized.
    //************************************************************************
    void CheckBalance()
    {
        cout << "===============Checking Whether if the Tree is balanced===================" << endl;
        bool result = CheckBalance(root);
        if (result == 1)
        {
            cout << "The Tree is Balanced" << endl;
        }
        else if (result == 0)
        {
            cout << "The Tree is not Balanced" << endl;
        }

        cout << "===============Checking Whether if the Tree is balanced===================" << endl;
    }

    //************************************************************************
    // Checks the height of everything that is left of the root
    // and everything that is right of the root,
    // and returns true or false due to comparison of the left and right
    //************************************************************************
    bool CheckleftSubtree(node *root)
    {
        return height(root->left) > height(root->right);
    }

    //************************************************************************
    // Checks the height of everything that is right of the root
    // and everything that is left of the root,
    // and returns true or false due to comparison of the right and left
    //************************************************************************
    bool CheckRightSubtree(node *root)
    {
        return height(root->right) > height(root->left);
    }

    //************************************************************************
    // Function that sends in root data to the actual height function
    //
    //
    //************************************************************************
    int height()
    {

        return height(root);
    }

    //************************************************************************
    // Function that sends in root data to the actual depth function
    //
    //
    //************************************************************************
    int depth()
    {
        return Depth(root, root->data, 0);
    }

    //************************************************************************
    // Function returns the Root node data value
    // which is considered the top of the list, or the front.
    // If the node is not the top, this function returns nothing
    //************************************************************************
    int top()
    {
        if (root)
            return root->data;
        else
            return 0;
    }

    //************************************************************************
    // A function used to print the tree
    // in Level order traversal going
    // line by line
    //************************************************************************
    void printLevelOrder()
    {
        cout << "Begin Level Order===================\n";
        int h = height(root);
        int i;
        for (i = 1; i <= h; i++)
        {
            printGivenLevel(root, i);
            cout << "\n";
        }
        cout << "End Level Order===================\n";
    }

    //************************************************************************
    // Recieves a filename to place the GraphViz data into.
    // It then calls the above two graphviz methods to create a data file
    // that can be used to visualize your expression tree.
    //************************************************************************
    void GraphVizOut(string filename)
    {
        ofstream VizOut;
        VizOut.open(filename);
        VizOut << "Digraph G {\n";
        GraphVizGetIds(root, VizOut);
        GraphVizMakeConnections(root, VizOut);
        VizOut << "}\n";
        VizOut.close();
    }
};

int main()
{
    // Uses time here so we can sorta get random numbers.
    srand(time(NULL));
    int x = rand() % 11 + 1;

    // Set class objects allow for insertion of values that are unique and sorted
    set<int> VectorSet;

    BSTree B;

    for (int i = 0; i <= (pow(2.0, x) - 2); i++)
    {
        // load list with random # of nodes between 0 and 100000
        int value = rand() % 100000;

        // This makes sure you still insert again even though the value
        // is a dupicate
        if (VectorSet.insert(value).second == false)
        {
            i--;
        }
        else
        {
            VectorSet.insert(value);
        }
    }

    //Initilized vector with set size
    //and then proceeds to copy the rest of the variables into vector for
    // the BST
    vector<int> TreeVector(VectorSet.size());
    copy(VectorSet.begin(), VectorSet.end(), TreeVector.begin());

    B.makeBalanced(TreeVector);
    B.CheckBalance();
    B.completeFULLorBALANCED();
    B.printLevelOrder();
    B.GraphVizOut("before.txt");

    return 0;
}
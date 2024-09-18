#ifndef IODIALOGUE_H_INCLUDED
#define IODIALOGUE_H_INCLUDED

#include <iostream>
#include <sstream>
#include <list>

using namespace std;

namespace IODialog
{

/*
 *
 * BSTree I/O Functions
 *
*/

void showBSTreeOperation()
{
    cout << " 1. Add nodes\t\t\t 2. Delete node" << endl
         << " 3. Get minimum node\t\t 4. Get maximum node" << endl
         << " 5. Get successor of node\t 6. Get predecessor of node" << endl
         << " 7. Show tree\t\t\t 8. Show inorder traversal" << endl
         << " 9. Compute tree depth\t\t 10. Exit" << endl
         << "Enter your choice (1-10): ";
}


int getBSTreeOperation()
{
    int option = 0;
    while (true)
    {
        showBSTreeOperation();
        if (!(cin >> option))
        {
            cout << "Unknown option. Try again." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
        else if (option < 1 || option > 10)
        {
            cout << "Unknown option. Try again." << endl;
        }
        else
        {
            cout << "Proceed with selection " << option << " .." << endl;
            cin.ignore(10000, '\n');
            break;
        }
    }
    return option;
}

void getBSTreeNodeKeys(list<int>& nodeKeys)
{
    cout << "Type in the keys of the nodes: " << flush;
    int key;
    string line;
    if (getline(cin,line))
    {
        istringstream iss(line);
        while (iss >> key)
        {
            nodeKeys.push_back(key);
        }
    }
}

int getBSTreeNodeKey()
{
    cout << "Type in the key of the node: ";
    int k;
    cin >> k;
    return k;
}

/*
 *
 * RBTree I/O Functions
 *
*/

void showRBTreeOperation()
{
    cout << " 1. Add nodes\t\t\t 2. Delete node" << endl
         << " 3. Get minimum node\t\t 4. Get maximum node" << endl
         << " 5. Get successor of node\t 6. Get predecessor of node" << endl
         << " 7. Show tree\t\t\t 8. Show inorder traversal" << endl
         << " 9. Show black-height\t\t 10. Show max key of black nodes" << endl
         << " 11. Show max key of red nodes\t 12. Compute tree depth" << endl
         << " 13. Exit" << endl
         << "Enter your choice (1-13): ";
}

int getRBTreeOperation()
{
    int option = 0;
    while (true)
    {
        showRBTreeOperation();
        if (!(cin >> option))
        {
            cout << "Unknown option. Try again." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
        else if (option < 1 || option > 13)
        {
            cout << "Unknown option. Try again." << endl;
        }
        else
        {
            cout << "Proceed with selection " << option << " .." << endl;
            cin.ignore(10000, '\n');
            break;
        }
    }
    return option;
}

void getRBNodeKeys(list<int>& nodeKeys)
{
    cout << "Type in the keys of the nodes: " << flush;
    int key;
    string line;
    if (getline(cin,line))
    {
        istringstream iss(line);
        while (iss >> key)
        {
            nodeKeys.push_back(key);
        }
    }
}

int getRBNodeKey()
{
    cout << "Type in the key of the node: ";
    int k;
    cin >> k;
    return k;
}

/*
 *
 * BTree I/O Functions
 *
*/

}

#endif // IODIALOGUE_H_INCLUDED

#include <iostream>
#include <cstdlib>
#include "BSTree.h"
#include "IODialogue.h"
#include "RBTree.h"
#include "BTree.h"

using namespace std;

/*
 *
 *BINARY SEARCH TREE MAIN FUNCTIONS
 *
*/

void startProcessing(BSTree*);

void perform(BSTree*, int);

void startProcessing(BSTree* tree)
{
    int op;
    while (true)
    {
        op = IODialog::getBSTreeOperation();
        perform(tree, op);
    }
}

void perform(BSTree* tree, int op)
{
    list<int> nodeKeys;
    Node* nod;
    int skey;
    switch (op)
    {
    case 1: // Add nodes
        IODialog::getBSTreeNodeKeys(nodeKeys);
        for (list<int>::iterator it = nodeKeys.begin();
                it !=nodeKeys.end(); it++)
            tree->insert(tree->createNode(*it));
        break;
    case 2: // Delete node
        skey = IODialog::getBSTreeNodeKey();
        nod = tree->search(tree->root, skey);
        if (nod != 0) tree->del(nod);
        else cout << "Node not found" << endl;
        break;
    case 3: // Get minimum node
        nod = tree->minimum(tree->root);
        if (nod == 0 ) cout << "Minimum not found" << endl;
        else cout << "Minimum is: " << nod->toString() << endl;
        break;
    case 4: // Get maximum node
        nod = tree->maximum(tree->root); // tree->maximum(Node*) must be implemented!
        if (nod == 0) cout << "Maximum not found" << endl;
        else cout << "Maximum is: " << nod->toString() << endl;
        break;
    case 5: // Get successor of specified node
        skey = IODialog::getBSTreeNodeKey();
        nod = tree->search(tree->root, skey);
        if (nod != 0)
        {
            nod = tree->successor(nod);
            if (nod == 0)
                cout << "Node with key " << skey << " has no successor.\n";
            else cout << "Successor is: " << nod->toString() << '\n';
        }
        else cout << "Node not found.\n";
        break;
    case 6: // Get predecessor of specified node
        skey = IODialog::getBSTreeNodeKey();
        nod = tree->search(tree->root, skey);
        if (nod != 0)
        {
            nod = tree->predecessor(nod); // tree->predecessor(Node*) must be implemented!
            if (nod == 0) cout << "Node with key " << skey << " has no predecessor.\n";
            else cout << "Predecessor is: " << nod->toString() << '\n';
        }
        else cout << "Node not found.\n";
        break;
    case 7: // Show the nodes of tree in indented form
        tree->indentedDisplay();
        break;
    case 8:
        cout << "\nInorder traversal of the tree yields" << endl << ' ';
        tree->inorder();
        cout << endl;
        break;
    case 9: // Compute and show tree depth of tree
        cout << "The depth of the tree is " << tree->depth() << endl;
        break;
    case 10: // Exit
        delete tree;
        cout << "Bye!" << endl;
        exit (0);
    }
}

/*
 *
 * RED BLACK TREE MAIN FUNCTIONS
 *
*/

void startProcessing(RBTree*);

void perform(RBTree*, int);

void startProcessing(RBTree* RB)
{
    int o;
    while (true)
    {
        o = IODialog::getRBTreeOperation();
        perform(RB, o);
    }
}

void perform(RBTree* RB, int o)
{
    list<int> nodeKeys;
    RBNode* rbn;
    int skey;
    switch (o)
    {
    case 1: // Add nodes
        IODialog::getRBNodeKeys(nodeKeys);
        for (list<int>::iterator it = nodeKeys.begin();
                it !=nodeKeys.end(); it++)
            RB->RBInsert(RB->createNode(*it));
        break;
    case 2: // Delete node
        skey = IODialog::getRBNodeKey();
        rbn = RB->search(RB->root, skey);
        if (!RB->isNil(rbn)) RB->del(rbn);
        else cout << "RB: Node not found" << endl;
        break;
    case 3: // Get minimum node
        rbn = RB->minimum(RB->root);
        if (RB->isNil(rbn) ) cout << "RB: Minimum not found" << endl;
        else cout << "RB: Minimum is: " << rbn->toString() << endl;
        break;
    case 4: // Get maximum node
        rbn = RB->maximum(RB->root); // RB->maximum(RBNode*) must be implemented!
        if (RB->isNil(rbn) ) cout << "RB: Maximum not found" << endl;
        else cout << "RB: Maximum is: " << rbn->toString() << endl;
        break;
    case 5: // Get successor of specified node
        skey = IODialog::getRBNodeKey();
        rbn = RB->search(RB->root, skey);
        if (!RB->isNil(rbn))
        {
            rbn = RB->successor(rbn);
            if (RB->isNil(rbn))
                cout << "RB: Node has no successor.\n";
            else cout << "RB: Successor is: " << rbn->toString() << '\n';
        }
        else cout << "RB: Node not found.\n";
        break;
    case 6: // Get predecessor of specified node
        skey = IODialog::getRBNodeKey();
        rbn = RB->search(RB->root, skey);
        if (!RB->isNil(rbn))
        {
            rbn = RB->predecessor(rbn); // RB->predecessor(RBNode*) must be implemented!
            if (RB->isNil(rbn)) cout << "RB: Node has no predecessor.\n";
            else cout << "RB: Predecessor is: " << rbn->toString() << '\n';
        }
        else cout << "RB: Node not found.\n";
        break;
    case 7: // Show tree RB
        RB->indentedDisplay();
        break;
    case 8:
        cout << "\nInorder traversal of RB tree yields" << endl << ' ';
        RB->inorder();
        cout << endl;
        break;
    case 9: // show black-height of RB
        cout << "The black-height of the RB tree is " << RB->bh() << endl;
        break;
    case 10: // show the maximum key of BLACK nodes of RB
        cout << "The max key of a black node in the RB tree is " << RB->maxBlackKey() << endl;
        break;
    case 11: // show the maximum key of RED nodes of RB
        cout << "The max key of a red node in the RB tree is " << RB->maxRedKey() << endl;
        break;
    case 12: // Compute and show tree depth of RB
        cout << "The tree depth of RB is " << RB->depth() << endl;
        break;
    case 13: // Exit
        delete RB;
        cout << "Bye!" << endl;
        exit (0);
    }
}

/*
 *
 * BTREE MAIN FUNCTIONS
 *
*/

void getBNodeKeys(list<int>&);

void showBTreeOperation()
{
    cout << " 1. Add nodes\t\t\t 2. Delete node" << endl
         << " 3. Get minimum node\t\t 4. Get maximum node" << endl
         << " 5. Get predecessor \t\t 6. Get successor" << endl
         << " 7. Show tree\t\t\t 8. Show tree content (inorder traversal)" << endl
         << " 9. Exit" << endl
         << "Enter your choice (1-9): ";
}

int getBTreeOperation()
{
    int option = 0;
    while (true)
    {
        showBTreeOperation();
        if (!(cin >> option))
        {
            cout << "Unknown option. Try again." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
        else if (option < 1 || option > 9)
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

void perform(BTree* B, int o)
{
    list<int> nodeKeys;
    int k;
    switch (o)
    {
    case 1: /* Add nodes -- DONE */
        getBNodeKeys(nodeKeys);
        for (list<int>::iterator it = nodeKeys.begin();
                it !=nodeKeys.end(); it++)
            B->insert(*it);
        break;
    case 2: /* delete node */
        ///************************
        cout << "Key for deletion: ";
        cin >> k;
        B->del(k);
        ///************************
        break;
    case 3: /* get minimum key */
        cout << "Mininum is " << B->min(B->root)<<endl;
        break;
    case 4: /* get maximum key */
        cout << "Maximum is " << B->max(B->root)<<endl;
        break;
    case 5: /* find predecessor */
        cout << "Get key of node for which to find predecessor: ";
        cin >> k;
        cout << "Predecessor: " << B->predecessor(B->root,k) << endl;
        break;
    case 6: /* find successor */
        cout << "Get key of node for which to find successor: ";
        cin >> k;
        cout << "Successor: " << B->successor(B->root,k) << endl;
        break;
    case 7:
        B->indentedDisplay();
        break;
    case 8:
        B->inorderDisplay(B->root);
        cout << endl;
        break;
    case 9:
        cout << "Exit" << endl;
        break;
    }
}

void getBNodeKeys(list<int>& nodeKeys)
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

int main()
{
    system("color 1f");

    int choice = 0;

    while(choice != 4){

    cout<<"-= Data Structures Visualizer =-"<<endl;
    cout<<"1. BSTree "<<endl;
    cout<<"2. RBTree "<<endl;
    cout<<"3. BTree "<<endl;
    cout<<"4. Exit "<<endl;
    cout<<"Enter your choice: ";

    cin>>choice;

    switch (choice)
    {
    case 1:
    {
        BSTree* tree = new BSTree();
        startProcessing(tree);
        delete tree;
        break;
    }
    case 2:
    {
        RBTree* RB = new RBTree();
        startProcessing(RB);
        delete RB;
        break;
    }
    case 3:
    {
        cout<< "Indicate the desired branching factor t: ";
        int t;
        cin >> t;
        BTree* Btree = new BTree(t);
        int o = 1;
        while (o != 9)
        {
            o = getBTreeOperation();
            perform(Btree, o);
        }
        delete Btree;
        break;
    }
    case 4:
    {
        return 0;
    }
    default:
    {
        cout << "Invalid choice\n";
        break;
    }
    }
    }
}

#ifndef RBTREE_H_INCLUDED
#define RBTREE_H_INCLUDED

#include <string>
#include <iostream>
#include <sstream>
#include <cmath>
#include <queue>
#include <windows.h>

using namespace std;


struct RBNode
{
    int key;        // key
    RBNode *parent; // pointer to parent
    RBNode *left;   // pointer to left child
    RBNode *right;  // pointer to right child
    enum color { RED, BLACK };
    color col;

    static RBNode* Nil; // sentinel leaf node

    RBNode(int k, RBNode *l = Nil, RBNode *r = Nil, RBNode *p = Nil, color c = RBNode::BLACK) :
        key(k), parent(p), left(l), right(r), col(c) { }

    string toString()
    {
        ostringstream os;
        os << key << ((col == RBNode::RED) ? ":r" : ":b");
        return os.str();
    }

    ~RBNode()
    {
        if (this != Nil)
        {
            if(left != Nil)
                delete left;
            if(right != Nil)
                delete right;
        }
    }

};

RBNode* RBNode::Nil = new RBNode(0);

struct RBTree
{
    RBNode* root;

    RBTree()
    {
        root = RBNode::Nil;
    }
    ~RBTree()
    {
        delete root;
    }

    RBNode* createNode(int key)
    {
        return new RBNode(key);
    }

    bool isNil(RBNode* n)
    {
        return (n == RBNode::Nil);
    }

    RBNode* search(RBNode* w, int key)
    {
        if (isNil(w) || w->key == key)
            return w;
        return search( (key < w->key) ? w->left : w->right, key);
    }

    /**
     * LeftRotate(x) method affecting node x and its
     * right child y
     */
    void LeftRotate(RBNode* x)
    {
        // Set y
        RBNode* y = x->right;
        // Turn y's left subtree into x's right subtree
        x->right = y->left;
        if (y->left != RBNode::Nil)
            y->left->parent = x;
        // link x's parent to y
        y->parent = x->parent;
        if (x->parent == RBNode::Nil)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
        // Put x on y's left
        y->left = x;
        x->parent = y;
    }

    /**
     * RightRotate(y) method affecting node y and its
     * left child x
     */
    void RightRotate(RBNode* y)
    {
        // Set x
        RBNode* x = y->left;
        // Turn x's right subtree into y's left subtree
        y->left = x->right;
        if (x->right != RBNode::Nil)
            x->right->parent = y;
        // link y's parent to x
        x->parent = y->parent;
        if (y->parent == RBNode::Nil)
            root = x;
        else if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
        // Put y on x's right
        x->right = y;
        y->parent = x;
    }

    /**
     * maximum(w) returns the node with maximum key in the
     * RB-tree with root node w
     */
    RBNode* maximum(RBNode* w)
    {
        RBNode* x = w;
        while (!isNil(x->right))
            x = x->right;
        return x;
    }

    /**
     * minimum(w) returns the node with minimum key in the
     * RB-tree with root node w
     */
    RBNode* minimum(RBNode* w)
    {
        RBNode* x = w;
        while (!isNil(x->left))
            x = x->left;
        return x;
    }

    /**
     * successor(w) returns the successor of node w in the
     * RB-tree to which node w belongs
     */
    RBNode* successor(RBNode* w)
    {
        if(isNil(w)) return w;
        RBNode* x = w;
        if (!isNil(x->right))
            return minimum(x->right);
        RBNode* y = x->parent;
        while (!isNil(y) && x == y->right)
        {
            x = y;
            y = x->parent;
        }
        return y;
    }

    RBNode* predecessor(RBNode* w)
    {
        if(isNil(w)) return w;
        RBNode* x = w;
        if (!isNil(x->left))
            return maximum(x->left);
        RBNode* y = x->parent;
        while (!isNil(y) && x == y->left)
        {
            x = y;
            y = x->parent;
        }
        return y;
    }


    /**
     * RBInsert(z) inserts node z in this RB-tree
     */
    void RBInsert(RBNode* z)
    {
        // insert like in a binary search tree
        RBNode *y = RBNode::Nil;
        RBNode *x = root;
        while (!isNil(x))
        {
            y = x;
            x = (z->key < x->key) ? x->left : x->right;
        }
        z->parent = y;
        if (isNil(y))
            root = z;
        else if (z->key < y->key)
            y->left = z;
        else
            y->right = z;
        z->left = z->right = RBNode::Nil;
        z->col = RBNode::RED;
        RBInsertFixup(z);

        std::cout<<"Inserting node "<<z->key<<":"<<std::endl;
        indentedDisplay();
    }

    RBNode* del(RBNode* z)
    {
        RBNode *y = (isNil(z->left) || isNil(z->right)) ? z : successor(z);
        RBNode *x = !isNil(y->left) ? y->left : y->right;
        x->parent = y->parent;
        if(isNil(y->parent))
        {
            root = x;
        }
        else
        {
            if (y == y->parent->left)
                y->parent->left = x;
            else
                y->parent->right = x;
        }
        if (y != z)
        {
            z->key = y->key;
            // copy y's satellite data into z
        }
        if (y->col == RBNode::BLACK)
            RBDeleteFixup(x);
        return y;
    }

    void inorder(RBNode* T)
    {
        if (!isNil(T))
        {
            inorder(T->left);
            cout << T->toString() << ' ';
            inorder(T->right);
        }
    }

    void inorder()
    {
        if (isNil(root))
        {
            cout << "empty";
        }
        else
            inorder(root);
    }

    void indentedDisplay()
    {
        indentedDisplay(root);
    }

    void indentedDisplay(RBNode* root)
    {
        std::queue<RBNode*> treeLevel, temp;
        treeLevel.push(root);
        int counter = 0;
        int height = depth(root);
        double numberOfElements = pow(2, (height + 1)) - 1;
        while (counter <= height) {
            RBNode* removed = treeLevel.front();
            treeLevel.pop();
            if (temp.empty()) {
                printSpace(numberOfElements / pow(2, counter + 1), removed);
            }
            else {
                printSpace(numberOfElements / pow(2, counter), removed);
            }
            if (removed == RBNode::Nil) {
                temp.push(RBNode::Nil);
                temp.push(RBNode::Nil);
            }
            else {
                temp.push(removed->left);
                temp.push(removed->right);
            }
            if (treeLevel.empty()) {
                std::cout << std::endl << std::endl;
                treeLevel = temp;
                while (!temp.empty()) {
                    temp.pop();
                }
                counter++;
            }
        }
    }

    void printSpace(double n, RBNode* removed)
    {
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        for (; n > 0; n--) {
            std::cout << "\t";
        }
        if (removed == RBNode::Nil) {
            SetConsoleTextAttribute(h, FOREGROUND_INTENSITY); // Light gray for Nil nodes
            std::cout << " ";
            SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN); // Reset to default color
        }
        else {
            if (removed->col == RBNode::RED) {
                SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY); // Light red for RED nodes
            }
            else {
                SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN); // Light gray for BLACK nodes
            }
            std::cout << removed->key << ((removed->col == RBNode::RED) ? ":r" : ":b");
            SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN); // Reset to default color
        }
    }
    /**
     * Compute the depth of the tree with root x
     */
    int depth(RBNode* x)
    {
        if (isNil(x))
        {
            return -1;
        }
        else
        {
            int lDepth = depth(x->left);
            int rDepth = depth(x->right);
            return (lDepth<rDepth ? rDepth : lDepth)+1;
        }
    }

    /**
     * Compute the depth of this red-black tree
     */
    int depth()
    {
        return depth(root);
    }

    // auxiliary method
    int countBlacks(RBNode* x)
    {
        if(isNil(x)) return 1;
        int n = countBlacks(x->left);
        return ((x->col == RBNode::RED)? n : n+1);
    }

    /**
     * Compute the black-height of the red-black tree with the root in x
     */
    int bh(RBNode* x)
    {
        if (isNil(x))
            return 1;
        int leftBlackHeight = bh(x->left);
        int rightBlackHeight = bh(x->right);
        if (leftBlackHeight != rightBlackHeight || x->col == RBNode::RED)
            return -1;  // Red violation or uneven black heights
        return leftBlackHeight + (x->col == RBNode::BLACK ? 1 : 0);
    }

    /**
     * Compute the black-height of this red-black tree
     */
    int bh()
    {
        return bh(root);
    }

    /* return the maximum key of black nodes.
     * If the tree is empty, return -1000
     */
    int maxBlackKey()
    {
        if (isNil(root))
            return -1000;  // or some other value to indicate an empty tree
        RBNode* x = root;
        while (!isNil(x->right))
            x = x->right;
        while (x->col == RBNode::RED)
            x = predecessor(x);
        return x->key;
    }

    /* return the maximum key of red nodes.
     * If the tree has no red nodes, return -1000
     */
    int maxRedKey()
    {
        if (isNil(root))
            return -1000;  // or some other value to indicate an empty tree
        RBNode* x = root;
        while (!isNil(x->right))
            x = x->right;
        while (x->col == RBNode::BLACK)
            x = predecessor(x);
        return x->key;
    }


    void RBInsertFixup(RBNode* z)
    {
        while (z->parent->col == RBNode::RED)
        {
            if (z->parent == z->parent->parent->left)
            {
                RBNode* y = z->parent->parent->right;
                if (y->col == RBNode::RED)
                {
                    z->parent->col = RBNode::BLACK;
                    y->col = RBNode::BLACK;
                    z->parent->parent->col = RBNode::RED;
                    z = z->parent->parent;
                }
                else
                {
                    if (z == z->parent->right)
                    {
                        z = z->parent;
                        LeftRotate(z);
                    }
                    z->parent->col = RBNode::BLACK;
                    z->parent->parent->col = RBNode::RED;
                    RightRotate(z->parent->parent);
                }
            }
            else
            {
                RBNode* y = z->parent->parent->left;
                if (y->col == RBNode::RED)
                {
                    z->parent->col = RBNode::BLACK;
                    y->col = RBNode::BLACK;
                    z->parent->parent->col = RBNode::RED;
                    z = z->parent->parent;
                }
                else
                {
                    if (z == z->parent->left)
                    {
                        z = z->parent;
                        RightRotate(z);
                    }
                    z->parent->col = RBNode::BLACK;
                    z->parent->parent->col = RBNode::RED;
                    LeftRotate(z->parent->parent);
                }
            }
        }
        root->col = RBNode::BLACK;
    }
    void RBDeleteFixup(RBNode* x)
{
    while (x != root && x->col == RBNode::BLACK)
    {
        if (x == x->parent->left)
        {
            RBNode* w = x->parent->right;
            if (w->col == RBNode::RED)
            {
                w->col = RBNode::BLACK;
                x->parent->col = RBNode::RED;
                LeftRotate(x->parent);
                w = x->parent->right;
            }
            if (w->left->col == RBNode::BLACK && w->right->col == RBNode::BLACK)
            {
                w->col = RBNode::RED;
                x = x->parent;
            }
            else
            {
                if (w->right->col == RBNode::BLACK)
                {
                    w->left->col = RBNode::BLACK;
                    w->col = RBNode::RED;
                    RightRotate(w);
                    w = x->parent->right;
                }
                w->col = x->parent->col;
                x->parent->col = RBNode::BLACK;
                w->right->col = RBNode::BLACK;
                LeftRotate(x->parent);
                x = root;
            }
        }
        else
        {
            RBNode* w = x->parent->left;
            if (w->col == RBNode::RED)
            {
                w->col = RBNode::BLACK;
                x->parent->col = RBNode::RED;
                RightRotate(x->parent);
                w = x->parent->left;
            }
            if (w->right->col == RBNode::BLACK && w->left->col == RBNode::BLACK)
            {
                w->col = RBNode::RED;
                x = x->parent;
            }
            else
            {
                if (w->left->col == RBNode::BLACK)
                {
                    w->right->col = RBNode::BLACK;
                    w->col = RBNode::RED;
                    LeftRotate(w);
                    w = x->parent->left;
                }
                w->col = x->parent->col;
                x->parent->col = RBNode::BLACK;
                w->left->col = RBNode::BLACK;
                RightRotate(x->parent);
                x = root;
            }
        }
    }
    x->col = RBNode::BLACK;
}

};

#endif // RBTREE_H_INCLUDED

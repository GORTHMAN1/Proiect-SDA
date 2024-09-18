#ifndef BSTREE_H_INCLUDED
#define BSTREE_H_INCLUDED

#include <string>
#include <iostream>
#include <sstream>
#include <cmath>
#include <queue>

struct Node
{
    int key;      // key
    Node *parent; // pointer to parent
    Node *left;   // pointer to left child
    Node *right;  // pointer to right child

    static Node* Nil;

    Node(int k, Node *l = Nil, Node *r = Nil, Node *p = Nil) :
        key(k), parent(p), left(l), right(r) { }

    std::string toString()
    {
        std::ostringstream os;
        os << key;
        return os.str();
    }

    ~Node()
    {
        if(left != Node::Nil)
            delete left;
        if(right != Node::Nil)
            delete right;
    }
};

Node* Node::Nil = new Node(0);

struct BSTree
{
    Node* root;

    /* Default constructor: creates an empty tree */
    BSTree()
    {
        root = Node::Nil;
    }

    ~BSTree()
    {
        delete root;
    }

    Node* createNode(int key)
    {
        return new Node(key);
    }

    /**
     * return the node with key k from this tree, and null
     * if no such node exists
     */
    Node* search(int k)
    {
        return search(root, k);
    }

    Node* search(Node* w, int key)
    {
        if (w == Node::Nil || w->key == key)
            return w;
        return search( (key < w->key) ? w->left : w->right, key);
    }

    Node* maximum(Node* w)
    {
        Node *x = w;
        if (x != Node::Nil)
        {
            while (x->right != Node::Nil)
                x = x->right;
            return x;
        }
        return Node::Nil;
    }

    Node* minimum(Node* w)
    {
        Node* x = w;
        while (x->left != Node::Nil)
            x = x->left;
        return x;
    }

    /**
     * return a pointer to the successor of node w in
     * this binary search tree
     */
    Node* successor(Node* w)
    {
        if (w->right != Node::Nil)
            return minimum(w->right);
        Node* x = w;
        Node* y = w->parent;
        while (y != Node::Nil && x == y->right)
        {
            x = y;
            y = y->parent;
        }
        return y;
    }

    /**
     * return a pointer to the predecessor of node w in
     * this binary search tree
     */
    Node* predecessor(Node* w)
    {
        if (w->left != Node::Nil)
            return maximum(w->left);

        Node* y = w->parent;
        while (y != Node::Nil && w == y->left)
        {
            w = y;
            y = y->parent;
        }
        return y;
    }

    /*
     * Insert node z at the right place in the binary search tree
     */
    void insert(Node* z)
    {
        Node* y = Node::Nil;
        Node* x = root;

        while (x != Node::Nil)
        {
            y = x;
            if (z->key < x->key)
                x = x->left;
            else
                x = x->right;
        }

        z->parent = y;

        if (y == Node::Nil)
            root = z;
        else if (z->key < y->key)
            y->left = z;
        else
            y->right = z;

        std::cout<<"Inserting node "<<z->key<<":"<<std::endl;
        indentedDisplay();
    }

    /**
     * Removes node z from this tree
     */
    Node* del(Node* z)
{
    if (z->left == Node::Nil)
        transplant(z, z->right);
    else if (z->right == Node::Nil)
        transplant(z, z->left);
    else
    {
        Node* y = minimum(z->right);
        if (y->parent != z)
        {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
    }

    return z;
}

void transplant(Node* u, Node* v)
{
    if (u->parent == Node::Nil)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;

    if (v != Node::Nil)
        v->parent = u->parent;
}

    /**
     * This method performs the traversal in inorder
     * of the nodes of a binary tree.
     */
    void inorder(Node* T)
    {
        if (T != Node::Nil)
        {
            inorder(T->left);
            std::cout << T->toString() << ' ';
            inorder(T->right);
        }
    }

    void inorder()
    {
        inorder(root);
    }

    /**
     * Auxiliary method to display the content of a binary tree
     * in an indented way.
     */
    void indentedDisplay()
    {
        indentedDisplay(root);
    }

    void indentedDisplay(Node* root)
    {
    std::queue<Node*> treeLevel, temp;
    treeLevel.push(root);
    int counter = 0;
    int height = depth(root);
    double numberOfElements = pow(2, (height + 1)) - 1;
    while (counter <= height) {
        Node* removed = treeLevel.front();
        treeLevel.pop();
        if (temp.empty()) {
            printSpace(numberOfElements
                           / pow(2, counter + 1),
                       removed);
        }
        else {
            printSpace(numberOfElements / pow(2, counter),
                       removed);
        }
        if (removed == nullptr) {
            temp.push(nullptr);
            temp.push(nullptr);
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
    int depth()
    {
        return depth(root);
    }

    int depth(Node* n)
    {
        if(n == Node::Nil)
            return -1;
        else
        {
            int lDepth = depth(n->left);
            int rDepth = depth(n->right);

            if(lDepth > rDepth)
                return lDepth + 1;
            else
                return rDepth + 1;
        }
    }

    void printSpace(double n, Node* removed)
    {
        for (; n > 0; n--) {
            std::cout << "\t";
        }
        if (removed == nullptr) {
            std::cout << " ";
        }
        else {
            std::cout << removed->key;
        }
    }
};

#endif // BSTREE_H_INCLUDED

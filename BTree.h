#ifndef BTREE_H_
#define BTREE_H_

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

struct BNode
{
    int n;
    int *keys;
    BNode **children;
    bool leaf;

    BNode(const int t)
    {
        keys = new int[2 * t - 1];
        children = new BNode *[2 * t];
        leaf = true;
        n = 0;
    }

    ~BNode()
    {
        delete[] children;
    }

    /**
     * caută cheia în nodul curent
     */
    int findKey(int k)
    {
        int i = 0;
        while (i < n && keys[i] < k)
            i++;
        return i;
    }
};

struct BTree
{
    BNode *root; // rădăcina arborelui
    int t;       // factorul de ramificare

    BTree(int); // se va folosi contructorul în loc de create()
    ~BTree();
    BNode *allocateNode();
    BNode *search(BNode *x, int key);
    int min(BNode *w);
    int max(BNode *w);
    void insert(int key);
    void insertNonfull(BNode *x, int k);
    void splitChild(BNode *, int, BNode *);

    void del(int key);
    void del(BNode *x, int k);
    int successor(BNode *x, int k);
    int predecessor(BNode *x, int k);
    void removeFromLeaf(BNode *x, int i);
    void removeFromNonLeaf(BNode *x, int i);
    void fill(BNode *x, int i);
    void borrowFromLeft(BNode *x, int i);
    void borrowFromRight(BNode *x, int i);
    void merge(BNode *x, int i);

    void display(BNode *, int);
    void inorderDisplay(BNode *);
    void indentedDisplay(BNode*, int);
    void indentedDisplay();

    int depth(BNode* c);
    void printSpace(double n, BNode* b);

    void diskRead(BNode *);
    void diskWrite(BNode *);
};

BNode *BTree::allocateNode()
{
    return new BNode(t);
}

BTree::BTree(int i) : t(i)
{
    BNode *x = allocateNode();
    diskWrite(x);
    root = x;
}

BTree::~BTree()
{
    delete root;
}

BNode *BTree::search(BNode *x, int k)
{
    int i = 0;
    while (i < x->n && k > x->keys[i])
        i++;
    if (i < x->n && k == x->keys[i])
        return x;
    if (x->leaf)
        return 0;
    else
    {
        diskRead(x->children[i]);
        return search(x->children[i], k);
    }
}

int BTree::min(BNode *w)
{
    return w->leaf ? w->keys[0] : min(w->children[0]);
}

int BTree::max(BNode *w)
{
    return w->leaf ? w->keys[w->n - 1] : max(w->children[w->n]);
}

void BTree::splitChild(BNode *x, int i, BNode *y)
{
    BNode *z = allocateNode();
    z->leaf = y->leaf;
    z->n = t - 1;
    for (int j = 0; j <= t - 2; j++)
        z->keys[j] = y->keys[j + t];
    if (!y->leaf)
        for (int j = 0; j <= t - 1; j++)
            z->children[j] = y->children[j + t];
    y->n = t - 1;
    for (int j = x->n; j >= i + 1; j--)
    {
        x->children[j + 1] = x->children[j];
        x->keys[j] = x->keys[j - 1];
    }
    x->children[i + 1] = z;
    x->keys[i] = y->keys[t - 1];
    x->n = 1 + x->n;
    diskWrite(y);
    diskWrite(z);
    diskWrite(x);
}

void BTree::insertNonfull(BNode *x, int k)
{
    int i = x->n - 1;
    if (x->leaf)
    {
        while (i >= 0 && k < x->keys[i])
        {
            x->keys[i + 1] = x->keys[i];
            i--;
        }
        x->keys[i + 1] = k;
        x->n = x->n + 1;
        diskWrite(x);
    }
    else
    {
        while (i >= 0 && k < x->keys[i])
            i--;
        i++;
        diskRead(x->children[i]);
        if (x->children[i]->n == 2 * t - 1)
        {
            splitChild(x, i, x->children[i]);
            if (k > x->keys[i])
                i++;
        }
        insertNonfull(x->children[i], k);
    }
}

void BTree::insert(int k)
{
    BNode *r = root;
    if (r->n == 2 * t - 1)
    {
        BNode *s = allocateNode();
        root = s;
        s->leaf = false;
        s->n = 0;
        s->children[0] = r;
        splitChild(s, 0, r);
        insertNonfull(s, k);
    }
    else
        insertNonfull(r, k);
}

void BTree::diskRead(BNode *x) {}

void BTree::diskWrite(BNode *x) {}

void BTree::indentedDisplay(BNode* x, int indent)
{
    if (x == nullptr)
        return;

    std::queue<BNode*> treeLevel, temp;
    treeLevel.push(x);
    int counter = 0;
    int height = depth(x);

    while (counter <= height)
    {
        BNode* removed = treeLevel.front();
        treeLevel.pop();

        if (temp.empty())
        {
            printSpace((double)pow(2, height - counter - 1), removed);
        }
        else
        {
            printSpace((double)pow(2, height - counter), removed);
        }

        if (removed != nullptr)
        {
            for (int i = 0; i < removed->n; i++)
                std::cout << removed->keys[i] << ' ';

            if (!removed->leaf)
            {
                for (int i = 0; i <= removed->n; i++)
                    temp.push(removed->children[i]);
            }
            else
            {
                temp.push(nullptr);
                temp.push(nullptr);
            }
        }
        else
        {
            temp.push(nullptr);
            temp.push(nullptr);
        }

        if (treeLevel.empty())
        {
            std::cout << std::endl << std::endl;
            treeLevel = temp;
            while (!temp.empty())
            {
                temp.pop();
            }
            counter++;
        }
    }
}

int BTree::depth(BNode* node)
{
    if (node == nullptr)
        return 0;
    int leftDepth = depth(node->children[0]);
    int rightDepth = depth(node->children[1]);
    return 1 + std::max(leftDepth, rightDepth);
}

void BTree::printSpace(double n, BNode* removed)
{
    for (; n > 0; n--)
    {
        std::cout << "\t";
    }

    if (removed == nullptr)
    {
        std::cout << " ";
    }
}

void BTree::inorderDisplay(BNode *x)
{
    bool b = x->leaf;
    for (int i = 0; i < x->n; i++)
    {
        if (!b)
            inorderDisplay(x->children[i]);
        cout << x->keys[i] << ' ';
    }
    if (!b)
        inorderDisplay(x->children[x->n]);
}

void BTree::indentedDisplay()
{
    cout << "The B-tree is" << endl;
    //indentedDisplay(root, 0);
    void display(Node *, int);
}

void BTree::display(BNode *x, int indent)
{
    if (x == 0)
        return;
    bool b = x->leaf;
    for (int i = 0; i < x->n; i++)
    {
        if (!b)
            display((x->children)[i], indent + 2);
        for (int j = 0; j < indent; j++)
            cout << ' ';
        cout << (x->keys)[i] << '\n';
    }
    if (!b)
        display((x->children)[x->n], indent + 2);
}

int BTree::successor(BNode *x, int k)
{
    int i = 0;
    while (i < x->n && k > x->keys[i])
        i++;

    if (!x->leaf)
    {
        diskRead(x->children[i]);
        return successor(x->children[i], k);
    }
    else if (i < x->n)
    {
        return x->keys[i];
    }
    else
    {
        while (x->leaf && i == x->n && x)
            x = x->children[i];

        if (x)
        {
            diskRead(x);
            return successor(x, k);
        }
        else
            return -1;
    }
}

int BTree::predecessor(BNode *x, int k)
{
    int i = 0;
    while (i < x->n && k > x->keys[i])
        i++;

    if (!x->leaf)
    {
        diskRead(x->children[i]);
        return predecessor(x->children[i], k);
    }
    else if (i > 0)
    {
        return x->keys[i - 1];
    }
    else
    {
        while (x->leaf && i == 0 && x)
            x = x->children[i];

        if (x)
        {
            diskRead(x);
            return predecessor(x, k);
        }
        else
            return -1;
    }
}

void BTree::del(int k)
{
    if (!root)
    {
        cout << "The tree is empty\n";
        return;
    }

    del(root, k);

    if (root->n == 0)
    {
        BNode *tmp = root;
        if (root->leaf)
            root = NULL;
        else
            root = root->children[0];

        delete tmp;
    }
    return;
}

void BTree::del(BNode *x, int k)
{
    int i = x->findKey(k);

    if (i < x->n && x->keys[i] == k)
    {
        if (x->leaf)
            removeFromLeaf(x, i);
        else
            removeFromNonLeaf(x, i);
    }
    else
    {
        if (x->leaf)
        {
            cout << "The key " << k << " does not exist in the tree\n";
            return;
        }

        bool last = ((i == x->n) ? true : false);

        if (x->children[i]->n < t)
            fill(x, i);

        if (last && i > x->n)
            del(x->children[i - 1], k);
        else
            del(x->children[i], k);
    }
    return;
}

void BTree::removeFromLeaf(BNode *x, int i)
{
    for (int j = i + 1; j < x->n; j++)
        x->keys[j - 1] = x->keys[j];

    x->n--;

    return;
}

void BTree::removeFromNonLeaf(BNode *x, int i)
{
    int k = x->keys[i];

    if (x->children[i]->n >= t)
    {
        int pred = max(x->children[i]);
        x->keys[i] = pred;
        del(x->children[i], pred);
    }
    else if (x->children[i + 1]->n >= t)
    {
        int succ = min(x->children[i + 1]);
        x->keys[i] = succ;
        del(x->children[i + 1], succ);
    }
    else
    {
        merge(x, i);
        del(x->children[i], k);
    }
}

void BTree::fill(BNode *x, int i)
{
    if (i != 0 && x->children[i - 1]->n >= t)
        borrowFromLeft(x, i);
    else if (i != x->n && x->children[i + 1]->n >= t)
        borrowFromRight(x, i);
    else
    {
        if (i != x->n)
            merge(x, i);
        else
            merge(x, i - 1);
    }
    return;
}

void BTree::borrowFromLeft(BNode *x, int i)
{
    BNode *child = x->children[i];
    BNode *sibling = x->children[i - 1];

    for (int j = child->n - 1; j >= 0; j--)
        child->keys[j + 1] = child->keys[j];

    if (!child->leaf)
    {
        for (int j = child->n; j >= 0; j--)
            child->children[j + 1] = child->children[j];
    }

    child->keys[0] = x->keys[i - 1];

    if (!child->leaf)
        child->children[0] = sibling->children[sibling->n];

    x->keys[i - 1] = sibling->keys[sibling->n - 1];

    child->n += 1;
    sibling->n -= 1;

    return;
}

void BTree::borrowFromRight(BNode *x, int i)
{
    BNode *child = x->children[i];
    BNode *sibling = x->children[i + 1];

    child->keys[(child->n)] = x->keys[i];

    if (!(child->leaf))
        child->children[(child->n) + 1] = sibling->children[0];

    x->keys[i] = sibling->keys[0];

    for (int j = 1; j < sibling->n; j++)
        sibling->keys[j - 1] = sibling->keys[j];

    if (!sibling->leaf)
    {
        for (int j = 1; j <= sibling->n; j++)
            sibling->children[j - 1] = sibling->children[j];
    }

    child->n += 1;
    sibling->n -= 1;

    return;
}

void BTree::merge(BNode *x, int i)
{
    BNode *child = x->children[i];
    BNode *sibling = x->children[i + 1];
    child->keys[t - 1] = x->keys[i];

    for (int j = 0; j < sibling->n; j++)
        child->keys[j + t] = sibling->keys[j];
    if (!child->leaf)
    {
        for (int j = 0; j <= sibling->n; j++)
            child->children[j + t] = sibling->children[j];
    }

    for (int j = i + 1; j < x->n; j++)
        x->keys[j - 1] = x->keys[j];

    for (int j = i + 2; j <= x->n; j++)
        x->children[j - 1] = x->children[j];

    child->n = 2 * t - 1;
    x->n--;

    delete sibling;

    diskWrite(child);
    diskWrite(x);
}

#endif /* BTREE_H_ */

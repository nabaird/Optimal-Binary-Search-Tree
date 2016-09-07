#ifndef OBST_H_INCLUDED
#define OBST_H_INCLUDED
#include <iostream>
#include <string>

using namespace std;

class bst
{
private:
    struct node//nodes of the BST
    {
        node(string);
        string word;
        char value;
        node* left;
        node* right;
    };

    struct nodeOpt//temp nodes storing data for optimization routine
    {
        nodeOpt();
        string root;
        int index;
        float prob;
    };

    bst(bst&);
    bst& operator=(bst&);

public:
    bst();
    ~bst();
    bool Add(string);
    bool Remove(string);
    bool Search(string);
    void Clear();
    void OptimizeBst(string *values, float *probs, int theSize);//takes a sorted array, as well as an array with the related probabilities (they match up one-to-one) and the size of both arrays and builds an OBST out of them
    void ReturnRootOrder();

private:
    void Erase(node*);
    bool FindLoc(string, node*);
    node* root;
    void OBSTInsert(nodeOpt, nodeOpt*, int, int, int);//takes input from OptimizeBst and recursively constructs the bst
    void PreOrderTraversal(node*, int);
};

#endif

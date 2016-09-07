#include<iostream>
#include<string>
#include "OBST.h"

using namespace std;

bst::node::node(string x)
{
    word = x;
    value = x.front();
    left = nullptr;
    right = nullptr;
}

bst::nodeOpt::nodeOpt()
{
    root = ' ';
    prob = 0;
    index = -1;
}

bst::bst()
{
    root = nullptr;
}

bst::~bst()
{
    if(root)
    {
        Erase(root);
    }
}

bool bst::Add(string x)
{
    if(root)
    {
        return FindLoc(x,root);
    }
    else
    {
        root = new node(x);
        return true;
    }
}

bool bst::Remove(string x)
{
    node* reader = nullptr;
    node* thisRoot = root;
    bool done = false;

    while(thisRoot && !done)
    {
        if(x.front()<thisRoot->value)
        {
            reader = thisRoot;
            thisRoot=thisRoot->left;
        }
        else if(x.front()>thisRoot->value)
        {
            reader = thisRoot;
            thisRoot=thisRoot->right;
        }
        else
        {
            done = true;
        }
    }

    if(thisRoot)//if the node was found
    {
        if(thisRoot->left && thisRoot->right)//node has 2 children
        {

            node* valFinder;
            valFinder = thisRoot->right;
            while(valFinder->left)
            {
                valFinder=valFinder->left;
            }
            string swapVal = valFinder->word;
            Remove(swapVal);

            thisRoot->word = swapVal;
        }
        else if(thisRoot->left)//if node has a left child
        {
            if(x.front()<reader->value)
            {
                reader->left = thisRoot->left;
                delete thisRoot;

            }
            else
            {
                reader->right = thisRoot->left;
                delete thisRoot;

            }
        }
        else if(thisRoot->right)//if node has a right child
        {
            if(x.front()<reader->value)
            {
                reader->left = thisRoot->right;
                delete thisRoot;

            }
            else
            {
                reader->right = thisRoot->right;
                delete thisRoot;

            }
        }
        else//node has 0 children
        {
            delete thisRoot;
            if(x.front()<reader->value)
            {
                reader->left = nullptr;
            }
            else
            {
                reader->right = nullptr;
            }

        }
    return true;
    }
    else
    {
        return false; //the node was not found
    }
}

bool bst::Search(string x)
{
    node* thisRoot= root;
    while(thisRoot)
    {
        if(x.front()<thisRoot->value)
        {
            thisRoot=thisRoot->left;
        }
        else if(x.front()>thisRoot->value)
        {
            thisRoot=thisRoot->right;
        }
        else
        {
            return true;
        }
    }
    return false;
}

void bst::Clear()
{
    if(root)
    {
       Erase(root);
    }
    root=nullptr;
}

bool bst::FindLoc(string x, node* thisRoot)//Only called when root is non-null
{
    node* reader = nullptr;
    while(thisRoot)
    {
        if(x.front()<thisRoot->value)
        {
            reader = thisRoot;
            thisRoot=thisRoot->left;
        }
        else if(x.front()>thisRoot->value)
        {
            reader = thisRoot;
            thisRoot=thisRoot->right;
        }
        else if(x.front()==thisRoot->value)
        {
            return false;
        }
    }
    if(x.front()<reader->value)
    {
        reader->left=new node(x);
    }
    else
    {
        reader->right=new node(x);
    }

    return true;
}

void bst::Erase(node* thisRoot)
{
    if(thisRoot->left)
    {
        Erase(thisRoot->left);
    }
    if(thisRoot->right)
    {
        Erase(thisRoot->right);
    }

    delete thisRoot;
}

void bst::OptimizeBst(string *values, float *probs, int theSize)
{
    nodeOpt *theArray = new nodeOpt[theSize*theSize];//a two dimensional array. 'theArray[i][j]' is instead written as 'theArray[i*theSize+j]'

    for(int i=0; i<theSize;i++)
    {
        theArray[i].root = values[i];
        theArray[i].prob = probs[i];
        theArray[i].index = i;
    }

    for(int i=1; i<theSize;i++)//number of iterations
    {
        for(int j=0;j<theSize;j++)//the nodes we fill per iteration
        {
            if(j+i<theSize)
            {
                float minProb=0;//we want to keep track of the lowest probability thus far, so we can replace it with anything lower
                string minRoot;
                int indexRoot = -1;
                float totalProb=0;//no need to continuously compute the total prob as it remains the same
                int left=j;
                int right = j+i;

                for(int u=0; u<=right-left;u++)//right-left delivers the size of the series, but does not overestimate it in terms of index values
                {
                    totalProb += probs[left+u];
                }

                for(int u=0; u<=right-left;u++)//u refers to the u'th value in the series we are testing as a root
                {
                    float leftProb=0;

                    if(left+u>left)
                    {
                        leftProb=theArray[(u-1)*theSize+left].prob;//u-1 delivers the number of values int the series prior to u, which is the level of iteration we want to check
                    }

                    float rightProb=0;

                    if(left+u<right)
                    {
                        rightProb=theArray[(right-left-u-1)*theSize+left+u+1].prob;//we take the series size and subtract u to get the number of values to the right of the root. However we want to decrement that value by 1, since one of those values will have been a root in a previous iteration
                    }

                    float finalProb = totalProb+leftProb+rightProb;

                    if(minProb>0)
                    {
                        if(finalProb<minProb)
                        {
                            minProb= finalProb;
                            minRoot= values[left+u];
                            indexRoot= j+u;
                        }
                    }
                    else
                    {
                        minProb= finalProb;
                        minRoot= values[left+u];
                        indexRoot= j+u;
                    }

                }
                nodeOpt theNode;
                theNode.root = minRoot;
                theNode.prob = minProb;
                theNode.index = indexRoot;

                theArray[i*theSize+j] = theNode;
            }
        }
    }

    OBSTInsert(theArray[(theSize-1)*theSize], theArray,0, theSize-1, theSize);//We pass the array to a recursive function which reads out the proper root ordering

    delete theArray;
}

void bst::OBSTInsert(nodeOpt thisNode, nodeOpt *theArray, int left, int right, int theSize)
{
    Add(thisNode.root);

    if(thisNode.index-1-left>=0)
    {
        OBSTInsert(theArray[(thisNode.index-1-left)*theSize+left], theArray, left, thisNode.index-1, theSize);//Find and insert the left root
    }

    if(right-thisNode.index-1>=0)
    {
        OBSTInsert(theArray[(right-thisNode.index-1)*theSize+thisNode.index+1], theArray, thisNode.index+1, right, theSize);
    }
}

void bst::ReturnRootOrder()
{
    if(root)
    {
       PreOrderTraversal(root,0);
    }

}

void bst::PreOrderTraversal(node *x, int level)
{
    cout<<x->word<<" level "<<level<<"\n";
    level++;
    if(x->left)
    {
        PreOrderTraversal(x->left, level);
    }

    if(x->right)
    {
        PreOrderTraversal(x->right, level);
    }

}





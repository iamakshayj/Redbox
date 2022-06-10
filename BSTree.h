// Akshay Jagadeesh
// axj190048
#ifndef BSTree_h
#define BSTree_h
#include "Node.h"
#include "DVD.h"
#include <iostream>
#include <fstream>
#include <iomanip>
template<typename T>
class BSTree
{
    public:
    //constructor
        BSTree<T>();
    //destructor
        ~BSTree<T>(){};
    //BSTree functions
        void add(Node<T>* node);
        void addnode(Node<T>* root, Node<T>* node, Node<T>* parent);
        bool find(Node<T>* node, Node<T>* curr);
        void remove(Node<T>* curr, Node<T>* parent);
        void print(Node<T>* parent);
        Node<T>* getRoot() {return root;}
        void setRoot(Node<T>* node) {root=node;}
    private:
        Node<T>* root;
};

template<typename T>
BSTree<T>::BSTree(){root=NULL;}
//helper function to add node to the root
template<typename T>
void BSTree<T>::add(Node<T>* node)
{
    addnode(root, node, NULL);
}
//adds node with root
template<typename T>
void BSTree<T>::addnode(Node<T>* curr, Node<T>* node, Node<T>* parent)
{
    //if root is null the new node is root
    if (root == nullptr)
        root = node;
    //if current node is less than new node
    else if (*node>*curr)
    {
        //checks if right child is null to add new node or else searches again with right node as current
        if(curr->getRight() == nullptr)
            curr->setRight(node);
        else
            addnode(curr->getRight(), node, curr);
    }
    //if current node is greater than new node
    else if (*node<*curr)
    {
        //checks if left child is null to add new node or else searches again with left node as current
        if(curr->getLeft() == nullptr)
            curr->setLeft(node);
        else
            addnode(curr->getLeft(), node, curr);
    }
    //if current node is same as new node
    else 
    {
        //updates available DVDs for the title
        curr->Payload()->setAvai(curr->getPayload().getAvai() + node->getPayload().getAvai());
        //updates rented DVDs for the title
        curr->Payload()->setRent(curr->getPayload().getRent() + node->getPayload().getRent());
        //if available and rented DVD's are 0 then deletes node by passing in current node and parent node to remove function
        if (curr->Payload()->getAvai()==0 && curr->Payload()->getRent() == 0)
          remove(curr,parent);
    }
}
//checks if a node title is in the binary search tree and returns true/false
template<typename T>
bool BSTree<T>::find(Node<T>* curr, Node<T>* node)
{
    //If current node is null, then node is not found
    if(curr == nullptr)
        return false;
    //If current node is less than node, then searches again with right node as current
    if(*node>*curr)
        return find(curr->getRight(), node);
    //If current node is greater than node, then searches again with left node as current
    else if(*node<*curr)
        return find(curr->getLeft(), node);
    //If node is found in the tree, then returns true
    else
        return true;
    return false;
}
//removes a node with its parent node
template<typename T>
void BSTree<T>::remove(Node<T>* cur, Node<T>* prev)
{
    //if node has 0 children
    if (!(cur->getLeft() || cur->getRight()))
    {
        //if the node to be deleted is root
        if (!prev)
            root = nullptr;
        //if the node to be deleted is left of parent
        else if(prev->getLeft() == cur)
            prev->setLeft(nullptr);
        //if the node to be deleted is right of parent
        else
            prev->setRight(nullptr);
    }
    //if node has two children
    else if (cur->getLeft() && cur->getRight())
    {
        //temporary node to hold to be deleted node
        Node<T> *hold = cur;
        prev = cur;
        //node moves to left subtree
        cur = cur->getLeft();
        //find max of left subtree
        while (cur->getRight())
        {
            prev = cur;
            cur = cur->getRight();
        }
        //cur points to rightmost node in left subtree
        //check if max of left subtree is root of left subtree and sets parent to node's left child
        if (prev->getLeft() == cur)
            prev->setLeft(cur->getLeft());
        //check if max of left subtree is root of right subtree and sets parent to node's right child
        else
            prev->setRight(cur->getLeft());
        //swap nodes with temporary payload
        T* temp = hold->Payload();
        hold->setPayload(cur->Payload());
        cur->setPayload(temp);
        cur->setLeft(nullptr);  //disconnect node
    }
    //if node has one child
    else
    {
        //if the node to be deleted is left child of root
        if (!prev && cur->getLeft())
            root = cur->getLeft();
        //if the node to be deleted is right child of root
        else if (!prev)
            root = cur->getRight();
        //if the node to be deleted is left child of parent and has a left child, the parent points to node's left child
        else if(prev->getLeft() == cur && cur->getLeft())
            prev->setLeft(cur->getLeft());
        //if the node to be deleted is left child of parent and has a right child, the parent points to node's left child
        else if(prev->getLeft() == cur)
            prev->setLeft(cur->getRight());
        //if the node to be deleted is right child of parent and has a left child, the parent points to node's right child
        else if(prev->getRight() == cur && cur->getLeft())
            prev->setRight(cur->getLeft());
        //if the node to be deleted is right child of parent and has a right child, the parent points to node's right child
        else
            prev->setRight(cur->getRight());
        //node is disconnected from tree
        cur->setLeft(nullptr);
        cur->setRight(nullptr);
    }
    // deletes node
    delete cur;
    
}
//Prints the binary search tree in order
template<typename T>
void BSTree<T>::print(Node<T>* curr)
{
    //stops is current node is null
    if (curr == NULL)
    return;
    //starts from the left(Alphabetically)
    print(curr->getLeft());
    //prints the node
    std::cout << curr->getPayload().getTitle() << "\t" <<  curr->getPayload().getAvai() << "\t" <<  curr->getPayload().getRent() << std::endl;
    //ends by printing right nodes of root(Alphabetically)
    print(curr->getRight());
}
#endif /* BSTree_h */

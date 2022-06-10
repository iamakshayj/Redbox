// Akshay Jagadeesh
// axj190048
#ifndef Node_h
#define Node_h
#include <string>
template<typename T>
class Node
{
    public:
    //constructor
        Node<T>(T *data) {this->payload = data; this->left=nullptr; this->right=nullptr;}
    //destructor
        ~Node(){};
    //accessors
        T getPayload() {return *payload;}
        T* Payload() {return payload;}
        Node<T>* getLeft() const { return left; }
        Node<T>* getRight() const { return right; }
    //mutators
        void setPayload(T* y) {payload = y;}
        void setLeft(Node<T>* l) { left=l; }
        void setRight(Node<T>* r) { right=r; }
    //overloaded operators
        bool operator>(const Node<T> curr);
        bool operator<(const Node<T> curr);
        bool operator==(const Node<T> curr);
    private:
        T* payload=nullptr;
        Node<T>* left;
        Node<T>* right;
};
//overloaded operator to compare if a node title is greater than new node title, returns true/false
template<typename T>
bool Node<T>::operator>(const Node<T> curr)
{
    if (payload->getTitle().compare(curr.payload->getTitle()) > 0)
        return true;
    return false;
}
//overloaded operator to compare if a node title is less than new node title, returns true/false
template<typename T>
bool Node<T>::operator<(const Node<T> curr)
{
    if (payload->getTitle().compare(curr.payload->getTitle()) < 0)
        return true;
    return false;
}
//overloaded operator to compare if a node title is same as new node title, returns true/false
template<typename T>
bool Node<T>::operator==(const Node<T> curr)
{
    if (payload->getTitle().compare(curr.payload->getTitle()) == 0)
        return true;
    return false;
}
#endif /* Node_h */

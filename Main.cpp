// Akshay Jagadeesh
// axj190048

// Packages used
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cmath>
#include <iomanip>
// Classes used
#include "Node.h"
#include "DVD.h"
#include "BSTree.h"
using namespace std;
int main() {
//Asks user input for inventory file and transaction log and opens files
    ifstream infile;
    string file ="inventory.dat";
    cout << "File name ";
    cin >> file;
    infile.open(file);
    ifstream inlog;
    file ="transaction.log";
    cout << "Log name ";
    cin >> file;
    inlog.open(file);
//Creates the Binary Search tree with root as NULL
    BSTree<DVD>* bst= new BSTree<DVD>();
//Node used to pass in BSTree to add, search, and delete
    Node<DVD>* node=NULL;
//Varibles used to store data from file
    string title=" ";
    int avai=0;
    int rent=0;
//If inventory file exists then open and read each line
    if (infile.good())
    {
        while (getline(infile,file))
        {
//Parse the line into strings and store data
            title = file.substr(1,file.find(",")-2);
            file = file.substr(file.find(",")+1);
            avai = stoi(file.substr(0,file.find(",")));
            file = file.substr(file.find(",")+1);
            rent = stoi(file.substr(0,file.find(",")));
//Create new node and add node to Binary Search Tree
            node = new Node<DVD>(new DVD(title,avai,rent));
            bst->add(node);
        }
    }
//Opens error log to report errors
    ofstream error;
    error.open("error.log");
//If transaction log exists then open and read each line
    if (inlog.good())
    {
        while (getline(inlog,file))
        {
//string to report for error
            string line=file;
            avai=1;
//Action to be performed (add, rent, return, remove)
            string cat = file.substr(0,file.find(" "));
            bool err = false;
//If none of the actions match then error
            if (cat!="add" && cat!="rent" && cat!="return" && cat!="remove")
            {error << line; err=true;}
//Else processess line
            else
            {
                cat= cat.substr(0,3);
                file = file.substr(file.find(" ")+1);
                //Parse and store data for add and remove with title and interger value
                if (file.find(",") != string::npos)
                {
                    //If rent or return then error
                    if (cat=="ren" || cat=="ret")
                        {error << line; err=true;}
                    else
                    {
                    title = file.substr(1,file.find(",")-2);
                    file = file.substr(file.find(",")+1);
                    //If not interger value then error
                    if(file>="0" && file<="9")
                    avai= stoi(file);
                    else
                    {error << line; err=true;}
                    }
                }
                //Parse and store data for rent and return with title and default interger value of 1
                else
                {
                    //If rent or return then error
                    if (cat=="add" || cat=="rem")
                        {error << line; err=true;}
                    else
                    {
                    file=file.substr(1,file.length()-1);
                    title=file.substr(0,file.find('"'));
                    file=file.substr(file.find('"')+1);
                    //If interger value exists beyond title then error
                    if (file.length()>1)
                        {error << line; err=true;}
                    }
                }
                rent=avai;
                //If not error then process actions
                if (!err)
                {
                //if rent
                if(cat == "ren")
                {
                    //create new node for DVD and add node if found in BSTree, else error
                    node = new Node<DVD>(new DVD(title,(-1)*avai,rent));
                    if(bst->find(bst->getRoot(),node))
                        bst->add(node);
                    else
                        error << line;
                }
                //if remove
                else if(cat == "rem")
                {
                    //create new node for DVD and add node if found in BSTree, else error
                    node = new Node<DVD>(new DVD(title,(-1)*avai,(0)));
                    if(bst->find(bst->getRoot(),node))
                        bst->add(node);
                    else
                        error << line;
                }
                //if return
                else if(cat == "ret")
                {
                    //create new node for DVD and add node if found in BSTree, else error
                    node = new Node<DVD>(new DVD(title,avai,(-1)*rent));
                    if(bst->find(bst->getRoot(),node))
                        bst->add(node);
                    else
                        error << line;
                }
                //if add
                else if(cat == "add")
                {
                    //create new node for DVD and add node to BSTree, else error
                    node = new Node<DVD>(new DVD(title,avai,(0)));
                    bst->add(node);
                }
                //else error
                else
                    error << line;
                }
            }
        }
    }
    //Print BSTree, close files, and delete node and BST
    bst->print(bst->getRoot());
    infile.close();
    inlog.close();
    error.close();
    delete node;
    delete bst;
    return 0;
}

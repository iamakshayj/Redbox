// Akshay Jagadeesh
// axj190048
#ifndef DVD_h
#define DVD_h
#include <iostream>
class DVD
{
    public:
    //constructors
        DVD();
        DVD(std::string t);
        DVD(std::string t, int a, int r);
    //mutators
        void setTitle(std::string T){title=T;}
        std::string getTitle()const{return title;}
        void setAvai(int A){available=A;}
    //accessors
        int getAvai(){return available;}
        void setRent(int R){rented=R;}
        int getRent(){return rented;}
    private:
    //DVD variables
        std::string title;
        int available;
        int rented;
};
#endif /* DVD_h */

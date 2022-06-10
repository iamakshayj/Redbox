
#include "DVD.h"
// Default seat values
DVD::DVD()
{
    title=" ";
    available=0;
    rented=0;
}
// Assigned values for title variable in DVD
DVD::DVD(std::string t)
{
    title=t;
    available=0;
    rented=0;
}
// Assigned values for each variables in DVD
DVD::DVD(std::string t, int a, int r)
{
    title=t;
    available=a;
    rented=r;
}

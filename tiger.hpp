#ifndef TIGER_HPP
#define TIGER_HPP
#include <string>
#include "animal.hpp"

class Tiger : public Animal
{
    private:
        const int NUMBEROFBABIES = 1;
        const double COST = 10000;
        const double FOODCOST = (getBaseFoodCost() * 5);
        const double PAYOFF = 1000;

    public:
        Tiger()
        {
            setAge(1);
            setNumberOfBabies(NUMBEROFBABIES);
            setCost(COST);
            setBaseFoodCost(FOODCOST);
            setPayoff(PAYOFF);

        }    
};

#endif
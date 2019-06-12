#ifndef PENGUIN_HPP
#define PENGUIN_HPP
#include "animal.hpp"

class Penguin : public Animal
{
    private:
        const int NUMBEROFBABIES = 5;
        const double COST = 1000;
        const double FOODCOST = getBaseFoodCost();
        const double PAYOFF = 100;
    public:
        Penguin()
        {
            setAge(1);
            setNumberOfBabies(NUMBEROFBABIES);
            setCost(COST);
            setBaseFoodCost(FOODCOST);
            setPayoff(PAYOFF);
        }    
};

#endif
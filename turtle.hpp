#ifndef TURTLE_HPP
#define TURTLE_HPP
#include "animal.hpp"

class Turtle : public Animal
{
    private:
        const int NUMBEROFBABIES = 10;
        const double COST = 100;
        const double FOODCOST = (getBaseFoodCost() * 0.50);
        const double PAYOFF = 5;
    public:
        Turtle()
        {
            setNumberOfBabies(NUMBEROFBABIES);
            setAge(1);
            setCost(COST);
            setBaseFoodCost(FOODCOST);
            setPayoff(PAYOFF);
        }    
};

#endif
#ifndef ANIMAL_HPP
#define ANIMAL_HPP

class Animal
{
private:
    int age, numberOfBabies;
    double cost, baseFoodCost, payoff;

public:
    Animal()
    {
        setAge(1);
        setNumberOfBabies(0);
        setCost(0.0);
        setBaseFoodCost(10.0);;
        setPayoff(0.0);
    }

    int getAge()
    {
        return age;
    }
    int getCost()
    {
        return cost;
    }
    int getBaseFoodCost()
    {
        return baseFoodCost;
    }
    int getNumberOfBabies()
    {
        return numberOfBabies;
    }
    int getPayoff()
    {
        return payoff;
    }


    void setAge(int age)
    {
        this->age = age;
    }
    void setCost(int cost)
    {
        this->cost = cost;
    }
    void setBaseFoodCost(int baseFoodCost)
    {
        this->baseFoodCost = baseFoodCost;
    }
    void setNumberOfBabies(int numberOfBabies)
    {
        this->numberOfBabies = numberOfBabies;
    }
    void setPayoff(int payoff)
    {
        this->payoff = payoff;
    }
};

#endif
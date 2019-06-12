#ifndef ZOO_HPP
#define ZOO_HPP
#include "animal.hpp"
#include "tiger.hpp"
#include "penguin.hpp"
#include "turtle.hpp"

class Zoo
{
private:
    int animalCapacity, breedCount,
        tigerCount, penguinCount,
        turtleCount, animalCount;

    Animal *pAnimal;
    Tiger *pTiger;
    Penguin *pPenguin;
    Turtle *pTurtle;

public:
    Zoo();

    //Function to increase capacity of array
    void increaseCapacity(Zoo *pZoo, int animalCapacity);

    //Get functions to get values of variables in Zoo
    int getAnimalCapacity()
    {
        return animalCapacity;
    }
    int getBreedCount()
    {
        return breedCount;
    }
    int getTigerCount()
    {
        return tigerCount;
    }
    int getPenguinCount()
    {
        return penguinCount;
    }
    int getTurtleCount()
    {
        return turtleCount;
    }
    int getAnimalCount()
    {
        return animalCount;
    }
    Animal *getAnimal()
    {
        return pAnimal;
    }
    Tiger *getTiger()
    {
        return pTiger;
    }
    Penguin *getPenguin()
    {
        return pPenguin;
    }
    Turtle *getTurtle()
    {
        return pTurtle;
    }

    //Set functions for variables in Zoo
    void setAnimalCapacity(int animalCapacity)
    {
        this->animalCapacity = animalCapacity;
    }
    void setAnimalCount(int animalCount)
    {
        this->animalCount = animalCount;
    }
    void setbreedCount(int breedCount)
    {
        this->breedCount = breedCount;
    }
    void setTigerCount(int tigerCount)
    {
        this->tigerCount = tigerCount;
    }
    void setPenguinCount(int penguinCount)
    {
        this->penguinCount = penguinCount;
    }
    void setTurtleCount(int turtleCount)
    {
        this->turtleCount = turtleCount;
    }
    void setAnimal(Animal *pAnimal)
    {
        this->pAnimal = pAnimal;
    }
    void setTiger(Tiger *pTiger)
    {
        this->pTiger = pTiger;
    }
    void setPenguin(Penguin *pPenguin)
    {
        this->pPenguin = pPenguin;
    }
    void setTurtle(Turtle *pTurtle)
    {
        this->pTurtle = pTurtle;
    }

    ~Zoo();
};

#endif
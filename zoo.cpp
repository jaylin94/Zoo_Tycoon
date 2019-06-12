/*********************************************************************
** Program name: Zoo Tycoon
** Author: Jay Lin
** Date: 04/24/2019
** Description: This is a game played by a single player. In the game, 
** the player tries to spend a given sum of money by investing in different
** types of animals. Each animal is placed in a zoo, and returns a profit
** for each day. The goal of the game is to make as much money as the player
** can by purchasing the right type of animal.
** Run the program by typing "make" in the terminal in the same 
** directory. Then type "./tycoon" to run the program.
*********************************************************************/
#include <iostream>
#include "zoo.hpp"
using std::cin;
using std::cout;
using std::endl;

//Default constructor, initializes dynamic arrays for Tiger, Penguin, Turtle
//Animal classes. Initializes the items of each array to be 10.
Zoo::Zoo()
{
    //Sets the animal capacity to 10, which results in 10 items for each array.
    animalCapacity = 10;

    //Dynamically allocates memory for array of tiger objects, sets pTiger in
    //the zoo class to point to this array.
    Tiger *pTiger;
    pTiger = new Tiger[animalCapacity];
    setTiger(pTiger);

    //Dynamically allocates memory for array of tiger objects, sets pPenguin in
    //the zoo class to point to this array.
    Penguin *pPenguin;
    pPenguin = new Penguin[animalCapacity];
    setPenguin(pPenguin);

    //Dynamically allocates memory for array of tiger objects, sets pTurtle in
    //the zoo class to point to this array.
    Turtle *pTurtle;
    pTurtle = new Turtle[animalCapacity];
    setTurtle(pTurtle);

    //Dynamically allocates memory for array of tiger objects, sets pAnimal in
    //the zoo class to point to this array.
    Animal *pAnimal;
    pAnimal = new Animal[animalCapacity];
    setAnimal(pAnimal);
}

//Dynamically allocates new memory locations for new size of the array,
//carries data for animal ages over, deletes old array, sets pTiger in
//Zoo to point to new memory location.
void Zoo::increaseCapacity(Zoo *pZoo, int animalCapacity)
{
    //Sets new animal capacity size given new size
    setAnimalCapacity(animalCapacity);

    //Dynamically allocates new memory locations for new size of the array,
    //carries data for animal ages over, deletes old array, sets pTiger in
    //Zoo to point to new memory location.
    Tiger *pTiger = new Tiger[animalCapacity];
    Tiger *tempTiger = pZoo->getTiger();
    for (int i = 0; i < getTigerCount(); i++)
    {
        pTiger[i].setAge(tempTiger[i].getAge());
        // pTiger[i].setAge(getTiger()[i].getAge());
    }
    delete[] pZoo->getTiger();
    setTiger(pTiger);

    //Dynamically allocates new memory locations for new size of the array,
    //carries data for animal ages over, deletes old array, sets pPenguin in
    //Zoo to point to new memory location.
    Penguin *pPenguin = new Penguin[animalCapacity];
    Penguin *tempPenguin = pZoo->getPenguin();
    for (int i = 0; i < getPenguinCount(); i++)
    {
        pPenguin[i].setAge(tempPenguin[i].getAge());
        // pPenguin[i].setAge(getPenguin()[i].getAge());
    }
    delete[] pZoo->getPenguin();
    setPenguin(pPenguin);

    //Dynamically allocates new memory locations for new size of the array,
    //carries data for animal ages over, deletes old array, sets pTurtle in
    //Zoo to point to new memory location.
    Turtle *pTurtle = new Turtle[animalCapacity];
    Turtle *tempTurtle = pZoo->getTurtle();
    for (int i = 0; i < getTurtleCount(); i++)
    {
        pTurtle[i].setAge(tempTurtle[i].getAge());
        // pTurtle[i].setAge(getTurtle()[i].getAge());
    }
    delete[] pZoo->getTurtle();
    setTurtle(pTurtle);
}

Zoo::~Zoo()
{
    //Deletes dynamically allocated memory locations for arrays of animal objects.
    delete[] getTiger();
    delete[] getPenguin();
    delete[] getTurtle();
    delete[] getAnimal();
}
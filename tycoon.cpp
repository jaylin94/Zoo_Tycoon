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
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "game.hpp"
#include "animal.hpp"
#include "zoo.hpp"
using std::cin;
using std::cout;
using std::endl;

//Display function prototypes
void displayContinue();
void displayDay(int *pDay);
void displayMoney(double *pMoney);
void displayAnimalCount(Zoo *pZoo);

//Buy animal function prototypes
void buyAnimals1(Zoo *pZoo, double *pMoney);
void buyAnimals2(Zoo *pZoo, double *pMoney);
void buyTigers(Zoo *pZoo, double *pMoney);
void buyPenguins(Zoo *pZoo, double *pMoney);
void buyTurtles(Zoo *pZoo, double *pMoney);

//Feed animals and pay user prototypes
void feedAnimals(Zoo *pZoo, double *pMoney);
void payUser(Zoo *pZoo, double *pMoney);

//Random event selector and random event prototypes
void randomEvent(Zoo *pZoo, double *pMoney);
void sickness(Zoo *pZoo);
void boom(Zoo *pZoo, double *pMoney);
void baby(Zoo *pZoo);

//Age animals and check capacity/increase capacity
void ageAnimals(Zoo *pZoo);
void checkCapacity(Zoo *pZoo);

//Input validation functions
int validateInt();
int validateIntBuy();

int main()
{
    //Set initial variables
    int day = 0;
    int tigerCount = 0;
    int penguinCount = 0;
    int turtleCount = 0;
    double money = 50000.00;
    srand(time(0));

    //Pointers to pass into functions
    double *pMoney = &money;
    int *pDay = &day;

    //Game object and pointer to pass into functions
    Game game1;
    Game *pGame;
    pGame = &game1;

    //Zoo object and pointer to pass into functions
    Zoo zoo1;
    Zoo *pZoo;
    pZoo = &zoo1;

    //Display menu then run game
    pGame->displayMenu();
    while (pGame->startCheck())
    {
        //Display day number
        displayDay(pDay);

        //If first day, buy initial animals to start game
        if (day == 0)
        {
            displayMoney(pMoney);
            buyAnimals1(pZoo, pMoney);
        }

        //Ages animals if it is after the first day
        if (day > 0)
        {
            ageAnimals(pZoo);
        }

        //Show user feed animal information
        displayContinue();
        feedAnimals(pZoo, pMoney);

        //Show user random event information
        displayContinue();
        randomEvent(pZoo, pMoney);

        //Show user profit and money information
        displayContinue();
        payUser(pZoo, pMoney);
        displayMoney(pMoney);

        //Show user option to buy animals if desired
        displayContinue();
        displayAnimalCount(pZoo);
        buyAnimals2(pZoo, pMoney);

        //Increment day
        day++;
        //Check capacity, double array capacity if needed
        checkCapacity(pZoo);

        //Display animal count and money information
        displayAnimalCount(pZoo);
        displayMoney(pMoney);

        //If no money left, game over
        if (*pMoney == 0)
        {
            displayMoney(pMoney);
            cout << "Game over. You've gone bankrupt! Thanks for playing. " << endl;
            break;
        }
        else if (*pMoney < 0)
        {
            displayMoney(pMoney);
            cout << "Game over. You've gone bankrupt! And even racked up some debt to the Iron Bank. Thanks for playing!" << endl;
            break;
        }

        //Display menu to continue or quit, does not display if game is over
        pGame->displayMenu();
    }

    return 0;
}

//Generates a random event for the user, sickness, boom, baby, or nothing.
//Takes a zoo pointer, double pointer for money.
//Changes user money, animal count, depending on event.
void randomEvent(Zoo *pZoo, double *pMoney)
{
    int randomEvent = (rand() % 4) + 1;
    if (randomEvent == 1)
    {
        sickness(pZoo);
    }
    else if (randomEvent == 2)
    {
        boom(pZoo, pMoney);
    }
    else if (randomEvent == 3)
    {
        baby(pZoo);
    }
    else if (randomEvent == 4)
    {
        cout << "Nothing spectacular happened on this day. How boring." << endl;
    }
}

//Sickness random event for the game. Will generate a random number between 1-3,
//if there are no animals of a specific type, regenerates number.
//Takes zoo pointer, changes animal count by -1.
void sickness(Zoo *pZoo)
{
    int randomBreed = (rand() % 3) + 1;

    //Regenerates number if breed selected currently has 0 animals
    while (randomBreed == 1 && pZoo->getTigerCount() == 0)
    {
        randomBreed = (rand() % 3) + 1;
    }
    while (randomBreed == 2 && pZoo->getPenguinCount() == 0)
    {
        randomBreed = (rand() % 3) + 1;
    }
    while (randomBreed == 3 && pZoo->getTurtleCount() == 0)
    {
        randomBreed = (rand() % 3) + 1;
    }

    //Takes breed and animal count, then subtracts one from the animal count.
    //Simulates the death of an animal by resetting age.
    if (randomBreed == 1 && pZoo->getTigerCount() > 0)
    {
        pZoo->getTiger()[pZoo->getTigerCount() - 1].setAge(0);
        pZoo->setTigerCount(pZoo->getTigerCount() - 1);

        cout << "A tiger has fallen sick... and passed away." << endl;
        cout << "You have " << pZoo->getTigerCount() << " Tigers, remaining." << endl;
    }

    else if (randomBreed == 2 && pZoo->getPenguinCount() > 0)
    {
        pZoo->getPenguin()[pZoo->getPenguinCount() - 1].setAge(0);
        pZoo->setPenguinCount(pZoo->getPenguinCount() - 1);

        cout << "A Penguin has fallen sick... and passed away." << endl;
        cout << "You have " << pZoo->getPenguinCount() << " Penguins, remaining." << endl;
    }
    else if (randomBreed == 3 && pZoo->getTurtleCount() > 0)
    {
        pZoo->getTurtle()[pZoo->getTurtleCount() - 1].setAge(0);
        pZoo->setTurtleCount(pZoo->getTurtleCount() - 1);

        cout << "A Turtle has fallen sick... and passed away." << endl;
        cout << "You have " << pZoo->getTurtleCount() << " Turtles, remaining." << endl;
    }
    else
    {
        cout << "There are no animals available to be sick. " << endl;
    }
}

//Boom random event where the user receives a bonus for the number of tigers
//that he/she has in the zoo. Takes a zoo pointer and money pointer. Changes
//money for user depending on the number of tigers.
void boom(Zoo *pZoo, double *pMoney)
{
    double bonus = (rand() % 500) + 1;

    //Regenerate bonus if number is below 250, so that range is 250-500.
    while (bonus < 250)
    {
        bonus = (rand() % 500) + 1;
    }
    bonus *= pZoo->getTigerCount();

    *pMoney += bonus;

    cout << "You have " << pZoo->getTigerCount() << " Tigers which nets you a bonus of: $"
         << std::fixed << std::showpoint << std::setprecision(2) << bonus << endl;
}

//Baby random event that adds the number of new animals specific to each animal
//types  numberOfBabies. Takes a zoo pointer.
//Increases animal count that gives birth, checks to see if array should be
//doubled in size and doubles if necessary.
void baby(Zoo *pZoo)
{
    int randomBreed = (rand() % 3) + 1;

    //Variable that sets eligibility of each animal to give birth, determined by age.
    int eligibleTiger = 0;
    int eligiblePenguin = 0;
    int eligibleTurtle = 0;

    //Recalculate random breed if 0 animals in first rolled breed.
    while (randomBreed == 1 && pZoo->getTigerCount() == 0)
    {
        randomBreed = (rand() % 3) + 1;
    }
    while (randomBreed == 2 && pZoo->getPenguinCount() == 0)
    {
        randomBreed = (rand() % 3) + 1;
    }
    while (randomBreed == 3 && pZoo->getTurtleCount() == 0)
    {
        randomBreed = (rand() % 3) + 1;
    }

    //Looks through the array of animal types to determine if there is
    //an animal eligible to have babies.
    for (int i = 0; i < pZoo->getTigerCount(); i++)
    {
        if (pZoo->getTiger()[i].getAge() >= 3)
        {
            eligibleTiger = 1;
        }
    }
    for (int i = 0; i < pZoo->getPenguinCount(); i++)
    {
        if (pZoo->getPenguin()[i].getAge() >= 3)
        {
            eligiblePenguin = 1;
        }
    }
    for (int i = 0; i < pZoo->getTurtleCount(); i++)
    {
        if (pZoo->getTurtle()[i].getAge() >= 3)
        {
            eligibleTurtle = 1;
        }
    }

    //Sees if there is an eligible animal to give birth and doubles array if necessary.
    //If an animal is eligible and a new animal or animals age 0 are created, breaks out of the loop.
    if (randomBreed == 1 && pZoo->getTigerCount() > 0 && eligibleTiger == 1)
    {
        for (int i = 0; i < pZoo->getTigerCount(); i++)
        {
            if (pZoo->getTiger()[i].getAge() >= 3)
            {
                pZoo->setTigerCount(pZoo->getTigerCount() + pZoo->getTiger()->getNumberOfBabies());
                checkCapacity(pZoo);
                pZoo->getTiger()[pZoo->getTigerCount() - 1].setAge(0);

                cout << "A Tiger has given birth!" << endl;
                cout << "You now have " << pZoo->getTigerCount() << " Tigers." << endl;
                break;
            }
        }
    }
    else if (randomBreed == 2 && pZoo->getPenguinCount() > 0 && eligiblePenguin == 1)
    {
        for (int i = 0; i < pZoo->getPenguinCount(); i++)
        {
            if (pZoo->getPenguin()[i].getAge() >= 3)
            {
                pZoo->setPenguinCount(pZoo->getPenguinCount() + pZoo->getPenguin()->getNumberOfBabies());
                checkCapacity(pZoo);
                pZoo->getPenguin()[pZoo->getPenguinCount() - 1].setAge(0);

                cout << "A Penguin has given birth!" << endl;
                cout << "You now have " << pZoo->getPenguinCount() << " Penguins." << endl;
                break;
            }
        }
    }
    else if (randomBreed == 3 && pZoo->getTurtleCount() > 0 && eligibleTurtle == 1)
    {
        for (int i = 0; i < pZoo->getTurtleCount(); i++)
        {
            if (pZoo->getTurtle()[i].getAge() >= 3)
            {
                pZoo->setTurtleCount(pZoo->getTurtleCount() + pZoo->getTurtle()->getNumberOfBabies());
                checkCapacity(pZoo);
                pZoo->getTurtle()[pZoo->getTurtleCount() - 1].setAge(0);

                cout << "A turtle has given birth!" << endl;
                cout << "You now have " << pZoo->getTurtleCount() << " Turtles." << endl;
                break;
            }
        }
    }
    else
    {
        cout << "No animals could have babies. " << endl;
    }
}

//Buys tigers, penguins, turtles at the initial start of the game.
//Takes a zoo pointer and money pointer. Adds animals and subtracts
//money depending on the users choices.
void buyAnimals1(Zoo *pZoo, double *pMoney)
{
    buyTigers(pZoo, pMoney);
    buyPenguins(pZoo, pMoney);
    buyTurtles(pZoo, pMoney);
}

//End of round option to buy animals for the user. Takes a zoo pointer
//and money pointer. Adds adult animal age 3 and subtracts user money
//depending on the animal type.
void buyAnimals2(Zoo *pZoo, double *pMoney)
{
    int purchaseChoice = 0;
    int breedChoice = 0;
    cout << "Would you like to buy one adult animal? (FYI: old enough for procreation)" << endl;
    cout << "Please enter '1' for yes, '2' for no." << endl;
    purchaseChoice = validateInt();
    if (purchaseChoice == 1)
    {
        cout << "Which animals would you like to purchase? " << endl;
        cout << "Enter '1' for a Tiger. ($" << pZoo->getTiger()->getCost() << ")" << endl;
        cout << "Enter '2' for a Penguin. ($" << pZoo->getPenguin()->getCost() << ")" << endl;
        cout << "Enter '3' for a Turtle. ($" << pZoo->getTurtle()->getCost() << ")" << endl;
        cout << "Enter '4' to continue without buying. " << endl;
        purchaseChoice = validateIntBuy();

        switch (purchaseChoice)
        {
        case 1:
            pZoo->setTigerCount(pZoo->getTigerCount() + 1);
            checkCapacity(pZoo);
            pZoo->getTiger()[pZoo->getTigerCount() - 1].setAge(3);

            *pMoney -= pZoo->getTiger()->getCost();
            cout << "Remaining Cash after buying a Tiger: $" << std::fixed
                 << std::showpoint << std::setprecision(2) << *pMoney << endl;

            displayContinue();
            break;

        case 2:
            pZoo->setPenguinCount(pZoo->getPenguinCount() + 1);
            checkCapacity(pZoo);
            pZoo->getPenguin()[pZoo->getPenguinCount() - 1].setAge(3);

            *pMoney -= pZoo->getPenguin()->getCost();
            cout << "Remaining Cash after buying a Penguin: $" << std::fixed
                 << std::showpoint << std::setprecision(2) << *pMoney << endl;

            displayContinue();
            break;

        case 3:
            pZoo->setTurtleCount(pZoo->getTurtleCount() + 1);
            checkCapacity(pZoo);
            pZoo->getTurtle()[pZoo->getTurtleCount() - 1].setAge(3);

            *pMoney -= pZoo->getTurtle()->getCost();
            cout << "Remaining Cash after buying a Turtle: $" << std::fixed
                 << std::showpoint << std::setprecision(2) << *pMoney << endl;

            displayContinue();
            break;

        case 4:
            cout << "Continuing without buying an adult animal. " << endl;

            displayContinue();
            break;
        };
    }
    else if (purchaseChoice == 2)
    {
        cout << "Continuing without buying an adult animal. " << endl;
        displayContinue();
    }
}

//Buy tigers for user with information. Takes zoo pointer and money pointer.
//User can buy two of each type of animal, subtracts money accordingly.
void buyTigers(Zoo *pZoo, double *pMoney)
{
    cout << "FYI: Per Tiger profit for each day is: $" << pZoo->getTiger()->getPayoff() << endl;
    cout << "FYI: Food cost per Tiger per day: $" << pZoo->getTiger()->getBaseFoodCost() << endl;
    cout << "FYI: $" << std::fixed << std::showpoint << std::setprecision(2) << pZoo->getTiger()->getCost()
         << " per Tiger. \n"
         << "Please enter the number of Tigers"
         << " that you would like to buy: " << endl;

    pZoo->setTigerCount(validateInt());

    for (int i = 0; i < (pZoo->getTigerCount()); i++)
    {
        pZoo->getTiger()[i].setAge(1);
        cout << "Tiger " << i << "'s age: " << pZoo->getTiger()[i].getAge() << endl;
        *pMoney -= pZoo->getTiger()->getCost();
    }
    cout << "Remaining Cash: $" << std::fixed
         << std::showpoint << std::setprecision(2) << *pMoney << endl;
}

//Buy penguins for user with information. Takes zoo pointer and money pointer.
//User can buy two of each type of animal, subtracts money accordingly.
void buyPenguins(Zoo *pZoo, double *pMoney)
{
    cout << "FYI: Per Penguin profit for each day is: $" << pZoo->getPenguin()->getPayoff() << endl;
    cout << "FYI: Food cost per Penguin per day: $"
         << pZoo->getPenguin()->getBaseFoodCost() << endl;
    cout << "FYI: $" << std::fixed << std::showpoint
         << std::setprecision(2) << pZoo->getPenguin()->getCost()
         << " per Penguin. \n"
         << "Please enter the number of Penguins"
         << " that you would like to buy: " << endl;

    pZoo->setPenguinCount(validateInt());

    for (int i = 0; i < (pZoo->getPenguinCount()); i++)
    {
        pZoo->getPenguin()[i].setAge(1);
        cout << "Penguin " << i << "'s age: " << pZoo->getPenguin()[i].getAge() << endl;
        *pMoney -= pZoo->getPenguin()->getCost();
    }
    cout << "Remaining Cash: $" << std::fixed
         << std::showpoint << std::setprecision(2) << *pMoney << endl;
}

//Buy Turtles for user with information. Takes zoo pointer and money pointer.
//User can buy two of each type of animal, subtracts money accordingly.
void buyTurtles(Zoo *pZoo, double *pMoney)
{
    cout << "FYI: Per Turtle profit for each day is: $" << pZoo->getTurtle()->getPayoff() << endl;
    cout << "FYI: Food cost per Turtle per day: $" << pZoo->getTurtle()->getBaseFoodCost() << endl;
    cout << "FYI: $" << std::fixed << std::showpoint
         << std::setprecision(2) << pZoo->getTurtle()->getCost()
         << " per Turtle. \n"
         << "Please enter the number of Turtles"
         << " that you would like to buy: " << endl;

    pZoo->setTurtleCount(validateInt());

    for (int i = 0; i < (pZoo->getTurtleCount()); i++)
    {
        pZoo->getTurtle()[i].setAge(1);
        cout << "Turtle " << i << "'s age: " << pZoo->getTurtle()[i].getAge() << endl;
        *pMoney -= pZoo->getTurtle()->getCost();
    }
    cout << "Remaining Cash: $" << std::fixed
         << std::showpoint << std::setprecision(2) << *pMoney << endl;
}

//Feeds animals, subtracts cost from users balance. Takes a zoo pointer and
//money pointer. Displays relevant information for the user.
void feedAnimals(Zoo *pZoo, double *pMoney)
{
    cout << "Food cost per Tiger per day: $" << pZoo->getTiger()->getBaseFoodCost() << endl;

    for (int i = 0; i < pZoo->getTigerCount(); i++)
    {
        *pMoney -= pZoo->getTiger()->getBaseFoodCost();
    }
    cout << "Remaining Cash after feeding " << pZoo->getTigerCount() << " Tigers: $" << std::fixed
         << std::showpoint << std::setprecision(2) << *pMoney << endl;

    cout << "Food cost per Penguin per day: $" << pZoo->getPenguin()->getBaseFoodCost() << endl;

    for (int i = 0; i < pZoo->getPenguinCount(); i++)
    {
        *pMoney -= pZoo->getPenguin()->getBaseFoodCost();
    }
    cout << "Remaining Cash after feeding " << pZoo->getPenguinCount() << " Penguins: $" << std::fixed
         << std::showpoint << std::setprecision(2) << *pMoney << endl;

    cout << "Food cost per Turtle per day: $" << pZoo->getTurtle()->getBaseFoodCost() << endl;

    for (int i = 0; i < pZoo->getTurtleCount(); i++)
    {
        *pMoney -= pZoo->getTurtle()->getBaseFoodCost();
    }
    cout << "Remaining Cash after feeding " << pZoo->getTurtleCount() << " Turtles: $" << std::fixed
         << std::showpoint << std::setprecision(2) << *pMoney << endl;
}

//Pays user depending on profits based on their animal count. Takes a zoo pointer
//and money pointer. Adds money and displays profit for the day.
void payUser(Zoo *pZoo, double *pMoney)
{
    double profits = 0;
    profits = (pZoo->getTigerCount() * pZoo->getTiger()->getPayoff()) + (pZoo->getPenguinCount() * pZoo->getPenguin()->getPayoff()) +
              (pZoo->getTurtleCount() * pZoo->getTurtle()->getPayoff());

    *pMoney += (pZoo->getTigerCount() * pZoo->getTiger()->getPayoff()) + (pZoo->getPenguinCount() * pZoo->getPenguin()->getPayoff()) +
               (pZoo->getTurtleCount() * pZoo->getTurtle()->getPayoff());

    cout << "Profits for the day: $" << std::fixed << std::showpoint
         << std::setprecision(2) << profits << endl;
}

//Ages animals one day depending on the number of animals for each array.
//Takes a zoo pointer.
void ageAnimals(Zoo *pZoo)
{
    for (int i = 0; i < pZoo->getTigerCount(); i++)
    {
        pZoo->getTiger()[i].setAge(pZoo->getTiger()[i].getAge() + 1);
        cout << "Tiger " << i << "'s age: " << pZoo->getTiger()[i].getAge() << endl;
    }

    for (int i = 0; i < pZoo->getPenguinCount(); i++)
    {
        pZoo->getPenguin()[i].setAge(pZoo->getPenguin()[i].getAge() + 1);
        cout << "Penguin " << i << "'s age: " << pZoo->getPenguin()[i].getAge() << endl;
    }

    for (int i = 0; i < pZoo->getTurtleCount(); i++)
    {
        pZoo->getTurtle()[i].setAge(pZoo->getTurtle()[i].getAge() + 1);
        cout << "Turtle " << i << "'s age: " << pZoo->getTurtle()[i].getAge() << endl;
    }
}

//Checks capacity of each animal type array and doubles array if necessary.
//Takes a zoo pointer.
void checkCapacity(Zoo *pZoo)
{
    int newCapacity = pZoo->getAnimalCapacity() * 2;
    if (pZoo->getTigerCount() >= pZoo->getAnimalCapacity())
    {
        pZoo->increaseCapacity(pZoo, newCapacity);
    }
    else if (pZoo->getPenguinCount() >= pZoo->getAnimalCapacity())
    {
        pZoo->increaseCapacity(pZoo, newCapacity);
    }
    else if (pZoo->getTurtleCount() >= pZoo->getAnimalCapacity())
    {
        pZoo->increaseCapacity(pZoo, newCapacity);
    }
}

//Validates user input for 1 and 2, no other inputs allowed. Returns an integer as
//user input.
int validateInt()
{
    //Float validation adapted from: https://www.quora.com/How-do-I-check-if-a-number-is-float-on-C++
    double choice = 0.0;
    int floatTest = 0;

    while (true)
    {
        while (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Please enter a valid integer, 1 or 2." << endl;
        }
        floatTest = choice * 100000000.0;
        if (((floatTest % 100000000) > 0) || choice < 1 || choice > 2)
        {
            //Clears extraction failure flag
            cin.clear();
            //Ignores next 10000 inputs in the buffer until \n
            cin.ignore(10000, '\n');
            cout << "Please enter a valid integer, 1 or 2." << endl;
        }
        else
        {
            cin.ignore(10000, '\n');
            return choice;
        }
    }
}

//Validates integers 1, 2, 3, 4, and no other inputs are accepted. Returns an integer
//as user input.
int validateIntBuy()
{
    //Float validation adapted from: https://www.quora.com/How-do-I-check-if-a-number-is-float-on-C++
    double choice = 0.0;
    int floatTest = 0;

    while (true)
    {
        while (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Please enter a valid integer, 1, 2, 3, or 4." << endl;
        }
        floatTest = choice * 100000000.0;
        if (((floatTest % 100000000) > 0) || choice < 1 || choice > 4)
        {
            //Clears extraction failure flag
            cin.clear();
            //Ignores next 10000 inputs in the buffer until \n
            cin.ignore(10000, '\n');
            cout << "Please enter a valid integer, 1, 2, 3, or 4." << endl;
        }
        else
        {
            cin.ignore(10000, '\n');
            return choice;
        }
    }
}

//Displays the day, takes a pointer to day.
void displayDay(int *pDay)
{
    cout << "This is Day " << *pDay << "!" << endl;
}

//Displays money, takes a pointer to user money.
void displayMoney(double *pMoney)
{
    cout << std::fixed << std::showpoint << std::setprecision(2)
         << "You have $" << *pMoney << " left in your account. " << endl;
}

//Displays the animal count of the user. Takes a zoo pointer.
void displayAnimalCount(Zoo *pZoo)
{
    cout << "Tiger count: " << pZoo->getTigerCount() << endl;
    cout << "Penguin count: " << pZoo->getPenguinCount() << endl;
    cout << "Turtle count: " << pZoo->getTurtleCount() << endl;
}

//Asks user to press any key and/or ENTER/RETURN to continue.
void displayContinue()
{
    std::string anyKey;
    cout << "Press any key and/or ENTER/RETURN to continue. " << endl;
    getline(cin, anyKey);
}

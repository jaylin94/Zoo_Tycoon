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

void displayContinue();
void displayDay(int *pDay);
void displayMoney(double *pMoney);
void displayAnimalCount(Zoo *pZoo);

void buyAnimals1(Zoo *pZoo, double *pMoney);
void buyAnimals2(Zoo *pZoo, double *pMoney);

void buyTigers(Zoo *pZoo, double *pMoney);
void buyPenguins(Zoo *pZoo, double *pMoney);
void buyTurtles(Zoo *pZoo, double *pMoney);

void feedAnimals(Zoo *pZoo, double *pMoney);
void payUser(Zoo *pZoo, double *pMoney);

void randomEvent(Zoo *pZoo, double *pMoney);
void sickness(Zoo *pZoo);
void boom(Zoo *pZoo, double *pMoney);
void baby(Zoo *pZoo);

void ageAnimals(Zoo *pZoo);
void checkCapacity(Zoo *pZoo);

int validateInt();
int validateIntBuy();

int main()
{
    int day = 0;
    int tigerCount = 0;
    int penguinCount = 0;
    int turtleCount = 0;
    double money = 100000.00;
    srand(time(0));

    double *pMoney = &money;
    int *pDay = &day;

    Game game1;
    Game *pGame = new Game;
    pGame = &game1;

    Zoo zoo1;
    Zoo *pZoo = new Zoo;
    pZoo = &zoo1;

    pGame->displayMenu();
    while (pGame->startCheck())
    {
        if (*pMoney == 0)
        {
            displayMoney(pMoney);
            cout << "Game over. You've gone bankrupt! Thanks for playing. " << endl;
            exit(EXIT_SUCCESS);
        }
        else if (*pMoney < 0)
        {
            displayMoney(pMoney);
            cout << "Game over. You've gone bankrupt! And even racked up some debt to the Iron Bank. Thanks for playing!" << endl;
            exit(EXIT_SUCCESS);
        }

        displayDay(pDay);
        if (day == 0)
        {
            displayMoney(pMoney);
            buyAnimals1(pZoo, pMoney);
        }

        displayContinue();
        randomEvent(pZoo, pMoney);

        displayContinue();
        feedAnimals(pZoo, pMoney);

        displayContinue();
        payUser(pZoo, pMoney);
        displayMoney(pMoney);

        displayContinue();
        displayAnimalCount(pZoo);
        buyAnimals2(pZoo, pMoney);

        day++;
        ageAnimals(pZoo);
        checkCapacity(pZoo);
        displayAnimalCount(pZoo);
        displayMoney(pMoney);
        pGame->displayMenu();
    }

    return 0;
}

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

void sickness(Zoo *pZoo)
{
    int randomBreed = (rand() % 3) + 1;

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
void boom(Zoo *pZoo, double *pMoney)
{
    double bonus = rand() % 500;
    while (bonus < 250)
    {
        bonus = rand() % 500;
    }
    bonus *= pZoo->getTigerCount();

    *pMoney += bonus;

    cout << "You have " << pZoo->getTigerCount() << " Tigers which nets you a bonus of: $"
         << std::fixed << std::showpoint << std::setprecision(2) << bonus  << endl;
}

void baby(Zoo *pZoo)
{
    int randomBreed = (rand() % 3) + 1;
    int eligibleTiger = 0;
    int eligiblePenguin = 0;
    int eligibleTurtle = 0;

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

    if (randomBreed == 1 && pZoo->getTigerCount() > 0 && eligibleTiger == 1)
    {
        for (int i = 0; i < pZoo->getTigerCount(); i++)
        {
            if (pZoo->getTiger()[i].getAge() >= 3)
            {
                pZoo->setTigerCount(pZoo->getTigerCount() + pZoo->getTiger()->getBabies());
                checkCapacity(pZoo);
                pZoo->getTiger()[pZoo->getTigerCount() - 1].setAge(0);

                cout << "A Tiger has given birth!" << endl;
                cout << "You now have " << pZoo->getTigerCount() << " Tigers." << endl;
                break;
            }
            // else
            // {
            //     cout << "Tiger " << i << " is not old enough to have a baby." << endl;
            // }
        }
    }
    else if (randomBreed == 2 && pZoo->getPenguinCount() > 0 && eligiblePenguin == 1)
    {
        for (int i = 0; i < pZoo->getPenguinCount(); i++)
        {
            if (pZoo->getPenguin()[i].getAge() >= 3)
            {
                pZoo->setPenguinCount(pZoo->getPenguinCount() + pZoo->getPenguin()->getBabies());
                checkCapacity(pZoo);
                pZoo->getPenguin()[pZoo->getPenguinCount() - 1].setAge(0);

                cout << "A Penguin has given birth!" << endl;
                cout << "You now have " << pZoo->getPenguinCount() << " Penguins." << endl;
                break;
            }
            // else
            // {
            //     cout << "Penguin " << i << " is not old enough to have a baby." << endl;
            // }
        }
    }
    else if (randomBreed == 3 && pZoo->getTurtleCount() > 0 && eligibleTurtle == 1)
    {
        for (int i = 0; i < pZoo->getTurtleCount(); i++)
        {
            if (pZoo->getTurtle()[i].getAge() >= 3)
            {
                pZoo->setTurtleCount(pZoo->getTurtleCount() + pZoo->getTurtle()->getBabies());
                checkCapacity(pZoo);
                pZoo->getTurtle()[pZoo->getTurtleCount() - 1].setAge(0);

                cout << "A turtle has given birth!" << endl;
                cout << "You now have " << pZoo->getTurtleCount() << " Turtles." << endl;
                break;
            }
            // else
            // {
            //     cout << "Turtle " << i << " is not old enough to have a baby." << endl;
            // }
        }
    }
    else
    {
        cout << "No animals could have babies. " << endl;
    }
}

void buyAnimals1(Zoo *pZoo, double *pMoney)
{
    buyTigers(pZoo, pMoney);
    buyPenguins(pZoo, pMoney);
    buyTurtles(pZoo, pMoney);
}

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

void buyTigers(Zoo *pZoo, double *pMoney)
{
    cout << "FYI: Per Tiger profit for each day is: $" << pZoo->getTiger()->getPayoff() << endl;
    cout << "FYI: Food cost per Tiger per day: $" << pZoo->getTiger()->getFoodCost() << endl;
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

void buyPenguins(Zoo *pZoo, double *pMoney)
{
    cout << "FYI: Per Penguin profit for each day is: $" << pZoo->getPenguin()->getPayoff() << endl;
    cout << "FYI: Food cost per Penguin per day: $"
         << pZoo->getPenguin()->getFoodCost() << endl;
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

void buyTurtles(Zoo *pZoo, double *pMoney)
{
    cout << "FYI: Per Turtle profit for each day is: $" << pZoo->getTurtle()->getPayoff() << endl;
    cout << "FYI: Food cost per Turtle per day: $" << pZoo->getTurtle()->getFoodCost() << endl;
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

void feedAnimals(Zoo *pZoo, double *pMoney)
{
    cout << "Food cost per Tiger per day: $" << pZoo->getTiger()->getFoodCost() << endl;

    for (int i = 0; i < pZoo->getTigerCount(); i++)
    {
        *pMoney -= pZoo->getTiger()->getFoodCost();
    }
    cout << "Remaining Cash after feeding " << pZoo->getTigerCount() << " Tigers: $" << std::fixed
         << std::showpoint << std::setprecision(2) << *pMoney << endl;

    cout << "Food cost per Penguin per day: $" << pZoo->getPenguin()->getFoodCost() << endl;

    for (int i = 0; i < pZoo->getPenguinCount(); i++)
    {
        *pMoney -= pZoo->getPenguin()->getFoodCost();
    }
    cout << "Remaining Cash after feeding " << pZoo->getPenguinCount() << " Penguins: $" << std::fixed
         << std::showpoint << std::setprecision(2) << *pMoney << endl;

    cout << "Food cost per Turtle per day: $" << pZoo->getTurtle()->getFoodCost() << endl;

    for (int i = 0; i < pZoo->getTurtleCount(); i++)
    {
        *pMoney -= pZoo->getTurtle()->getFoodCost();
    }
    cout << "Remaining Cash after feeding " << pZoo->getTurtleCount() << " Turtles: $" << std::fixed
         << std::showpoint << std::setprecision(2) << *pMoney << endl;
}

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

void ageAnimals(Zoo *pZoo)
{
    for (int i = 0; i < pZoo->getTigerCount(); i++)
    {
        pZoo->getTiger()[i].setAge(pZoo->getTiger()[i].getAge() + 1);
    }

    for (int i = 0; i < pZoo->getPenguinCount(); i++)
    {
        pZoo->getPenguin()[i].setAge(pZoo->getPenguin()[i].getAge() + 1);
    }

    for (int i = 0; i < pZoo->getTurtleCount(); i++)
    {
        pZoo->getTurtle()[i].setAge(pZoo->getTurtle()[i].getAge() + 1);
    }
}

void checkCapacity(Zoo *pZoo)
{
    if (pZoo->getTigerCount() >= pZoo->getAnimalCapacity())
    {
        pZoo->increaseCapacity(pZoo->getAnimalCapacity() * 2);
    }
    else if (pZoo->getPenguinCount() >= pZoo->getAnimalCapacity())
    {
        pZoo->increaseCapacity(pZoo->getAnimalCapacity() * 2);
    }
    else if (pZoo->getTurtleCount() >= pZoo->getAnimalCapacity())
    {
        pZoo->increaseCapacity(pZoo->getAnimalCapacity() * 2);
    }
}

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

void displayDay(int *pDay)
{
    cout << "This is Day " << *pDay << "!" << endl;
}

void displayMoney(double *pMoney)
{
    cout << std::fixed << std::showpoint << std::setprecision(2)
         << "You have $" << *pMoney << " left in your account. " << endl;
}

void displayAnimalCount(Zoo *pZoo)
{
    cout << "Tiger count: " << pZoo->getTigerCount() << endl;
    cout << "Penguin count: " << pZoo->getPenguinCount() << endl;
    cout << "Turtle count: " << pZoo->getTurtleCount() << endl;
}

//Asks user to press any key and ENTER/RETURN to continue.
void displayContinue()
{
    std::string anyKey;
    cout << "Press any key and ENTER/RETURN to continue. " << endl;
    getline(cin, anyKey);
}

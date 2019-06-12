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
#include <string>
#include "game.hpp"
using std::cout;
using std::endl;
using std::cin;
using std::string;

//Displays menu for the game, prompts user to start or quit. Provides a
//quick description of the game. Displays menu to rerun as well.
void Game::displayMenu()
{
    //Times run checks if this is the first time running.
    //The welcome message will only be displayed if timesRun is 0.
    if (timesRun == 0)
    {
        //gameName is set by getGameName() in the constructor.
        cout << "This is " << getGameName() << "!" << endl;
        
        cout << "You are the proud owner of a new zoo in "
            << "New York City!" << endl;
        
        cout << "Try to earn as much money as you can by making "
            << "smart investments in your animals." << endl;
        
        cout << "The game is over when you quit, or when you "
            << "run out of money. Spend wisely." << endl;
        
        cout << "Enter 's' to start, or 'q' to quit. " << endl;
    }
    //Displays rerun prompt if timesRun is > 0.
    else if (timesRun > 0)
    {
        cout << "Continue with " << getGameName() << "? "
             << "Enter 's' to start, 'q' to quit." << endl;
    }
    setTimesRun(getTimesRun() + 1);
}

//Takes input from the user for an integer and validates the input.
//Values must be between 1 and 32767. Returns an integer for set
//functions in the class.
int Game::validateInt()
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
            cout << "Please enter a valid integer > 0"
                 << ", < 32767." << endl;
        }
        floatTest = choice * 100000000.0;
        if (((floatTest % 100000000) > 0) || choice < 1 || choice > 32767)
        {
            //Clears extraction failure flag
            cin.clear();
            //Ignores next 10000 inputs in the buffer until \n
            cin.ignore(10000, '\n');
            cout << "Please enter a valid integer > 0"
                 << ", < 32767." << endl;
        }
        else
        {
            cin.ignore(10000, '\n');
            return choice;
        }
        
    }
}

//Validates menu input choice to start the program or quit.
//Ensures that input is a character of 's' to start or
//'q' to quit.
char Game::validateStartChoice()
{
    string choice;
    while (true)
    {
        cin >> (choice);
        char newChoice[1];
        newChoice[0] = choice[0];
        cin.ignore(10000, '\n');
        if (choice.length() > 1)
        {
            cout << "Please enter 's' to start or 'q' to quit." << endl;
        }
        else if (newChoice[0] == 's' || newChoice[0] == 'q')
        {
            setStartChoice(newChoice[0]);
            return newChoice[0];
        }
        else
        {
            cout << "Please enter 's' to start or 'q' to quit." << endl;
        }
    }
}

//Prompts user for menu input to start or quit, using
//getMenuChoice(). Quits if user input is 'q'.
bool Game::startCheck()
{
    if (validateStartChoice() == 'q')
    {
        return false;
    }
    else
    {
        return true;
    }
}
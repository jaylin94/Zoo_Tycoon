#ifndef GAME_HPP
#define GAME_HPP
#include <string>

class Game
{
    private:
        int timesRun;
        char startChoice;
        std::string gameName;

    public:
        Game()
        {
            timesRun = 0;
            startChoice = 's';
            gameName = "Zoo Tycoon";
        }

        //Menu functions to display and check to start or quit
        void displayMenu();
        bool startCheck();

        //Validates user start choice and integer input
        char validateStartChoice();
        int validateInt();

        //Get functions for variables
        int getTimesRun()
        {return timesRun;}
        char getStartChoice()
        {return startChoice;}
        std::string getGameName()
        {return gameName;}

        //Set functions for variables
        void setTimesRun(int timesRun)
        {this->timesRun = timesRun;}
        void setStartChoice(char startChoice)
        {this->startChoice = startChoice;}
        void setGameName(std::string gameName)
        {this->gameName = gameName;}
};

#endif
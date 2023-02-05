/*
* This file is header file to Data class. Data is class wich
* contais all player high scores informations. It can return the game high
* scores in string.Classes methods and attributes are introduced here and you
* can read more details above method or attribute in guestion.
*
* ===========================
* Program author
* Name: Matti Linna
* Student number: 151072437
* UserID: ckmali
* E-Mail: matti.linna@tuni.fi
* ===========================
*/
#ifndef DATA_HH
#define DATA_HH
#include <iostream>
#include <vector>

class Data
{
public:
    Data(std::string filename);

    //Checks that does program find data.txt file, which consist all player data
    //Returns true if file is found and false if it's not found.
    bool isDataFound();

    //Adds players result (name and points) to the high scores. Returns
    //high scores in string. Also checks that high scores are found (data.txt
    //file is found) and if it isn't found returns error message.
    std::string getResults(std::string name,float points);

private:
    //Reads the highscore data from file and stores them to container
    //playerResults_ vector defined below.
    void readFile();

    //Adds one player results to the highscores list
    void addResult(std::string name, float points);

    //Formats and writes data-file again.
    void writeFile();

    //Checks is player result in the container. Uses player name to check that.
    bool isPlayerList(std::string name);

    //container to highscores
    std::vector<std::pair<std::string, float>> playerResults_;

    //File name where the all highscore information is stored
    std::string fileName_="";
};

#endif // DATA_HH

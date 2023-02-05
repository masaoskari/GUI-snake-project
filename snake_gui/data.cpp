/* ===========================
* Program author
* Name: Matti Linna
* Student number: 151072437
* UserID: ckmali
* E-Mail: matti.linna@tuni.fi
* ===========================
*
* This is a implementation file where is all Data class method
* implementations.
* */
#include "data.hh"
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>

Data::Data(std::string filename):
    fileName_(filename)
{

}

bool Data::isDataFound()
{
     //Checks is file found
     std::ifstream input_file(fileName_);
     //Returns true if the file is found and false if it's not.
     return !not input_file;

}

std::string Data::getResults(std::string name,float points)

{
    //Checks that highscores file is found
    if (isDataFound())
    {
        //Clearing container where the all player data is. That is importat if
        //the game is reseted so the player scores will not be two times in the
        //score board.
        playerResults_.clear();

        //Reading player data to vector playerResults_
        readFile();

        //Adds players result to the container playerResults
        addResult(name, points);

        //Saving container information back to data.txt file
        writeFile();

        //The next task is to get top 5 player scores in string to return.

        //Boolean to check is user in top five in results
        bool isUserBetterThan5th=false;

        //Initializing result text to return
        std::string resultText="High scores:\n";

        //Adding top five player results to result text
        for (unsigned int i=0; i<5; i++)
        {
            //Examining is player in top five in results
            if (playerResults_.at(i).first==name)
            {
                isUserBetterThan5th=true;
            }
            //Gets player name and score from vector.
            std::string name=playerResults_.at(i).first;
            int score=round(playerResults_.at(i).second);
            std::string scoreStr= std::to_string(score);

            //Adds player position, name and score to string.
            resultText+=(std::to_string(i+1)+". "+name+" "+scoreStr+"\n");
        }
        //If user is not in top 5, showing his/her position and score at the
        //end off scoreboard.
        if (!isUserBetterThan5th)
        {
            //Initialising string which tells player position
            std::string whatPosition="";
            unsigned int position=1;

            //Examining player position and saving it to string. This loop
            //finds player position even if the user has not name.
            for (unsigned int i=0; i<playerResults_.size(); i++)
            {
                if (playerResults_.at(i).second>points)
                {
                    position+=1;
                }
            }
            whatPosition=std::to_string(position);

            //Rounding score (in some reason this cannot be straigth when
            //adding score to string)
            int score=round(points);
            std::string scoreStr=std::to_string(score);

            //Showing player score when player is not in top 5
            if (position>5)
            {
                //Adding user position and score at the end off scoreboard.
                resultText+="\n";
                resultText+="Your score:\n";
                resultText+=(whatPosition+". "+name+" "+scoreStr);
            }
        }
        return resultText;
    }
    //Returns error message when data.txt. file is not found
    else
    {
        return "No data found.\nCheck that data.txt\nfile is found.";
    }
}

void Data::readFile()
{
   //Starting to read file
   std::ifstream inputFile(fileName_);

   //Some variables to handle file data
   std::string row="";
   std::string rowsPart="";
   float points=0;
   std::string username="";

   //Pair to store one player score
   std::pair<std::string, float> onePlayerPoints;

   //Reading file row by row
   while (getline(inputFile, row))
   {
      //Stringstream to split one row
      std::stringstream str(row);

      //Variable to take care is rows part username or score (points). If number
      //is 0 the part is username and if 1 the part is score.
      int element=0;
      //Splitting line with separator ";"
      while(getline(str, rowsPart, ';'))
      {
           //Rows first part add to username string
           if (element==0)
           {
               username=rowsPart;
               element=1;
           }
           //Rows second part add to points variable
           else
           {
               points=std::stoi(rowsPart);
               element=0;
           }
      }
      //Saving player informations to pair
      onePlayerPoints={username, points};

      //Adding pair to the container
      playerResults_.push_back(onePlayerPoints);
    }
//Closing file
inputFile.close();
}

void Data::addResult(std::string name, float points)
{
    //If user has not given name, the player score is not added to scoreboard.
    if (name!="")
    {
        //Boolean to check is add needed (the add is needed when the player is
        //already in the list and him/her score is bigger than the last time.
        bool addNeeded=true;
        if (isPlayerList(name))
        {
            addNeeded=false;
            //Checking is player score bigger than last game and if it is the
            //players last score is erased.
            for (unsigned int i=0; i<playerResults_.size(); i++)
            {
                if (playerResults_.at(i).first==name)
                {
                   if (playerResults_.at(i).second<round(points))
                   {
                       playerResults_.erase(playerResults_.begin()+i);
                       //Needing to add player new highscore to the container so
                       //the addNeeded is defined to true.
                       addNeeded=true;
                       break;
                   }
                }
            }
        }
        //If player is not found in the list or the players score is bigger than
        //last time the add to the container will be done.
        if (addNeeded)
        {
            //Putting player score at the right place of scoreboard by looping
            //that vector and searching when the player score is bigger than
            //players which is already on the list. If player's score is lowest
            //the add is done at the end of the list (vector).
            for (unsigned int i=0; i<playerResults_.size(); i++)
            {
                if (playerResults_.at(i).second<=round(points))
                {
                   playerResults_.insert(playerResults_.begin() + i,
                                         {name, round(points)});
                   break;
                }
                else if (i==playerResults_.size()-1 and
                         playerResults_.at(i).second>=round(points))
                {
                    playerResults_.push_back({name, round(points)});
                }
             }
        }
    }
}

void Data::writeFile()
{
    //Writing vectors information to data.txt file.
    std::ofstream outputFile(fileName_);

    for (std::pair<std::string, float> result : playerResults_)
    {
       //On the row the words are separated with ";"
       outputFile<<result.first<<";"<<round(result.second)<<";\n";
    }
    outputFile.close();
}

bool Data::isPlayerList(std::string name)
{
    //Looping through that container and searching is player which name has
    //given on the list. Return true if it is and false if it is not.
    bool isPlayerFound=false;
    for (std::pair<std::string, float> result : playerResults_)
    {
        if (result.first==name)
        {
            isPlayerFound=true;
        }
    }
    return isPlayerFound;
}




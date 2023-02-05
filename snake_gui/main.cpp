/*
* This program implements a snake game. At the beginning user can give username
* in games homescreen. If player gives username she/he score will be saved to
* high scores table. At the home screen user can also change game area width
* and heigth with spinboxes. At the screen player can also give a seed value,
* wich generates random position to snake food. Player can start game by
* pressing "Play". At the beginning the snake is in place and when user hits
* moving keys the snake starts moving. User can move snake with
* “wasd”-keyboard keys (“w”=up, “s”=down, “a”=left, “d”=rigth). Snakes aim is
* to eat food (bananas) from the screen. When snake eats food, the food goes to
* random location on the screen, snake body grows, score is updated and the
* snakes movement speed increases.
*
* Player will win the game when the snake’s size is as big as the play area size
* (snake fills the whole screen). When player wins the screen around the play
* are will turn green. Also the “YOU WON + score” label is shown. High scores
* table is also shown left side of the screen. On the other hand player will
* lose the game when she/he collides to the wall or when the head collides to
* other snake part. When player loses the game the screen around play area turns
* red and the “GAME OVER + score” label is shown. Also in this case the high
* scores table is also shown. High scores table takes informations from
* data.txt file, where the high scores are stored. Player scores are stored
* to table when she/he is given username. High scores table label shows only
* top 5 players on the list. If the player’s score is not in top five the
* players position and score are shown at the bottom of the table. If the
* highscores file data.txt is not found the error message to user is given.
*
* Player can pause the game by using pausebutton wich pauses the game and also
* enables start button again. She/he can continue the game by pressing start
* button. Player can reset the game with reset button whenever she/he wants.
* When the reset button is pressed the games homescreen appears and user can
* modify the game parameters or the username and play the game again. User can
* close the game by clicking cross on the rigth-upper corner of the window.
*
* NOTE! When trying to run this program make sure that your build directory
* contains files data.txt, bananas.png, headVol2.png and tailVol2.png.
*
* The more details how game is implemented you will find from GameBoard, Point
* and Mainwindow classes. There is also instructions.txt file where you can
* find more details why different designs determined.
* ===========================
* Program author
* Name: Matti Linna
* Student number: 151072437
* UserID: ckmali
* E-Mail: matti.linna@tuni.fi
* ===========================
*/
#include "mainwindow.hh"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

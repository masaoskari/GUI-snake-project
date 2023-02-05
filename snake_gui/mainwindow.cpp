/* ===========================
* Program author
* Name: Matti Linna
* Student number: 151072437
* UserID: ckmali
* E-Mail: matti.linna@tuni.fi
* ===========================
*
* This is a implementation file where is all Mainwindow class method
* implementations.
* */

#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <deque>
#include <string>
#include <iostream>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QLabel>
#include <QGridLayout>
#include <QDebug>
#include <QPushButton>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui_(new Ui::MainWindow)
{
    //Setting UI
    ui_->setupUi(this);

    //Setting mainwindow background-color to black.
    this->setStyleSheet("background-color: black;");

    //New scene to game
    scene_ = new QGraphicsScene(this);

    //Graphicsview to gameboard
    view_ = new QGraphicsView(this);

    //Hiding gameboard at the beginning
    view_->hide();

    //Game timer for checking game events (moving snake etc...)
    timer_.setSingleShot(false);
    connect(&timer_, &QTimer::timeout, this, &MainWindow::checkEvent);

    //Timer for showing user the used time
    timeTimer_=new QTimer(this);
    timeTimer_->setInterval(1000);
    connect(this->timeTimer_, &QTimer::timeout, this, &MainWindow::updateTimer);
    ui_->labelTime->hide();

    //Reset button
    resetButton_ = new QPushButton("RESET", this);
    resetButton_->setGeometry(WINDOW_WIDTH/2-GAMEBOARD_MAX_SIZE/2,
                             WINDOW_WIDTH/2-GAMEBOARD_MAX_SIZE/2-BUTTON_HEIGTH,
                             BUTTON_WIDTH, BUTTON_HEIGTH);
    resetButton_->setStyleSheet("background-color: rgb(238, 238, 236);");
    //Hiding button at the beginning
    resetButton_->hide();
    connect(resetButton_, &QPushButton::clicked, this,
            &MainWindow::onResetButtonClicked);

    //Start button
    startButton_ = new QPushButton("PLAY",this);
    startButton_->setGeometry(WINDOW_WIDTH/2-BUTTON_WIDTH/2, GAMEBOARD_MAX_SIZE,
                             BUTTON_WIDTH, BUTTON_HEIGTH);
    startButton_->setStyleSheet("background-color: rgb(238, 238, 236);");
    connect(startButton_, &QPushButton::clicked, this,
            &MainWindow::onStartButtonClicked);

    //Pause button
    pauseButton_ = new QPushButton("PAUSE",this);
    pauseButton_->setGeometry(WINDOW_WIDTH/2-BUTTON_WIDTH/2,
                             WINDOW_WIDTH/2-GAMEBOARD_MAX_SIZE/2-BUTTON_HEIGTH,
                             BUTTON_WIDTH, BUTTON_HEIGTH);
    pauseButton_->setStyleSheet("background-color: rgb(238, 238, 236);");
    connect(pauseButton_, &QPushButton::clicked, this,
            &MainWindow::onPauseButtonClicked);
    pauseButton_->hide();

    //Label for snake food
    foodLabel_ = new QLabel("", this);
    //Adding foodlabel backroud to transparent.
    foodLabel_->setStyleSheet("background-color: rgba(255, 255, 255, 0%);");

    //Label to show when game ends
    endLabel_ = new QLabel(this);

    //Label for score
    scoreLabel_=new QLabel("Score: ", this);
    scoreLabel_->hide();

    //Resulttablelabel (for showing high scores) is made with Qt designer.
    //This hides it at the beginning of game.
    ui_->resultTableLabel->hide();
}

MainWindow::~MainWindow()
{
    //Releasing memory of different pointers wich are implemented with new-
    //command
    delete ui_;
    ui_=nullptr;

    //Pointer to GameBoard object memory release
    delete board_;
    board_=nullptr;

    //Buttons which are not implemented in QT designer
    delete pauseButton_;
    pauseButton_=nullptr;
    delete startButton_;
    pauseButton_=nullptr;
    delete resetButton_;
    resetButton_=nullptr;

    //Labels memory releases
    delete foodLabel_;
    foodLabel_=nullptr;
    delete endLabel_;
    endLabel_=nullptr;
    delete scoreLabel_;
    scoreLabel_=nullptr;

    //Stopwatch memory reselase
    delete timeTimer_;
    timeTimer_=nullptr;

    //Snake parts memory releases
    delete snakeHead_;
    snakeHead_=nullptr;
    if(snakeBodySize_>=3)
    {
        delete snakeTail_;
        snakeTail_=nullptr;
    }
    for (QGraphicsRectItem* part : bodyParts)
    {
        delete part;
        part=nullptr;
    }

    //Scene and view_ memory releases
    delete scene_;
    scene_=nullptr;
    delete view_;
    view_=nullptr;
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    //If player press d-key, setting turning parameters to to turn snake right
    if (event->key()==Qt::Key_D)
    {
        if(!left_)
        {
            rigth_=true;
            left_=false;
            up_=false;
            down_=false;
            return;
        }
    }
    //If player press a-key, setting turning parameters to to turn snake left
    if (event->key()==Qt::Key_A)
    {
        if (!rigth_)
        {

        left_=true;
        rigth_=false;
        up_=false;
        down_=false;
        return;
        }
    }
    //If player press w-key, setting turning parameters to to turn snake up
    if (event->key()==Qt::Key_W)
    {
        if (!down_)
        {
            up_=true;
            left_=false;
            rigth_=false;
            down_=false;
            return;
        }
    }
    //If player press s-key, setting turning parameters to to turn snake down
    if (event->key()==Qt::Key_S)
    {
        if (!up_)
        {
            down_=true;
            left_=false;
            rigth_=false;
            up_=false;
            return;
        }
    }
}

void MainWindow::updateTimer()
{
    //Grows totalsecond by 1. Total seconds are needed in calculating score.
    totalSeconds_+=1;

    //Grows seconds by 1 when the function is called.
    seconds_+=1;

    //Minutes and seconds QStrings to show in label
    QString minutesStr="";
    QString secondsStr="";

    //Calculating total minutes and seconds
    if (seconds_==60)
    {
        seconds_=0;
        minutes_+=1;
    }
    //Setting value 0 in front of minutes if minutes are less than 10.
    if (minutes_<10)
    {
        minutesStr="0"+QString::number(minutes_);
    }

    else
    {
        minutesStr=QString::number(minutes_);
    }
    //Setting value 0 in front of the seconds if seconds are less than 10.
    if (seconds_<10)
    {
        secondsStr="0"+QString::number(seconds_);
    }
    else
    {
        secondsStr=QString::number(seconds_);
    }
    //Final string to set on label
    QString timeString =minutesStr+" : "+secondsStr;

    //Setting time to label
    ui_->labelTime->setText(timeString);
}
void MainWindow::gameInit()
{
    //Making new pointer to Gameboard object with player given specs.
    board_=new GameBoard(gameboardWidth_/STEP, gameboardHeigth_/STEP, seed_);

    //Showing gameboard Graphicsview, setting it background color to white and
    //adding scene to it.
    view_->show();
    view_->setStyleSheet("background-color: rgb(255, 255, 255); ");
    view_->setScene(scene_);

    //Setting gameboard width and heigth. Gameboard heigth and width is added 2
    //px because graphicsview bordes takes that pixels.
    view_->setGeometry((WINDOW_WIDTH-gameboardWidth_)/2,
                       (WINDOW_WIDTH-gameboardHeigth_)/2,
                       (gameboardWidth_+2),
                       (gameboardHeigth_+2));

    //setting scene width and height so that it is on same are as graphicsView
    scene_->setSceneRect(0, 0, gameboardWidth_-1, gameboardHeigth_-1);

    //showing snakes head on the gameboard
    printSnake();

    //Drawing food to the gameboard
    drawFood();

    //Setting stopwatch to 0 and showing it
    ui_->labelTime->setText("00 : 00");
    ui_->labelTime->show();

    //Initializing scorelabel
    scoreLabel_->setText("Score: \n0");

    //Showing scorelabel
    scoreLabel_->show();

    //Setting scorelabel geometry
    scoreLabel_->setGeometry((WINDOW_WIDTH-gameboardWidth_)/2-BUTTON_WIDTH,
                            (WINDOW_WIDTH-gameboardHeigth_)/2,
                            BUTTON_WIDTH, 2*BUTTON_HEIGTH);
    //Setting style to scorelabel
    scoreLabel_->setStyleSheet("color: red;"
                               "font: bold 20px;"
                             );
    //Setting scorelabel text alignment
    scoreLabel_->setAlignment(Qt::AlignCenter);

}
void MainWindow::checkEvent()
{
    //Moving snake
    snakeMove();

    //Checks is player lost or won the game
    gameLostOrWon();
}

void MainWindow::snakeMove()
{
    //If key d is pressed. Moving snake to right by using GameBoard object
    //board_
    if (rigth_)
    {
        board_->moveSnake("d");
    }
    //If key a is pressed. Moving snake to left by using GameBoard object
    //board_
    if (left_)
    {
        board_->moveSnake("a");
    }
    //If key w is pressed. Moving snake to up by using GameBoard object
    //board_
    if (up_)
    {
        board_->moveSnake("w");
    }
    //If key s is pressed. Moving snake to down by using GameBoard object
    //board_
    if (down_)
    {
        board_->moveSnake("s");
    }

    //Checks is snake eaten food when it has moved on board_.
    //This check should be here before moving snake on the screen, because
    //snake is now rigth before food on the screen.
    if (snakeBodySize_<board_->returnSnake().size() and
            board_->returnSnake().size()!=1)
    {
        //Moving food
        drawFood();

        //Groving snake body size (this variable is for example used examining
        //when snake has eaten food)
        snakeBodySize_+=1;

        //Groving snake on the screen
        growSnake();

        //Updating score
        calculateScore();

        //Setting snake move faster
        setSnakeMoveFaster();
    }
    //Taking snake coordinates from board_ with returnSnake() method.
    //Return snake method gives snake part coordinates in deque. That deque
    //consist Point objects where x- and y-coordinates are stored.
    for (uint i=0; i<board_->returnSnake().size(); i++)
    {
        //Moving snake head. Snake's head coordinates are in deque's last
        //element
        if (i==board_->returnSnake().size()-1)
        {
            //Sets snake head coordinates, which are found from Point object
            //whit methods getX() and getY(). When sanke moves one step
            //on board it moves 20 pixels on the screen so coordinates are
            //multiplied by STEP=20.
            snakeHead_->setPos(board_->returnSnake().at(i).getX()*STEP,
                               board_->returnSnake().at(i).getY()*STEP);
        }
        //Moving snakes tail when snake have tail (bodysize is bigger than 3).
        //Snake's tail coordinates are in deque's first element.
        else if (i==0 and snakeBodySize_>=3)
        {

            snakeTail_->setPos(board_->returnSnake().at(i).getX()*STEP,
                               board_->returnSnake().at(i).getY()*STEP);
        }
        //Moving snake bodyparts
        else
        {

            bodyParts.at(i)->setPos(board_->returnSnake().at(i).getX()*STEP,
                                    board_->returnSnake().at(i).getY()*STEP);
        }
    }
}
void MainWindow::drawFood()
{
    //If food is hidden, getting it back to screen
    foodLabel_->show();

    //Image to food
    QPixmap image(QString::fromStdString("bananas.png"));

    //Scaling image
    image=image.scaled(FOOD_SIZE, FOOD_SIZE);

    //Getting food x- and y-coordinates by using GameBoard objects method
    //returnFood() and Point object methods getX() and getY().
    int foodX=board_->returnFood().getX();
    int foodY=board_->returnFood().getY();

    //Setting foodlabel coordinates and size
    foodLabel_->setGeometry((WINDOW_WIDTH-gameboardWidth_)/2+foodX*STEP,
                           (WINDOW_WIDTH-gameboardHeigth_)/2+foodY*STEP,
                           FOOD_SIZE, FOOD_SIZE);

    //Setting food image to label
    foodLabel_->setPixmap(image);
}


void MainWindow::printSnake()
{
    //Initializing picture for snake's head and adding it to scene
    QPixmap headPic("headVol2.png");
    QPixmap headPicScaled=headPic.scaled(STEP,STEP);
    snakeHead_ = new QGraphicsPixmapItem(headPicScaled);
    scene_->addItem(snakeHead_);

    //Tooks snake's parts coordinates
    std::deque<Point> snakeCoordinates=board_->returnSnake();

    //Sets snake head coordinates
    snakeHead_->setPos(snakeCoordinates.at(0).getX()*STEP,
                       snakeCoordinates.at(0).getY()*STEP);

    //Empty item to body parts because snake head is not added to here and
    //if I do this I can loop througth bodyParts more easily with right indexes.
    QGraphicsRectItem* bodyPart=new QGraphicsRectItem();
    scene_->addItem(bodyPart);
    bodyParts.push_back(bodyPart);
}


void MainWindow::growSnake()
{
    //Color to snake bodypart's borders
    QPen whitePen(Qt::white);

    //Snake tail add to scene when snakebody size grows to 3.
    if (snakeBodySize_==3)
    {
        //Initializing picture for snake's tail and adding it to scene
        QPixmap tailPic("tailVol2.png");
        QPixmap headPicScaled=tailPic.scaled(STEP,STEP);
        snakeTail_ = new QGraphicsPixmapItem(headPicScaled);
        scene_->addItem(snakeTail_);

        //Setting tail coordinates
        snakeTail_->setPos(board_->returnSnake().front().getX()*STEP+STEP/2,
                           board_->returnSnake().front().getY()*STEP+STEP/2);

        //Adding empty item to the bodyParts so the container indexes goes right
        //when parts are moved on the screen with method snakeMove().
        QGraphicsRectItem* bodyPart=new QGraphicsRectItem();
        scene_->addItem(bodyPart);
        bodyParts.push_front(bodyPart);
    }
    //When snakesize is 2, rect add should be done little bit different
    //because snake hasn't tai.
    else if (snakeBodySize_==2)
    {
         //Setting green rectangle with white borders to snake body
         QGraphicsRectItem* bodyPart=new QGraphicsRectItem();
         bodyPart->setRect(0, 0, STEP, STEP);

         //Body part coordinates are found from GameBoard object board_. These
         //coordinates are scaled to the screen with STEP const value.
         bodyPart->setPos(board_->returnSnake().front().getX()*STEP,
                           board_->returnSnake().front().getY()*STEP);
         bodyPart->setBrush(Qt::green);
         bodyPart->setPen(whitePen);

         //Adding rectangle to scene
         scene_->addItem(bodyPart);

         //Storing rectangle to bodyParts deque
         bodyParts.push_front(bodyPart);
    }
    //This kind off add is done when snake size is more than 3.
    else
    {
        //Setting green rectangle with white borders to snake body
        QGraphicsRectItem* bodyPart=new QGraphicsRectItem();
        bodyPart->setRect(0, 0, STEP, STEP);
        bodyPart->setPos(board_->returnSnake().front().getX()*STEP,
                         board_->returnSnake().front().getY()*STEP);

        //Setting bodypart color
        bodyPart->setBrush(QColor(0, 255, rgbBlue));

        //Changing bodypart colors so that different bodypart colors changes
        //like sliding colors (from green to ligth blue)
        setSnakeBodyColor();
        bodyPart->setPen(whitePen);

        //Adding bodypart to scene
        scene_->addItem(bodyPart);

        //Deleting last rectangle from the scene and front of the bodyparts
        //this is done because new bodypart must not be the first item of
        //bodyparts because tail is first item (in this case empty rectangle).
        scene_->removeItem(bodyParts.front());
        delete bodyParts.front();
        bodyParts.front()=nullptr;
        bodyParts.pop_front();

        //Adding above defined bodypart to front of the bodyparts
        bodyParts.push_front(bodyPart);

        //Adding empty rectangle to bodyparts, because now the tail is done by
        //picture so this empty part is needed.
        QGraphicsRectItem* body_part2=new QGraphicsRectItem();
        scene_->addItem(body_part2);
        bodyParts.push_front(body_part2);
    }
}

void MainWindow::setSnakeBodyColor()
{
    //Explores is rbg-color blue value growing and if it is the rgbBlue value
    //is increased.
    if (isBlueValueGrowing)
    {
        rgbBlue+=BLUE_VALUE_CHANGING_SIZE;
    }
    //If blue value is decreasing the blue value is decreased.
    else
    {
        rgbBlue-=BLUE_VALUE_CHANGING_SIZE;
    }

    //When blue value reach it's maximum
    if (rgbBlue>255)
    {
        //Setting max value
        rgbBlue=255;

        //Setting blue value to decrease
        isBlueValueGrowing=false;
    }
    //When blue value reach its's minimum 0
    else if (rgbBlue<0)
    {
        //Setting minimum value
        rgbBlue=0;

        //Setting blue value to increase
        isBlueValueGrowing=true;
    }
}

void MainWindow::gameLostOrWon()
{
    //QString to show the player score
    QString scoreString=QString::number(score_, 'f', 0);

    //Checks is player lost or won the game and changing label text and screen
    //color
    if (board_->gameLost())
    {  
        //Setting game over text to endlabel
        endLabel_->setText("GAME OVER\nYour score:\n"+scoreString);

        //Setting window backround-color to red
        this->setStyleSheet("background-color: red;");

    }
    else if(board_->gameWon())
    {
        //Setting game won text to endlabel
        endLabel_->setText("YOU WON\nYour score:\n"+scoreString);

        //Setting window backround-color to green
        this->setStyleSheet("background-color: green;");
    }
    //If player has won or lost, showing endlabel and high scores. Also stopping
    //timers.
    if (board_->gameWon() or board_->gameLost())
    {
        //Hiding score
        scoreLabel_->hide();

        //Showing endlabel
        endLabel_->show();

        //Setting endlabel style
        endLabel_->setStyleSheet("color: rgb(255, 255, 255); "
                                 "background-color: rgb(0, 0, 0); "
                                 "border-radius: 10px; "
                                 "font: bold 50px; ");
        endLabel_->setAlignment(Qt::AlignCenter);
        endLabel_->setGeometry(WINDOW_WIDTH/2-ENDLABEL_SIZE/2,
                               WINDOW_WIDTH/2-ENDLABEL_SIZE/2,
                               ENDLABEL_SIZE+2, ENDLABEL_SIZE+2);
        //Showing high scores
        showHighScores();

        //Stopping both timers
        timer_.stop();
        timeTimer_->stop();
    }
}



void MainWindow::calculateScore()
{
    //Updating score when the snake eats food.
    //If screen is bigger the points per food are smaller. Player gets more
    //points when she/he takes next food fast.
    //Calculating screen parameters average so that screen size can be
    //considered.
    float average=(gameboardHeigth_+gameboardWidth_)/2;
    //Checks that score doesn't go infinity when dividing small number
    //totalSeconds_-lastFoodSeconds_ (this happens when snake takes next food
    //too fast).
    if (totalSeconds_-lastFoodSeconds_>=1)
    {
        score_=score_+(POINTS_PER_FOOD*(STEP/average))/(totalSeconds_-
                                                   lastFoodSeconds_);
    }
    else
    {
       score_=score_+(POINTS_PER_FOOD*(STEP/average));
    }
    //Setting score to label
    QString score="Score: \n"+QString::number(score_, 'f', 0);
    scoreLabel_->setText(score);

    //Storing the seconds when the last food is ate. This is needed for
    //calculating score.
    lastFoodSeconds_=totalSeconds_;

}

void MainWindow::setSnakeMoveFaster()
{

    //Sets snake move faster. The snake speed increased more if the gameboard
    //is bigger. Max duration is 120.
    if (duration_>MIN_DURATION)
    {
        duration_=duration_-((gameboardHeigth_+gameboardWidth_)/2)/(STEP*4);
        timer_.setInterval(duration_);
    }
}

void MainWindow::showHighScores()
{
    //Adds player to high scores table. Also brings high scores table to QString
    //from Data object playerData_.
    QString resultText=QString::fromStdString(playerData_.getResults(username_,
                                                                     score_));
    //Showing the resultlabel and setting it's text, wich is generated
    //above
    ui_->resultTableLabel->show();
    ui_->resultTableLabel->setText(resultText);
}

void MainWindow::onStartButtonClicked()
{
    //When user has given gameboard specs and username (optional) and clicked
    //start button the reset and pause buttons are showed. Also start button is
    //moved
    if (pauseButton_->isHidden() and resetButton_->isHidden())
    {
        //Buttons shows
        pauseButton_->show();
        resetButton_->show();

        //Moving startButton_
        startButton_->setGeometry(WINDOW_WIDTH/2+GAMEBOARD_MAX_SIZE/2
                                 -BUTTON_WIDTH,
                                 WINDOW_WIDTH/2-GAMEBOARD_MAX_SIZE/2-
                                 BUTTON_HEIGTH,
                                 BUTTON_WIDTH, BUTTON_HEIGTH);
    }
    //This is done only when game is paused
    if (!pauseButton_->isEnabled())
    {
        timer_.start(duration_);
        timeTimer_->start();
        pauseButton_->setDisabled(false);
        startButton_->setDisabled(true);
    }
    //When the game is started
    else
    {
        //Initing game
        gameInit();

        //Starting timer and stopwatch
        timeTimer_->start();
        timer_.start(duration_);

        //Button disapling and enablings
        pauseButton_->setDisabled(false);
        startButton_->setDisabled(true);

        //Hiding start screen labels and inputs
        ui_->spinBoxHeigth->hide();
        ui_->spinBoxSeed->hide();
        ui_->spinBoxWidth->hide();
        ui_->labelHeigth->hide();
        ui_->labelWidth->hide();
        ui_->labelSeed->hide();
        ui_->labelUsername->hide();
        ui_->usernameLineEdit->hide();
     }
}

void MainWindow::onResetButtonClicked()
{
    //Hiding game over label if its showing
    endLabel_->hide();

    //setting windon backround-color black if its red
    this->setStyleSheet("background-color: black;");

    //Stopping timer
    timer_.stop();

    //Stopping stopwatch and hiding it
    timeTimer_->stop();
    ui_->labelTime->hide();

    //Removing snake parts from the scene and deleting them. Taken care off that
    //What is snake size.
    //Head remove
    scene_->removeItem(snakeHead_);
    delete snakeHead_;
    snakeHead_=nullptr;

    //Tail remove
    if(snakeBodySize_>=3)
    {
        scene_->removeItem(snakeTail_);
        delete snakeTail_;
        snakeTail_=nullptr;
    }

    //Bodyparts remove
    for (QGraphicsRectItem* part : bodyParts)
    {
        scene_->removeItem(part);
        delete part;
        part=nullptr;
    }
    bodyParts.clear();
    //board_ delete
    delete board_;
    board_=nullptr;
    //Setting snake bodysize back to 1
     snakeBodySize_=1;

    //hiding graphicsview
    view_->hide();

    //Enabling startButton_ and setting it to initial position
    startButton_->setDisabled(false);
    startButton_->setGeometry(WINDOW_WIDTH/2-BUTTON_WIDTH/2, GAMEBOARD_MAX_SIZE,
                             BUTTON_WIDTH, BUTTON_HEIGTH);

    //Showing gameboard specs labels, spinboxes and line-edits, so user can
    //to edit gameboard specs
    ui_->labelHeigth->show();
    ui_->labelWidth->show();
    ui_->labelSeed->show();
    ui_->labelUsername->show();
    ui_->usernameLineEdit->show();
    ui_->spinBoxHeigth->show();
    ui_->spinBoxSeed->show();
    ui_->spinBoxWidth->show();

    //hiding food
    foodLabel_->hide();

    //button hides
    resetButton_->hide();
    //Enaling pauseButton_ if reset is done when pause button is not enabled.
    if (!pauseButton_->isEnabled())
    {
        pauseButton_->setEnabled(true);
    }
    pauseButton_->hide();

    //disabling snake move
    rigth_=false;
    left_=false;
    up_=false;
    down_=false;

    //Setting blue rgb-value back to zero.
    rgbBlue=0;

    //Reseting time parameters.
    minutes_=0;
    seconds_=0;
    totalSeconds_=0;
    lastFoodSeconds_=0;

    //Reseting score
    score_=0;

    //Setting snake speed to default
    duration_ = DEFAULT_DURATION;
    //Hiding high scores
    ui_->resultTableLabel->hide();
    //Hiding scorelabel
    scoreLabel_->hide();
}

void MainWindow::onPauseButtonClicked()
{
    //Stopping timers
    timer_.stop();
    timeTimer_->stop();

    //Enabling startButton_
    startButton_->setDisabled(false);

    //Disapling pauseButton_
    pauseButton_->setDisabled(true);
}


void MainWindow::on_spinBoxHeigth_valueChanged(int arg1)
{
    //Changing gameboard heigth attribute when the screen heigth spinbox value
    //is changed.
    gameboardHeigth_=arg1;
}


void MainWindow::on_spinBoxWidth_valueChanged(int arg1)
{
    //Changing gameboard width attribute when the screen width spinbox value
    //is changed.
    gameboardWidth_=arg1;

}


void MainWindow::on_usernameLineEdit_textChanged(const QString &arg1)
{
    //Changing username attribute when username line edit text is changed.
    username_=arg1.toStdString();
}


void MainWindow::on_spinBoxSeed_valueChanged(int arg1)
{
    //Changing seed attribute when seed value spinbox is changed.
    seed_=arg1;
}


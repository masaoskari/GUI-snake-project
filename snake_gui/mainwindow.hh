/* ===========================
* Program author
* Name: Matti Linna
* Student number: 151072437
* UserID: ckmali
* E-Mail: matti.linna@tuni.fi
* ===========================
*
* This file is header file to Mainwindow class. Mainwindow is class wich
* contains all frontend to snake game. Classes methods and attributes
* are introduced here and you can read more details above method or attribute
* in guestion.
*
* */

#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH
#include "gameboard.hh"
#include "point.hh"
#include "data.hh"
#include <deque>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <QDialog>
#include <QLabel>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //Method for checking what key ("w", "a", "s", "d") user has pressed.
    //Sets snake to its moving direction: "w"=up, "a"=left, "s"=down, "d"=right.
    void keyPressEvent(QKeyEvent* event) override;


private slots:
    //Slots for buttons
    void onStartButtonClicked();
    void onResetButtonClicked();
    void onPauseButtonClicked();

    //Slot for updating stopwatch minutes and seconds which shows user the
    //spent time for the game.
    void updateTimer();

    //NOTE! Below this these slots are made with QT designer so their names are
    //automatically generated. Because of that names didn't follow same naming
    //conventions like other methods. NOTE!

    //Slots for changing gameboard heigth and width with spinboxes
    void on_spinBoxHeigth_valueChanged(int arg1);
    void on_spinBoxWidth_valueChanged(int arg1);

    //Slot for examining players username from line-edit
    void on_usernameLineEdit_textChanged(const QString &arg1);

    //Slot for changing GameBoard objects seed value with spinbox
    void on_spinBoxSeed_valueChanged(int arg1);

private:
    //Inits the game when user is on startscreen and press play-button.
    //Method defines gameboard (its GameBoard object and its frontend
    //graphicsview and scene) with user given specs. Method also sets snake's
    //head and food to the gameboard. Also sets stopwatch and scorelabel on the
    //screen.
    void gameInit();

    //Moves snake and checks is player lost or won the game. Method is called
    //when timer_ singleShot duration is spent.
    void checkEvent();

    //Moves snake user desired direction on the gameboard. Also moves food
    //when snake eats it and grows the snake. Updates score when the food is
    //eaten.
    void snakeMove();

    //Sets food (bananas) on the screen. Method needs "bananas.png"-image to be
    //in build directory to do that.
    void drawFood();

    //Sets snakes head on the screen. Method needs "headVol2.png"-image to be
    //in build directory to do that.
    void printSnake();

    //Grows snake with rectangles when the snake has eaten food. Adds tail to
    //snake when its bodysize is 3.
    void growSnake();

    //Changing snake bodypart colors so that different bodypart colors changes
    //like sliding colors (from green to ligth blue and from ligth blue to
    //green)
    void setSnakeBodyColor();

    //Brings that information is player won or lost to frontend (here) from
    //GameBoard object board_. Also shows player endlabel and highscores when
    //the game ends. Stops timers.
    void gameLostOrWon();

    //Calculates player score and updates it to screen. The score/per food
    //depends on how big the gameboard is and how much time is spent when
    //the last food is eaten.
    void calculateScore();

    //Makes snake food faster. The snake speeds up when the snake eats food.
    //When the game area is bigger the snake speeds up more.
    void setSnakeMoveFaster();

    //Adds user score to highscores table (if user has given name). Shows
    //five best players highscores. If the player is not in top five shows
    //player the player position and score at the end of highscores table.
    //Also shows error message if highscores are not found.
    void showHighScores();

    Ui::MainWindow *ui_;
    //Scene to for handling game objects
    QGraphicsScene* scene_;
    //View to show gameboard
    QGraphicsView* view_;

    //Game buttons
    QPushButton* pauseButton_;
    QPushButton* startButton_;
    QPushButton* resetButton_;

    //Food label to show snakes food on the gameboard
    QLabel* foodLabel_;

    //Booleans for turning
    bool left_=false;
    bool rigth_=false;
    bool up_=false;
    bool down_=false;

    //Gameboard heigth and width. Defaults are 500 and 500.
    int gameboardHeigth_=500;
    int gameboardWidth_=500;

    //value for seed
    int seed_=0;

    //GameBoard object which handles snake and fruit coordinates
    GameBoard* board_;

    //Pictures to snake head and tail
    QGraphicsPixmapItem* snakeHead_;
    QGraphicsPixmapItem* snakeTail_;

    //Rectangles to snake body
    std::deque<QGraphicsRectItem*> bodyParts;

    //rgb_blue value for changing snake body colors
    int rgbBlue=0;
    bool isBlueValueGrowing=true;

    //Timer for snake moving
    QTimer timer_;

    //Stopwatch to show time for player
    QTimer* timeTimer_;
    //Attributes to handle timer seconds and minutes
    uint minutes_=0;
    uint seconds_=0;

    //Label to show, when game ends
    QLabel* endLabel_;

    //Attribute to player username
    std::string username_="";

    //Data object to handle highscores list
    Data playerData_=Data("data.txt");

    //Attributes to calculate player score
    uint snakeBodySize_=1;
    uint totalSeconds_=0;
    uint lastFoodSeconds_=0;

    //Attribute to player score
    float score_=0;

    //Label to visualize player score in real time
    QLabel* scoreLabel_;

    //Some constant values to use
    //How many pixels snake move at the one step
    const int STEP = 20;

    //Default duration in ms when snake is moved.
    const int DEFAULT_DURATION=250;

    //Min duration to block that snake doesn't go too fast when the game proceed
    const int MIN_DURATION=120;

    //Setted window width (px)
    const int WINDOW_WIDTH=850;

    //Gameboards max width and heigth (px)
    const int GAMEBOARD_MAX_SIZE=500;

    //Food size (px)
    const int FOOD_SIZE=20;

    //Constant to be used in calculating score.
    const int POINTS_PER_FOOD=1000;

    //How much blue rgb-value changes when the blocks are added to snake body.
    const int BLUE_VALUE_CHANGING_SIZE=30;

    //Size to endlabel (px)
    const int ENDLABEL_SIZE=300;

    //Default button specs
    const int BUTTON_WIDTH=100;
    const int BUTTON_HEIGTH=50;

    //Attribute to take care of how many milliseconds snake move takes. It
    //is updated when snake eats food.
    int duration_ = DEFAULT_DURATION;

};
#endif // MAINWINDOW_HH

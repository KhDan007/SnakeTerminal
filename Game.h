#if !defined(GAME_H)
#define GAME_H

// Inluding libraries
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <WinUser.h>

class Game
{
private:
    bool isStart;
    bool isGameOver;
    int m_width, m_height; // parameters of the size of box
    int m_delay; // delay of drawing everything (ms)
     
    int x, y; // coordinates of player
    int fruitX, fruitY; // coordinates of fruit
    int score; // count of collected fruits
    
    enum eDirection {STOP=0, UP, DOWN, RIGHT, LEFT}; // creating each of direction
    eDirection dir;

    enum eDeathReason {NONE=0, WALL, TAIL};
    eDeathReason death;

    int tailX[100], tailY[100]; // coordinates of whole tail (arrays)
    int tailLength;

public:
    // Constructor
    Game(const char* window_name, int width, int height);
    // Destructor
    ~Game();

    // Setters
    void setDelay(int delay) {
        m_delay = delay;
    }

    // Drawing method
    void draw();

    // Clearing method
    void clear();

    // Input method
    void input();

    // Logic method
    void logic();

    // Define and show death reason
    void showDeath();

    // Confirm exit from app
    void confirmExit();

    void welcome();

    // Run method
    void run() {
        // Game loop
        while(!isGameOver) {
            clear();
            draw();
            input();
            logic();
            Sleep(m_delay); // delay to avoid blinks
        }
        showDeath();
        confirmExit();
    }
};




#endif
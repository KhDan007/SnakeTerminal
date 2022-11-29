#include "Game.h"

Game::Game(const char* window_name, int width, int height)
{
    // Setting up the game parameters
    isGameOver = false;
    isStart = false;
    m_width = width;
    m_height = height;
    m_delay = 100;
    score = 0;

    // Settong up window name
    SetConsoleTitleA(window_name);
    
    // Centering the player
    x = (m_width % 2 == 0) ? (m_width / 2) : (m_width + 1) / 2;
    y = (m_height % 2 == 0) ? (m_height / 2) : (m_height + 1) / 2;

    // Randomly spawning the fruit
    std::srand(time(0));
    fruitX = std::rand() % m_width;
    fruitY = std::rand() % m_height;

    // Setting up default direction (stop)
    dir = STOP;

    // Setting up default death reason
    death = NONE;

    tailLength = 0;
}

// Clearing method
void Game::clear() {
    system("CLS");
}


// Drawing method
void Game::draw()
{
    // Drawing welcome meassage
    welcome();

    // Drawing the top side of the border
    for (int i{}; i < m_width; i++)
    {
        std::cout << "#";
    }
    std::cout << std::endl;

    // Drawing the center part of the box (including side borders)
    for (int i{}; i < m_height; i++)
    {
        for (int j{}; j < m_width; j++)
        {
            // When we should draw borders
            if (j == 0 || j == m_width - 1)
            {
                std::cout << "#";
            } else if (j == x && i == y) { // When we should draw player
                std::cout << "O";
            } else if (j == fruitX && i == fruitY) { // When we should draw fruit
                std::cout << "@";
            }
            else
            { 
                bool print = false;

                for (int k{}; k < tailLength; k++) {
                    if (j == tailX[k] && i == tailY[k]) {
                        std::cout << "o";
                        print = true;
                    }
                }

            // In other case we should draw spaces
                if (!print) {
                    std::cout << " ";
                }
            }
        }
        std::cout << std::endl;
    }

    // Drawing the bottom side of the border
    for (int i{}; i < m_width; i++)
    {
        std::cout << "#";
    }
    std::cout << std::endl;

    // Showing score
    std::cout << "Score: " << score << std::endl;
}

void Game::input() {
    if (_kbhit()) {
        switch (_getch()) // Giving the direction according to the key
        {
        case 'w':
            if (dir != DOWN) dir = UP; // to avoid rotating 180 degree (if we look up we cannot rotate down)
            isStart = true;
            break;
        case 's':
            if (dir != UP) dir = DOWN;
            isStart = true;
            break;
        case 'a':
            if (dir != RIGHT) dir = LEFT;
            isStart = true;
            break;
        case 'd':
            if (dir != LEFT) dir = RIGHT;
            isStart = true;
            break;
        default:
            break;
        }
    }
}

void Game::logic() {
    // If fruit spawns in the border - respawn
    if (fruitX == 0 || fruitX == m_width-1 || fruitY == -1 || fruitY == m_height) {
        fruitX = std::rand() % m_width;
        fruitY = std::rand() % m_height;
    }

    // Logic of tail
    // Creating variables to keep track of tail
    int prevX = tailX[0];
    int prevY = tailY[0];

    // The first element of tail is head    
    tailX[0] = x;
    tailY[0] = y;

    // Creating 2 another variables to keep track of tail
    int prevToX, prevToY;

    // 
    for (int i{1}; i < tailLength; i++) {
        prevToX = tailX[i];
        prevToY = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prevToX;
        prevY = prevToY;
    }

    // Moving up down left right
    switch (dir)
    {
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    default:
        break;
    }

    // If the player goes out from the arena, he will lose
    if (x < 1 || x > m_width - 2 || y < 0 || y > m_height - 1) {
        death = WALL;
        isGameOver = true;
    }

    // If the player eats a fruit, score increases and spawns a new fruit
    if (x == fruitX && y == fruitY) {
        score++;
        fruitX = std::rand() % m_width;
        fruitY = std::rand() % m_height;
        tailLength++;
    }

    // If head collide with the tail
    for (int i{}; i < tailLength; i++) {
        if (x == tailX[i] && y == tailY[i]) {
            death = TAIL;
            isGameOver = true;
        }
    }
}

void Game::showDeath() {
    switch (death) {
        case WALL:
            std::cout << "You died from collision with wall!" << std::endl;
            break;
        case TAIL:
            std::cout << "You died from a collision with your tail!" << std::endl;
            break;
        default:
            break;
    }    
}

void Game::confirmExit() {
    std::string a;
    std::cout << "Type 'exit' to exit: ";
    do {
        std::cin >> a;
    } while (a != "exit");
}

void Game::welcome() {
    if (!isStart) {
        std::cout << "Hello, welcome to the snake! Press w/a/s/d to start (O - Snake; @ - Fruit)" << std::endl << std::endl;
    }
}

Game::~Game()
{
}
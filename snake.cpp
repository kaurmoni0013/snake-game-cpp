#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <fstream>

using namespace std;

bool gameOver;

const int width = 20;
const int height = 20;

int x, y;
int fruitX, fruitY;

int score;
int highScore = 0;

int tailX[100], tailY[100];
int nTail;

enum eDirection
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

eDirection dir;

int gameSpeed = 120;

void gotoxy(int x, int y)
{
    COORD coord;

    coord.X = x;
    coord.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void hideCursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO info;

    info.dwSize = 100;
    info.bVisible = false;

    SetConsoleCursorInfo(consoleHandle, &info);
}

void loadHighScore()
{
    ifstream file("highscore.txt");

    if (file.is_open())
    {
        file >> highScore;
        file.close();
    }
}

void saveHighScore()
{
    ofstream file("highscore.txt");

    if (file.is_open())
    {
        file << highScore;
        file.close();
    }
}

void chooseDifficulty()
{
    int choice;

    cout << "===== SNAKE GAME =====" << endl;
    cout << "1. Easy" << endl;
    cout << "2. Medium" << endl;
    cout << "3. Hard" << endl;

    cout << "\nChoose Difficulty: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        gameSpeed = 200;
        break;

    case 2:
        gameSpeed = 180;
        break;

    case 3:
        gameSpeed = 120;
        break;

    default:
        gameSpeed = 120;
    }

    system("cls");
}

void setup()
{
    gameOver = false;

    dir = STOP;

    x = width / 2;
    y = height / 2;

    fruitX = rand() % width;
    fruitY = rand() % height;

    score = 0;

    nTail = 0;
}

void draw()
{
    system("cls");

    // Top Wall
    for (int i = 0; i < width + 2; i++)
        cout << "#";

    cout << endl;

    // Game Area
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "#";

            if (i == y && j == x)
            {
                cout << "O";
            }
            else
            {
                bool print = false;

                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }

                if (!print)
                {
                    if (i == fruitY && j == fruitX)
                        cout << "*";
                    else
                        cout << " ";
                }
            }

            if (j == width - 1)
                cout << "#";
        }

        cout << endl;
    }

    // Bottom Wall
    for (int i = 0; i < width + 2; i++)
        cout << "#";

    cout << endl;

    cout << "Score      : " << score << endl;
    cout << "High Score : " << highScore << endl;

    cout << "\nControls: W A S D | Press X to Exit" << endl;

    cout.flush();
}

void input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            if (dir != RIGHT)
                dir = LEFT;
            break;

        case 'd':
            if (dir != LEFT)
                dir = RIGHT;
            break;

        case 'w':
            if (dir != DOWN)
                dir = UP;
            break;

        case 's':
            if (dir != UP)
                dir = DOWN;
            break;

        case 'x':
            gameOver = true;
            break;
        }
    }
}

void logic()
{
    // Tail Movement
    int prevX = tailX[0];
    int prevY = tailY[0];

    int prev2X, prev2Y;

    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];

        tailX[i] = prevX;
        tailY[i] = prevY;

        prevX = prev2X;
        prevY = prev2Y;
    }

    // Snake Movement
    switch (dir)
    {
    case LEFT:
        x--;
        break;

    case RIGHT:
        x++;
        break;

    case UP:
        y--;
        break;

    case DOWN:
        y++;
        break;

    default:
        break;
    }

    // Wall Collision
    if (x >= width || x < 0 || y >= height || y < 0)
        gameOver = true;

    // Self Collision
    for (int i = 0; i < nTail; i++)
    {
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;
    }

    // Fruit Collision
    if (x == fruitX && y == fruitY)
    {
        score += 10;

        if (score > highScore)
        {
            highScore = score;
            saveHighScore();
        }

        fruitX = rand() % width;
        fruitY = rand() % height;

        nTail++;
    }
}

int main()
{
    srand(time(0));

    hideCursor();

    loadHighScore();

    chooseDifficulty();

    setup();

    while (!gameOver)
    {
        draw();
        input();
        logic();

        Sleep(gameSpeed);
    }

    system("cls");

    cout << "===== GAME OVER =====" << endl;

    cout << "Final Score : " << score << endl;
    cout << "High Score  : " << highScore << endl;

    return 0;
}
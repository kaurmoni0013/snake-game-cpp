#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
using namespace std;
bool gameOver;
int width = 20;
int height = 20;

int x, y;
int fruitX, fruitY;

int score;

enum eDirection
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};
eDirection dir;
// Setup Function
void setup()
{

    gameOver = false;

    x = width / 2;
    y = height / 2;

    fruitX = 5;
    fruitY = 7;

    score = 0;
    dir = STOP;
}

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void draw()
{
    gotoxy(0, 0);
    // Top wall
    for (int i = 0; i < width + 2; i++)

        cout << "#";

    cout << endl;
    // side wall + snake + fruit

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            if (j == 0)
                cout << "#";

            if (i == y && j == x)
                cout << "O"; // Snake Head

            else if (i == fruitY && j == fruitX)
                cout << "*"; // Fruit

            else
                cout << " ";

            if (j == width - 1)
                cout << "#";
        }

        cout << endl;
    }

    // Bottom Wall
    for (int i = 0; i < width + 2; i++)
        cout << "#";

    cout << endl;

    cout << "Score: " << score << endl;
    cout.flush();
}

void input()
{

    if (_kbhit())
    {

        switch (_getch())
        {

        case 'a':
            dir = LEFT;
            break;

        case 'd':
            dir = RIGHT;
            break;

        case 'w':
            dir = UP;
            break;

        case 's':
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

    // Fruit Collision
    if (x == fruitX && y == fruitY)
    {
        score += 10;

        fruitX = rand() % width;
        fruitY = rand() % height;
    }
}

void hideCursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO info;

    info.dwSize = 100;
    info.bVisible = false;

    SetConsoleCursorInfo(consoleHandle, &info);
}

int main()
{
    system("cls");
    gameOver = false;
    srand(time(0)); // initialize random seed
    hideCursor();
    setup();
    while (!gameOver)
    {

        draw();
        input();
        logic();
        Sleep(200);
    }
    return 0;
}
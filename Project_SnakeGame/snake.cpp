#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>

using namespace std;

const int width = 20;
const int height = 20;
bool gameOver;
int x, y, fruitX, fruitY, score, Cbomb=50, screenCount=0;
int tailX[100], tailY[100], bombX[10], bombY[10];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    //bombX = fruitX + 3;
    //bombY = fruitY + 3;
    for (int n = 0; n < 10; n++) {
        bombX[n] = rand() % width;
        bombY[n] = rand() % height;
    }
}


void Draw() {
    system("cls"); // Clear the console

    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                cout << "#"; // Left wall

            else if (i == y && j == x)
                if (dir == LEFT)
                    cout << "<";
                else if (dir == RIGHT)
                    cout << ">";
                else if (dir == UP)
                    cout << "^";
                else if (dir == DOWN)
                    cout << "v";// Snake head
                else
                    cout << "x";

            else if (i == fruitY && j == fruitX)
                cout << "F"; // Fruit

            //else if (i == bombY && j == bombX)
            //    cout << "B"; // Bomb
            else {
                bool printBomb = false;
                for (int n = 0; n < 10; n++) {
                    if (i == bombY[n] && j == bombX[n]) {
                        cout << "B"; // Bomb
                        printBomb = true;
                        break;
                    }
                }

                bool printTail = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o"; // Snake tail
                        printTail = true;
                    }
                }
                if (!printTail && !printBomb)
                    cout << " ";
            }
            if (j == width - 1)
                cout << "#"; // Right wall
        }
        cout << endl;
    }
    for (int i = 0; i < width + 2; i++)
        cout << "#";

    cout << endl;

    screenCount++;
    if (screenCount == Cbomb) {
        for (int n = 0; n < 10; n++) {
            bombX[n] = rand() % width;
            bombY[n] = rand() % height;
        }
       //bombX = rand() % width;
       //bombY = rand() % height;
       // bomb near
       // bombX = fruitX + 3;
       // bombY = fruitY + 3;
        screenCount = 0;
    }

    cout << "Score:" << score << endl;
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
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

void Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) {
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
    }

    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;

    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;

    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }

    //if (x == bombX && y == bombY) {
    //    gameOver = true;
    //}
    for (int n = 0; n < 10; n++) {
        if (x == bombX[n] && y == bombY[n]) {
            gameOver = true;
            break;
        }
    }
}

int main() {
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(100); // Sleep for 100 milliseconds to control the game speed
    }
    cout << "  ____    _    __  __ _____    _____     _______ ____    _ " << endl;
    cout << " / ___|  / \\  |  \\/  | ____|  / _ \\ \\   / / ____|  _ \\  | |" << endl;
    cout << "| |  _  / _ \\ | |\\/| |  _|   | | | \\ \\ / /|  _| | |_) | | |" << endl;
    cout << "| |_| |/ ___ \\| |  | | |___  | |_| |\\ V / | |___|  _ <  |_|" << endl;
    cout << " \\____/_/   \\_\\_|  |_|_____|  \\___/  \\_/  |_____|_| \\_\\ (_)" << endl;
    //cout << "Press any key to exit...";
    system("pause"); // Pause
    
    return 0;
}

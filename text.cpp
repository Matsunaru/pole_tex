#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <thread> 
#include <chrono>


using namespace std::chrono_literals;
using namespace std;

HANDLE console;

const int TEXT_BOX_WIDTH = 10;
const int TEXT_BOX_HEIGHT = 1;
const int START_X = 10;
const int START_Y = 20;

int cursorPosition = 0;

void Draw() {
    COORD pos;
    pos.X = START_X;
    pos.Y = START_Y;


    SetConsoleTextAttribute(console, BACKGROUND_BLUE);

    for (int i = 0; i < TEXT_BOX_WIDTH; ++i) {
        SetConsoleCursorPosition(console, pos);
        std::cout << " ";
        pos.X++;
    }

    SetConsoleTextAttribute(console, 0);
}

void MoveCursorLeft() {
    if (cursorPosition > 0) {
        cursorPosition--;
    }
}

void MoveCursorRight() {
    if (cursorPosition < TEXT_BOX_WIDTH - 1) {
        cursorPosition++;
    }
}

void DrawCursor() {
    COORD cursorPos;
    cursorPos.X = START_X + cursorPosition;
    cursorPos.Y = START_Y;
    SetConsoleCursorPosition(console, cursorPos);
}

int main()
{
    console = GetStdHandle(STD_OUTPUT_HANDLE);
    Draw();
    DrawCursor();
    while (true) {
    if (_kbhit()) {
        char key = _getch();
        if (key == 75) { 
            MoveCursorLeft();
        }
        else if (key == 77) { 
            MoveCursorRight();
        }
        else if ((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z')) {
            COORD pos;
            pos.X = START_X + cursorPosition;
            pos.Y = START_Y;
            SetConsoleCursorPosition(console, pos);
            std::cout << 'X';
            MoveCursorRight();
        }
        DrawCursor(); 
    }
}
    
    return 0;
}
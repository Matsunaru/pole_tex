#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <thread> 
#include <chrono>


using namespace std::chrono_literals;
using namespace std;

HANDLE console;

const int TEXT_BOX_WIDTH = 11;
const int TEXT_BOX_HEIGHT = 1;
const int START_X = 30;
const int START_Y = 10;

int cursorPosition = 0;
char textBox[TEXT_BOX_WIDTH + 1] = {};
WORD textAttributes[TEXT_BOX_WIDTH] = {};

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

void InsertChar(char key) {
    if (cursorPosition < TEXT_BOX_WIDTH - 1) {
        textBox[cursorPosition] = key;
        textAttributes[cursorPosition] = FOREGROUND_RED | BACKGROUND_BLUE;
        cursorPosition++;
    }
}



void RefreshTextBox() {
    COORD pos;
    pos.X = START_X;
    pos.Y = START_Y;
    SetConsoleCursorPosition(console, pos);
    for (int i = 0; i < TEXT_BOX_WIDTH; ++i) {
        SetConsoleTextAttribute(console, textAttributes[i]);
        std::cout << textBox[i];
    }
    SetConsoleTextAttribute(console, 0);
}

void DeleteChar() {
    if (cursorPosition > 0) {
        std::move(textBox + cursorPosition, textBox + TEXT_BOX_WIDTH, textBox + cursorPosition - 1);
        std::move(textAttributes + cursorPosition, textAttributes + TEXT_BOX_WIDTH, textAttributes + cursorPosition - 1);

        textBox[TEXT_BOX_WIDTH - 1] = ' ';
        textAttributes[TEXT_BOX_WIDTH - 1] = BACKGROUND_BLUE;

        cursorPosition--;

        RefreshTextBox();
    }
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
                InsertChar(key);
                RefreshTextBox();
            }
            else if (key == 8) {
                DeleteChar();
                

            }


            DrawCursor();
        }
    }

    return 0;
}
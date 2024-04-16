#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <thread> 
#include <chrono>

using namespace std::chrono_literals;
using namespace std;

HANDLE console;

const int TEXT_BOX_WIDTH = 11;  // Width of the text box
const int START_X = 30;          // Starting X coordinate of the text box
const int START_Y = 10;          // Starting Y coordinate of the text box

int cursorPosition = 0;          // Current cursor position in the text box
char textBox[TEXT_BOX_WIDTH + 1] = {};   // Array to store characters in the text box
WORD textAttributes[TEXT_BOX_WIDTH] = {};  // Array to store text attributes (e.g., color) for each character
int textBoxLength = 0;           // Current length of the text in the text box

// Function to draw the initial state of the text box
void Draw() {
    COORD pos;
    pos.X = START_X;
    pos.Y = START_Y;

    // Set background color for the text box
    SetConsoleTextAttribute(console, BACKGROUND_BLUE);

    // Draw the text box
    for (int i = 0; i < TEXT_BOX_WIDTH; ++i) {
        SetConsoleCursorPosition(console, pos);
        std::cout << " ";
        pos.X++;
    }

    // Reset text attributes
    SetConsoleTextAttribute(console, 0);
}

// Function to move the cursor left
void MoveCursorLeft() {
    if (cursorPosition > 0) {
        cursorPosition--;
    }
}

// Function to move the cursor right
void MoveCursorRight() {
    if (cursorPosition < textBoxLength) {
        cursorPosition++;
    }
}

// Function to draw the cursor at its current position
void DrawCursor() {
    COORD cursorPos;
    cursorPos.X = START_X + cursorPosition;
    cursorPos.Y = START_Y;
    SetConsoleCursorPosition(console, cursorPos);
}

// Function to insert a character into the text box at the cursor position
void InsertChar(char key) {
    if (cursorPosition < TEXT_BOX_WIDTH - 1 && textBoxLength < TEXT_BOX_WIDTH - 1) {
        // Shift characters to the right to make space for the new character
        for (int i = textBoxLength; i > cursorPosition; --i) {
            textBox[i] = textBox[i - 1];
            textAttributes[i] = textAttributes[i - 1];
        }
        // Insert the new character at the cursor position
        textBox[cursorPosition] = key;
        textAttributes[cursorPosition] = FOREGROUND_RED | BACKGROUND_BLUE;
        cursorPosition++;
        textBoxLength++;
    }
}

// Function to refresh the text box display
void RefreshTextBox() {
    COORD pos;
    pos.X = START_X;
    pos.Y = START_Y;
    SetConsoleCursorPosition(console, pos);
    // Print each character in the text box with its corresponding text attributes
    for (int i = 0; i < TEXT_BOX_WIDTH; ++i) {
        SetConsoleTextAttribute(console, textAttributes[i]);
        std::cout << textBox[i];
    }
    // Reset text attributes
    SetConsoleTextAttribute(console, 0);
}

// Function to delete a character from the text box at the cursor position
void DeleteChar() {
    if (cursorPosition > 0) {
        // Shift characters to the left to remove the character at the cursor position
        std::move(textBox + cursorPosition, textBox + textBoxLength + 1, textBox + cursorPosition - 1);
        std::move(textAttributes + cursorPosition, textAttributes + textBoxLength, textAttributes + cursorPosition - 1);

        // Replace the last character with a space
        textBox[TEXT_BOX_WIDTH - 1] = ' ';
        textAttributes[TEXT_BOX_WIDTH - 1] = BACKGROUND_BLUE;

        // Move the cursor position and update the text box length
        cursorPosition--;
        textBoxLength--;

        // Refresh the text box display
        RefreshTextBox();
    }
}

int main()
{
    // Get the handle to the console
    console = GetStdHandle(STD_OUTPUT_HANDLE);

    // Draw the initial state of the text box
    Draw();

    // Draw the cursor at the initial position
    DrawCursor();

    // Main loop for handling user input
    while (true) {
        if (_kbhit()) {
            char key = _getch();
            if (key == -32) {
                key = _getch();
                if (key == 75) {
                    // Left arrow key pressed, move the cursor left
                    MoveCursorLeft();
                }
                else if (key == 77) {
                    // Right arrow key pressed, move the cursor right
                    MoveCursorRight();
                }
            }
            else if ((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z')) {
                // Alphabetic character pressed, insert it into the text box
                InsertChar(key);
                // Refresh the text box display
                RefreshTextBox();
            }
            else if (key == 8) {
                // Backspace key pressed, delete the character before the cursor
                DeleteChar();
            }

            // Draw the cursor at its updated position
            DrawCursor();
        }
    }

    return 0;
}

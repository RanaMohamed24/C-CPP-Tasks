#include "header.h"
#include <cstdlib>
#include <iostream>

using namespace std;

#if defined(_WIN32)
WORD windowsColorMap[] = {
    0,                                                         // BLACK
    FOREGROUND_RED | FOREGROUND_INTENSITY,                     // RED
    FOREGROUND_GREEN | FOREGROUND_INTENSITY,                   // GREEN
    FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,  // YELLOW
    FOREGROUND_BLUE | FOREGROUND_INTENSITY,                    // BLUE
    FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY,   // MAGENTA
    FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY, // CYAN
    FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE        // WHITE (no intensity or you can add INTENSITY)
};
#endif

int linuxColorMap[] = {
    30, // BLACK
    31, // RED
    32, // GREEN
    33, // YELLOW
    34, // BLUE
    35, // MAGENTA
    36, // CYAN
    37  // WHITE
};

void setColor(Color color)
{
#if defined(_WIN32)
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    WORD attr = windowsColorMap[(int)color];
    SetConsoleTextAttribute(hConsole, attr);
#else
    int ansi = linuxColorMap[(int)color];
    cout << "\033[" << ansi << "m";
#endif
}

void clearScreen()
{
#if defined(_WIN32)
    system("cls");
#else
    system("clear");
#endif
}

void moveCursor(int row, int col)
{
#if defined(_WIN32)
    COORD coord;
    coord.X = col - 1;
    coord.Y = row - 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
#else
    cout << "\033[" << row << ";" << col << "H";
#endif
}

void printColoredText(const string &text, Color color, int row, int col)
{
    moveCursor(row, col);
    setColor(color);
    cout << text;

#if defined(_WIN32)

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#else
    cout << "\033[0m";
#endif
}

void delay(int number)
{
#if defined(_WIN32)
    cout << endl
         << "Running on Windows!" << endl;
    Sleep(number * 1000);
#else
    cout << endl
         << "Running on Linux!" << endl;
    sleep(number);
#endif
}
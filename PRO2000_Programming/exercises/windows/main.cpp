// screen_control.cpp
// Object-oriented example: controlling the console screen in Windows.
//
// Concepts:
//   - The screen is a grid of 25 rows x 80 columns.
//   - Row 0 is at the top, column 0 at the left edge.
//   - A cell is identified by its (row, column) coordinates.
//
// Build (Visual Studio Developer Prompt):  cl /EHsc screen_control.cpp
// Build (MinGW):                           g++ screen_control.cpp -o screen_control.exe

#include <windows.h>
#include <iostream>
#include <string>

using namespace std;

// ---------------------------------------------------------------------------
// Screen: encapsulates the operating-system details of console output.
// Other classes never touch HANDLE or COORD directly.
// ---------------------------------------------------------------------------
class Screen
{
public:
    static const int ROWS = 25;
    static const int COLS = 80;

    Screen()
    {
        // Handle used to reference the output screen
        handle = GetStdHandle(STD_OUTPUT_HANDLE);
    }

    // Move the cursor to a cell. Returns false if the cell is off the grid.
    bool moveTo(int row, int col)
    {
        if (!isValidCell(row, col))
            return false;

        COORD position;          // holds the coordinates of a cell
        position.X = (SHORT)col; // X is the column
        position.Y = (SHORT)row; // Y is the row
        SetConsoleCursorPosition(handle, position);
        return true;
    }

    // Display text starting at a given cell.
    bool write(int row, int col, const string& text)
    {
        if (!moveTo(row, col))
            return false;
        cout << text << endl; // end with endl so the output is flushed
        return true;
    }

    // Blank the whole screen and send the cursor home (row 0, column 0).
    void clear()
    {
        COORD home = { 0, 0 };
        DWORD written;
        DWORD cells = ROWS * COLS;
        FillConsoleOutputCharacter(handle, ' ', cells, home, &written);
        moveTo(0, 0);
    }

    // Leave the cursor below the drawing area so the shell prompt is clean.
    void parkCursor()
    {
        moveTo(ROWS - 1, 0);
    }

    static bool isValidCell(int row, int col)
    {
        return row >= 0 && row < ROWS && col >= 0 && col < COLS;
    }

private:
    HANDLE handle;
};

// ---------------------------------------------------------------------------
// Label: a piece of text that knows where it lives on the screen.
// It uses a Screen object to draw itself (composition / "has-a").
// ---------------------------------------------------------------------------
class Label
{
public:
    Label(Screen& s, int row, int col, const string& text)
        : screen(s), row(row), col(col), text(text) {}

    void draw() const
    {
        screen.write(row, col, text);
    }

    void moveTo(int newRow, int newCol)
    {
        erase();
        row = newRow;
        col = newCol;
        draw();
    }

    // Overwrite the label with spaces.
    void erase() const
    {
        screen.write(row, col, string(text.length(), ' '));
    }

private:
    Screen& screen;
    int row;
    int col;
    string text;
};

// ---------------------------------------------------------------------------
// Demo
// ---------------------------------------------------------------------------
int main()
{
    Screen screen;
    screen.clear();

    // The example from the notes: row 12, column 30
    screen.write(12, 30, "Look at me!");
    Sleep(1500);

    // Mark the four corners of the 25 x 80 grid
    screen.write(0, 0, "Top-left (0,0)");
    screen.write(0, Screen::COLS - 17, "Top-right (0,79)");
    screen.write(Screen::ROWS - 2, 0, "Bottom-left (24,0)");
    screen.write(Screen::ROWS - 2, Screen::COLS - 20, "Bottom-right (24,79)");
    Sleep(1500);

    // Label objects that draw and move themselves
    Label title(screen, 2, 25, "OBJECT-ORIENTED SCREEN DEMO");
    title.draw();

    Label mover(screen, 6, 0, ">>> moving label >>>");
    for (int col = 0; col < 55; ++col)
    {
        mover.moveTo(6, col);
        Sleep(40);
    }

    // Off-grid cells are rejected by the class
    if (!screen.write(30, 100, "never shown"))
        screen.write(20, 20, "Cell (30,100) is outside the 25 x 80 grid.");

    screen.parkCursor();
    return 0;
}
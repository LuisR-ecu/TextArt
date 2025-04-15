/*
* This program allows display and editing of text art (also called ASCII art).
*/

#include <iostream>
#include <fstream>
#include <cctype>
#include <conio.h>
#include <windows.h>
using namespace std;

const int BUFFERSIZE = 20;
const int FILENAMESIZE = 255;
const int MAXROWS = 22;
const int MAXCOLS = 80;

// ASCII codes for special keys; for editing
const char ESC = 27;
const char LEFTARROW = 75;
const char UPARROW = 72;
const char RIGHTARROW = 77;
const char DOWNARROW = 80;
const char SPECIAL = (char)224;

/*
* Gets a filename from the user. If file can be opened for reading,
* this function loads the file's contents into canvas.
* File is a TXT file located in the SavedFiles folder.
* If file cannot be opened, error message is displayed and
* canvas is left unchanged.
*/
void loadCanvas(char canvas[][MAXCOLS]);

/*
* Gets a filename from the user. If file can be opened for writing,
* this function writes the canvas contents into the file.
* File is a TXT file located in the SavedFiles folder.
* If file cannot be opened, error message is displayed.
*/
void saveCanvas(char canvas[][MAXCOLS]);

/*
* Initializes canvas to contain all spaces.
*/
void initCanvas(char canvas[][MAXCOLS]);

/*
* Displays canvas contents on the screen, with a border
* around the right and bottom edges.
*/
void displayCanvas(char canvas[][MAXCOLS]);

/*
* Allows user to edit the canvas by moving the cursor around and
* entering characters. Editing continues until the ESC key is pressed.
*/
void editCanvas(char canvas[][MAXCOLS]);

/*
* Copies contents of the "from" canvas into the "to" canvas.
*/
void copyCanvas(char to[][MAXCOLS], char from[][MAXCOLS]);

/*
* Replaces all instances of a character in the canvas.
* oldCh is the character to be replaced.
* newCh character is the character to replace with.
*/
void replace(char canvas[][MAXCOLS], char oldCh, char newCh);

/*
* Shifts contents of the canvas by a specified number of rows and columns.
* rowValue is the number of rows by which to shift
*    positive numbers shift downward; negative numbers shift upward
* colValue is the number of rows by which to shift
*    positive numbers shift right; negative numbers shift left
*/
void moveCanvas(char canvas[][MAXCOLS], int rowValue, int colValue);

/*
* Clears a line on the output screen, then resets the cursor back to the
* beginning of this line.
* lineNum is the line number on the output screen to clear
* numOfChars is the number of characters to clear on this line
*/
void clearLine(int lineNum, int numOfChars);

/*
* Moves the cursor in the output window to a specified row and column.
* The next output produced by the program will begin at this position.
*/
void gotoxy(short row, short col);


int main()
{
    char canvas[MAXROWS][MAXCOLS]{};
    int rowValue = 0, colValue = 0;
    char oldCh = '\0', newCh = '\0';
    bool quit = false;

    // TODO: write code for the main program
    char input = '\0';

    while (!quit)
    {
        displayCanvas(canvas);
        cin >> input;

        switch (input)
        {
        case 'E': case 'e':
            editCanvas(canvas);
            break;
        case 'M': case 'm':
            moveCanvas(canvas, rowValue, colValue);
            break;
        case 'R': case 'r':
            replace(canvas, oldCh, newCh);
            break;
        case 'U': case 'u':
            break;
        case 'L': case 'l':
            loadCanvas(canvas);
            break;
        case 'S': case 's':
            saveCanvas(canvas);
            break;
        case 'Q': case 'q':
            quit = true;
            break;
        default:
            break;
        }

    }
    return 0;
}


void gotoxy(short row, short col)
{
    COORD pos = { col, row };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


void clearLine(int lineNum, int numOfChars)
{
    // Move cursor to the beginning of the specified line on the console
    gotoxy(lineNum, 0);

    // Write a specified number of spaces to overwrite characters
    for (int x = 0; x < numOfChars; x++)
        cout << " ";

    // Move cursor back to the beginning of the line
    gotoxy(lineNum, 0);
}


void replace(char canvas[][MAXCOLS], char oldCh, char newCh)
{
    cout << "Enter the character you'd like to replace:\t";
    cin >> oldCh;
    cout << "Enter the new character:\t";
    cin >> newCh;

    for (int row = 0; row < MAXROWS; row++) {
        for (int col = 0; col < MAXCOLS; col++) {
            if (canvas[row][col] == oldCh)
            {
                canvas[row][col] = newCh;
            }
        }
    }
}


void editCanvas(char canvas[][MAXCOLS])
{
    char input;
    int row = 1, col = 1;

    // Move cursor to row,col and then get
    gotoxy(row, col);

    while (true)
    {
        input = _getch();

        // TODO: write code for the function
            switch (input)
            {
            case LEFTARROW:
                if (col > 1)
                {
                    col--;
                    break;
                }
            case UPARROW:
                if (row > 1)
                {
                    row--;
                    break;
                }
            case RIGHTARROW:
                if (col < MAXCOLS - 1)
                {
                    col++;
                    break;
                }
            case DOWNARROW:
                if (row < MAXCOLS - 1)
                {
                    row++;
                    break;
                }
            case ESC:
                return;
            default:
                canvas[row][col] = input;
                break;
            }
            gotoxy(row, col);
        }
    }


void moveCanvas(char canvas[][MAXCOLS], int rowValue, int colValue)
{
    cout << "Enter a row value:\t";
    cin >> rowValue;
    cout << "Enter a column value:\t";
    cin >> colValue;

    // Check for out-of-bounds shifts
    if (abs(rowValue) >= MAXROWS || abs(colValue) >= MAXCOLS)
    {
        std::cerr << "Error: Shift would cause elements to go out of bounds." << std::endl;
        return;
    }

    // Create a temporary canvas to hold shifted elements 
    char tempCanvas[MAXROWS][MAXCOLS]{};

    // Using a temporary canvas
    for (int row = 0; row < MAXROWS; row++) {
        for (int col = 0; col < MAXCOLS; col++) {
            // Calculate new indices for the shifted characters
            int newRow = (row + rowValue) % MAXROWS;  // Wrap around for rows
            int newCol = (col + colValue) % MAXCOLS;  // Wrap around for columns
            tempCanvas[newRow][newCol] = canvas[row][col];
        }
    }

    copyCanvas(canvas, tempCanvas);

    /*// Copy the temporary canvas back to the original canvas
    for (int row = 0; row < MAXROWS; row++)
    {
        for (int col = 0; col < MAXCOLS; col++)
        {
            canvas[row][col] = tempCanvas[row][col];
        }
    }*/
}



void initCanvas(char canvas[][MAXCOLS])
{
    // Fill the canvas with spaces
    for (int row = 0; row < MAXROWS; row++) {
        for (int col = 0; col < MAXCOLS; col++) {
            canvas[row][col] = ' ';
        }
    }

    // Add top and bottom borders
    for (int col = 0; col < MAXCOLS; col++) {
        canvas[0][col] = canvas[MAXROWS - 1][col] = '-'; //Assigns a border to the top and the bottom
    }

    // Add left and right borders
    for (int row = 1; row < MAXROWS - 1; row++) {
        canvas[row][0] = canvas[row][MAXCOLS - 1] = '|'; //Assigns the border to the left side and the right side
    }

}


void displayCanvas(char canvas[][MAXCOLS])
{
   /* // fill the convas with spaces
    for (int i = 0; i < MAXROWS; i++)
    {
        for (int j = 0; j < MAXCOLS; j++)
        {
            canvas[i][j] = ' ';
        }
    }
    // add borders
    for (int i = 0; i < MAXROWS; i++)
    {
        canvas[i][MAXCOLS - 1] = '|'; // right border
    }
    for (int j = 0; j < MAXCOLS; j++)
    {
        canvas[MAXROWS - 1][j] = '-';// Bottom border
    }
    //print the canvas
    for (int i = 0; i < MAXROWS; i++)
    {
        for (int j = 0; j < MAXCOLS; j++)
        {
            printf("%c", canvas[i][j]);
        }
        printf("\n"); // Move to the next line after each row
    }*/

    initCanvas(canvas);

    for (int row = 0; row < MAXROWS; row++)
    {
        for (int col = 0; col < MAXCOLS; col++)
        {
            cout << canvas[row][col];
        }
        cout << endl;
    }

    cout << "<E>dit / <M>ove/ <R>eplace / <U>ndo / <S>ave / <Q>uit:\t";
}


void copyCanvas(char to[][MAXCOLS], char from[][MAXCOLS])
{
    // Iterate through each row and column of the 'from' canvas
    // and copy the characters to the 'to' canvas
    for (int row = 0; row < MAXROWS; row++) {
        for (int col = 0; col < MAXCOLS; col++) {
            to[row][col] = from[row][col];
        }
    }
}


void saveCanvas(char canvas[][MAXCOLS])
{
    // TODO: write code for the function
    char newFile[FILENAMESIZE]{};
    cout << "Please enter a file name(with '.txt' at the end. \t";
    cin.getline(newFile, FILENAMESIZE);
    cin.ignore();
    ofstream file(newFile);

}


void loadCanvas(char canvas[][MAXCOLS])
{
    // TODO: write code for the function

    char fileName[FILENAMESIZE]{};
    cout << "Enter the name of the file you would like to open:\t";
    cin.getline(fileName, FILENAMESIZE);
    cin.ignore();

    ifstream file(fileName);

    int row = 0;
    int col = 0;
    char ch;

    while (file.get(ch) && row < MAXROWS)
    {
        if (ch != '\n' && col < MAXCOLS)
        {
            canvas[row][col] = ch;
            col++;
        }
        else if (ch == '\n')
        {
            row++;
            col = 0; // Reset column for the next line
        }
    }
    if (!file.is_open())
    {
        cerr << "Error: Could not open file " << fileName << endl;

    }
    file.close();
}
/*
Gaming Console Program
*/
#include <bits/stdc++.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
using namespace std;

bool gameOver;
const int width = 30;
const int height = 15;
int x, y, fruitX, fruitY, score;
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

class SnakeGame
{
public:
    SnakeGame()
    {
        gameOver = false;
        x = width / 2;
        y = height / 2;
        fruitX = rand() % width;
        fruitY = rand() % height;
        score = 0;
        dir = STOP;
    }
    void Setup();
    void Input();
    void Logic();
};

void SnakeGame::Setup()
{
    system("cls");
    for (int i = 0; i < width + 2; i++)
    {
        if (i == 0)
            cout << "\xDA"; // Top-left corner
        else if (i == width + 1)
            cout << "\xBF"; // Top-right corner
        else
            cout << "\xC4"; // Horizontal border
    }
    cout << endl;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "\xB3"; // Vertical border
            if (i == y && j == x)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); // Set text color to green for the snake
                cout << "O";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // Set text color back to white (default)
            }
            else if (i == fruitY && j == fruitX)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); // Set text color to red for the fruit
                cout << '0';                                                  // Character code for a red circle (may display differently on some consoles)
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);  // Set text color back to white (default)
            }
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); // Set text color to green for the tail
                        cout << "o";
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // Set text color back to white (default)
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }
            if (j == width - 1)
                cout << "\xB3"; // Vertical border
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
    {
        if (i == 0)
            cout << "\xC0"; // Bottom-left corner
        else if (i == width + 1)
            cout << "\xD9"; // Bottom-right corner
        else
            cout << "\xC4"; // Horizontal border
    }
    cout << endl;
    cout << "Score:" << score << endl;
}

void SnakeGame::Input()
{
    if (_kbhit())
    {
        char key = _getch();
        switch (key)
        {
        case 'a':
            if (dir != RIGHT) // Prevent going right if currently moving left
                dir = LEFT;
            break;
        case 'd':
            if (dir != LEFT) // Prevent going left if currently moving right
                dir = RIGHT;
            break;
        case 'w':
            if (dir != DOWN) // Prevent going down if currently moving up
                dir = UP;
            break;
        case 's':
            if (dir != UP) // Prevent going up if currently moving down
                dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

void SnakeGame::Logic()
{
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

    if (x >= width)
        x = 0;
    else if (x < 0)
        x = width - 1;
    if (y >= height)
        y = 0;
    else if (y < 0)
        y = height - 1;

    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;

    if (x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}

class Grid
{
public:
    int board[4][4];
    Grid()
    {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                board[i][j] = 0;
        int i1, i2, i3, i4;
        i1 = rand() % 4;
        i2 = rand() % 4;
        while (1)
        {
            i3 = rand() % 4;
            i4 = rand() % 4;
            if (i3 != i1 && i4 != i2)
                break;
        }
        board[i1][i2] = 2;
        board[i3][i4] = 4;
    }
};

class Game2048 : public Grid
{
public:
    void upmove();
    void downmove();
    void leftmove();
    void rightmove();
    int IsOver(int temp[4][4]);
    int Check();
    void AddBlock();
    void Display();
};

void Game2048 ::upmove()
{
    int i, j, li, ri;
    for (j = 0; j < 4; j++)
    {
        li = 0, ri = j;
        for (i = 1; i < 4; i++)
        {
            if (board[i][j] != 0)
            {
                if (board[i - 1][j] == 0 || board[i - 1][j] == board[i][j])
                {
                    if (board[li][ri] == board[i][j])
                    {
                        board[li][ri] *= 2;
                        board[i][j] = 0;
                    }
                    else
                    {
                        if (board[li][ri] == 0)
                        {
                            board[li][ri] = board[i][j];
                            board[i][j] = 0;
                        }
                        else
                        {
                            board[++li][ri] = board[i][j];
                            board[i][j] = 0;
                        }
                    }
                }
                else
                    li++;
            }
        }
    }
}

void Game2048 ::downmove()
{
    int i, j, li, ri;
    for (j = 0; j < 4; j++)
    {
        li = 3, ri = j;
        for (i = 2; i >= 0; i--)
        {
            if (board[i][j] != 0)
            {
                if (board[i + 1][j] == 0 || board[i + 1][j] == board[i][j])
                {
                    if (board[li][ri] == board[i][j])
                    {
                        board[li][ri] *= 2;
                        board[i][j] = 0;
                    }
                    else
                    {
                        if (board[li][ri] == 0)
                        {
                            board[li][ri] = board[i][j];
                            board[i][j] = 0;
                        }
                        else
                        {
                            board[--li][ri] = board[i][j];
                            board[i][j] = 0;
                        }
                    }
                }
                else
                    li--;
            }
        }
    }
}

void Game2048 ::leftmove()
{
    int i, j, li, ri;
    for (i = 0; i < 4; i++)
    {
        li = i, ri = 0;
        for (j = 1; j < 4; j++)
        {
            if (board[i][j] != 0)
            {
                if (board[i][j - 1] == 0 || board[i][j - 1] == board[i][j])
                {
                    if (board[li][ri] == board[i][j])
                    {
                        board[li][ri] *= 2;
                        board[i][j] = 0;
                    }
                    else
                    {
                        if (board[li][ri] == 0)
                        {
                            board[li][ri] = board[i][j];
                            board[i][j] = 0;
                        }
                        else
                        {
                            board[li][++ri] = board[i][j];
                            board[i][j] = 0;
                        }
                    }
                }
                else
                    ri++;
            }
        }
    }
}

void Game2048 ::rightmove()
{
    int i, j, li, ri;
    for (i = 0; i < 4; i++)
    {
        li = i, ri = 3;
        for (j = 2; j >= 0; j--)
        {
            if (board[i][j] != 0)
            {
                if (board[i][j + 1] == 0 || board[i][j + 1] == board[i][j])
                {
                    if (board[li][ri] == board[i][j])
                    {
                        board[li][ri] *= 2;
                        board[i][j] = 0;
                    }
                    else
                    {
                        if (board[li][ri] == 0)
                        {
                            board[li][ri] = board[i][j];
                            board[i][j] = 0;
                        }
                        else
                        {
                            board[li][--ri] = board[i][j];
                            board[i][j] = 0;
                        }
                    }
                }
                else
                    ri--;
            }
        }
    }
}

int Game2048 ::IsOver(int temp[4][4])
{
    int fl = 1, i, j;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            if (temp[i][j] != board[i][j])
            {
                fl = 0;
                break;
            }
    return fl;
}

int Game2048 ::Check()
{
    int fl = 0, gl = 0, i, j;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            if (board[i][j] == 0)
            {
                fl = 1;
                break;
            }

    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            if (board[i + 1][j] == board[i][j] || board[i][j + 1] == board[i][j])
            {
                gl = 1;
                break;
            }
    if (fl || gl)
        return 1;
    else
        return 0;
}

void Game2048 ::AddBlock()
{
    int li, ri;
    srand(time(0));
    while (1)
    {
        li = rand() % 4;
        ri = rand() % 4;
        if (board[li][ri] == 0)
        {
            board[li][ri] = pow(2, li % 2 + 1);
            break;
        }
    }
}

void Game2048 ::Display()
{
    cout << "\n\t\tPress ESC to quit the game";
    cout << "\n\n\n\n";
    int i, j;
    cout << "\t---------------------------------" << endl;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            cout << "\t| ";
            if (board[i][j] != 0)
                cout << board[i][j];
        }
        cout << "\t|" << endl
             << "\t---------------------------------" << endl;
    }
}

class Board
{
protected:
    vector<vector<int>> board;
    int size;
    virtual void initialize() = 0;
    virtual void shuffle() = 0;
    virtual void display() = 0;
    virtual bool isSolved() = 0;
    virtual bool move(char direction) = 0;

public:
    Board(int n)
    {
        size = n;
        board.resize(size, vector<int>(size));
    }
};

class Puzzle15 : public Board
{
public:
    int emptyRow, emptyCol;
    Puzzle15(int n) : Board(n) {}
    void initialize()
    {
        int count = 1;
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                board[i][j] = count++;
            }
        }
        emptyRow = size - 1;
        emptyCol = size - 1;
        board[emptyRow][emptyCol] = 0;
    }
    void shuffle()
    {
        vector<int> numbers;
        for (int i = 0; i < size * size; i++)
            numbers.push_back(i);
        random_shuffle(numbers.begin(), numbers.end());
        int index = 0;
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                board[i][j] = numbers[index++];
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                if (board[i][j] == 0)
                {
                    emptyRow = i;
                    emptyCol = j;
                    break;
                }
    }
    void display()
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (board[i][j] != 0)
                    cout << board[i][j];
                cout << "\t";
            }
            cout << endl;
        }
    }
    bool isSolved()
    {
        int count = 1;
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
                if (board[i][j] != count % (size * size))
                    return false;
            count++;
        }
        return true;
    }
    bool move(char direction)
    {
        int n1, n2;
        int newRow = emptyRow;
        int newCol = emptyCol;
        if (direction == 80 && emptyRow > 0)
            newRow--;
        else if (direction == 72 && emptyRow < size - 1)
            newRow++;
        else if (direction == 77 && emptyCol > 0)
            newCol--;
        else if (direction == 75 && emptyCol < size - 1)
            newCol++;
        else if (direction == 27)
            return true;
        else
            return false;
        swap(board[emptyRow][emptyCol], board[newRow][newCol]);
        emptyRow = newRow;
        emptyCol = newCol;
        return false;
    }
};

class matrixt
{
public:
    char matrixttt[3][3];
    matrixt()
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                matrixttt[i][j] = ' ';
            }
        }
    }

    void display()
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                cout << matrixttt[i][j];
                if (j < 2)
                {
                    cout << '|';
                }
            }
            cout << endl;
            if (i < 2)
            {
                cout << "-----" << endl;
            }
        }
    }

    bool isFull()
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (matrixttt[i][j] == ' ')
                {
                    return false;
                }
            }
        }
        return true;
    }

    bool isWin(char player)
    {
        for (int i = 0; i < 3; i++)
        {
            if (matrixttt[i][0] == player && matrixttt[i][1] == player && matrixttt[i][2] == player)
            {
                return true; // Row win
            }
            if (matrixttt[0][i] == player && matrixttt[1][i] == player && matrixttt[2][i] == player)
            {
                return true; // Column win
            }
        }
        if (matrixttt[0][0] == player && matrixttt[1][1] == player && matrixttt[2][2] == player)
        {
            return true; // Diagonal win
        }
        if (matrixttt[0][2] == player && matrixttt[1][1] == player && matrixttt[2][0] == player)
        {
            return true; // Diagonal win
        }
        return false;
    }

    void placeMarker(int row, int col, char marker)
    {
        if (row >= 0 && row < 3 && col >= 0 && col < 3 && matrixttt[row][col] == ' ')
        {
            matrixttt[row][col] = marker;
        }
    }
};

class Game : public matrixt
{
public:
    void play()
    {
        char currentPlayer = 'X';

        while (true)
        {
            system("cls"); // Clear the console (Linux/macOS)
            // system("cls");  // Clear the console (Windows)
            display();
            cout << "Player " << currentPlayer << ", enter row and column (e.g., 1 2): ";

            int row, col;
            cin >> row >> col;

            if (row < 1 || row > 3 || col < 1 || col > 3)
            {
                cout << "Invalid input. Try again." << endl;
                continue;
            }

            row--;
            col--;

            if (matrixttt[row][col] == ' ')
            {
                placeMarker(row, col, currentPlayer);

                if (isWin(currentPlayer))
                {
                    system("clear");
                    // system("cls");
                    display();
                    cout << "Player " << currentPlayer << " wins!" << endl;
                    break;
                }

                if (isFull())
                {
                    system("clear");
                    // system("cls");
                    display();
                    cout << "It's a draw!" << endl;
                    break;
                }

                currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
            }
            else
            {
                cout << "That spot is already taken. Try again." << endl;
            }
        }
    }
};

class console
{
public:
    void game1();
    void game2();
    void game3();
    void game4();
};

void console::game1()
{
    system("cls");
    cout << "\n\n\n\n\t\t\tSNAKE GAME\n\n\n\t\tPress any key to continue";
    getch();
    system("cls");
    SnakeGame game;
    game.Setup();
    while (!gameOver)
    {
        game.Input();
        game.Logic();
        game.Setup();
        Sleep(100); // Sleep for 100 milliseconds
    }
    cout << "\n\nGAME OVER!!\n\n\n";
    system("PAUSE");
}

void console::game2()
{
    system("cls");
    cout << "\n\n\n\n\t\t\t2048 GAME\n\n\n\t\tPress any key to continue";
    getch();
    system("cls");
    Game2048 G;
    int ch, i, j;
    int temp[4][4];
    while (1)
    {
        for (i = 0; i < 4; i++)
            for (j = 0; j < 4; j++)
                temp[i][j] = G.board[i][j];
        ch = getch();
        system("cls");
        if (ch == 72)
            G.upmove();
        if (ch == 80)
            G.downmove();
        if (ch == 75)
            G.leftmove();
        if (ch == 77)
            G.rightmove();
        if (ch == 27)
            break;

        if (!G.IsOver(temp))
            G.AddBlock();
        G.Display();

        if (!G.Check())
        {
            cout << "\n\n\t\t\tGAME OVER!!\n\n\n";
            break;
        }
    }
}

void console::game3()
{
    system("cls");
    int ch = 1;
    char d;
    while (1)
    {
        system("cls");
        system("color 9f");
        cout << "press ESC to Exit\n";
        cout << "\nDifficulty level\n";
        cout << "\nnoob\t";
        if (ch % 5 == 1)
            cout << "<";
        cout << "\nEasy\t";
        if (ch % 5 == 2)
            cout << "<";
        cout << "\nMedium\t";
        if (ch % 5 == 3)
            cout << "<";
        cout << "\nHard\t";
        if (ch % 5 == 4)
            cout << "<";
        cout << "\nInsane\t";
        if (ch % 5 == 0)
            cout << "<";
        d = _getch();
        Beep(3000, 50);
        if (d == 72)
            ch--;
        if (d == 80)
            ch++;
        if (d == 13)
            break;
        if (d == 10)
            return;
    }
    if (ch % 5 != 0)
        ch = ch % 5;
    else
        ch = 5;
    Puzzle15 Board(ch + 1);
    Board.initialize();
    Board.shuffle();
    while (!Board.isSolved())
    {
        system("cls");
        cout << "Press ESC to exit\n"
             << endl;
        Board.display();
        char move = _getch();
        if (Board.move(move))
            break;
    }
    cout << "Congratulations! You solved the Board." << endl;
}

void console::game4()
{
    Game game;
    game.play();
}

int menu()
{
    int ch = 1;
    char d;
    while (1)
    {
        system("cls");
        system("color 9f");
        cout << "\n\t\t\t\t------------------* Welcome To Gaming console * ------------------\n\n";
        cout << "press ESC to Exit\n";
        cout << "\nSnake Game\t";
        if (ch % 4 == 1)
            cout << "<";
        cout << "\n\n2048\t\t";
        if (ch % 4 == 2)
            cout << "<";
        cout << "\n\nPuzzle15\t";
        if (ch % 4 == 3)
            cout << "<";
        cout << "\n\nTic-Tac-Toe\t";
        if (ch % 4 == 0)
            cout << "<";
        cout << "\n";
        Beep(3000, 50);
        d = _getch();
        if (d == 72)
            ch--;
        if (d == 80)
            ch++;
        if (d == 13)
            break;
        if (d == 27)
            return -1;
    }
    if (ch % 4 != 0)
        return (ch % 4);
    else
        return 4;
}

int main()
{
    system("color 9f");
    int ch = 1;
    console c;
    while (ch)
    {
        system("cls");
        ch = menu();
        if (ch == -1)
            break;
        cout << "Start time: ";
        switch (ch)
        {
        case 1:
            c.game1();
            break;
        case 2:
            c.game2();
            system("color 9f");
            break;
        case 3:
            c.game3();
            break;
        case 4:
            c.game4();
            break;
        }
    }
    return 0;
}

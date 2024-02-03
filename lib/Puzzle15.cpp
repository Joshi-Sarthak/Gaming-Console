#include "Puzzle15.h"
#include <vector>
#include <algorithm>
#include <iostream>

Puzzle15::Puzzle15(int n)
{
    size = n;
    board.resize(size, std::vector<int>(size));
}

void Puzzle15::initialize()
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

void Puzzle15::shuffle()
{
    std::vector<int> numbers;
    for (int i = 0; i < size * size; i++)
        numbers.push_back(i);
    std::random_shuffle(numbers.begin(), numbers.end());
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

void Puzzle15::display()
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (board[i][j] != 0)
                std::cout << board[i][j];
            std::cout << "\t";
        }
        std::cout << std::endl;
    }
}

bool Puzzle15::isSolved()
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

bool Puzzle15::move(char direction)
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
    std::swap(board[emptyRow][emptyCol], board[newRow][newCol]);
    emptyRow = newRow;
    emptyCol = newCol;
    return false;
}
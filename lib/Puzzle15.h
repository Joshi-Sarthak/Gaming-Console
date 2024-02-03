#ifndef PUZZLE15_H
#define PUZZLE15_H

#include <bits/stdc++.h>

#pragma once

class Puzzle15
{
    std::vector< std::vector<int> > board;
    int size;
public:
    int emptyRow, emptyCol;
    Puzzle15(int);
    void initialize();
    void shuffle();
    void display();
    bool isSolved();
    bool move(char);
};

#endif
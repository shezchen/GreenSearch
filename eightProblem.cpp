#include <iostream>

#include "header.h"
#include  <random>

eightProblem::eightProblem()
{
    std::vector<int> temp = {1, 2, 3, 4, 5, 6, 7, 8, 0};
    std::shuffle(temp.begin(), temp.end(), std::mt19937(std::random_device()()));
    for (int i = 0; i < 3; i++)
    {
        std::vector<int> row;
        for (int j = 0; j < 3; j++)
        {
            row.push_back(temp[i * 3 + j]);
        }
        currentBoard.push_back(row);
    }    
}

void eightProblem::printCurrentBoard()
{
    std::cout<<"--Current Board:"<<std::endl;
    std::for_each(currentBoard.begin(), currentBoard.end(), [](std::vector<int> row)
    {
        std::for_each(row.begin(), row.end(), [](int num)
        {
            std::cout<<num<<" ";
        });
        std::cout<<std::endl;
    });
}

int eightProblem::getManhattanDistance()
{
    int distance = 0;
    for (int i = 0; i < 3; i++)
    {
        //(i,j)
        for (int j = 0; j < 3; j++)
        {
            if(currentBoard[i][j] == goalBoard[i][j])
                continue;
            else
            {
                //得到目标行列
                std::tuple<int,int> target{currentBoard[i][j]/3, currentBoard[i][j]%3};
                distance += std::abs(i-std::get<0>(target))+std::abs(j-std::get<1>(target));
            }
        }
    }
    return distance;
}

void eightProblem::move(int value)
{
    //value = -3,-1,+1,+3
    int row, col;
    auto it = std::ranges::find_if(currentBoard,[value,&col](std::vector<int> row)
    {
        col = std::ranges::find(row, 0)-row.begin();
       return  std::ranges::find(row, 0)!=row.end();
    });
    row = it-currentBoard.begin();

    switch (value)
    {
    case -3:
        std::swap(currentBoard[row][col], currentBoard[row-1][col]);
        break;
    case -1:
        std::swap(currentBoard[row][col], currentBoard[row][col-1]);
        break;
    case 1:
        std::swap(currentBoard[row][col], currentBoard[row][col+1]);
        break;
    case 3:
        std::swap(currentBoard[row][col], currentBoard[row+1][col]);
        break;
    }
}

std::vector<int> eightProblem::getAvailableMoves()
{
    std::vector<int> moves;
    int row, col;
    auto it = std::ranges::find_if(currentBoard,[&col](std::vector<int> row)
    {
        col = std::ranges::find(row, 0)-row.begin();
       return  std::ranges::find(row, 0)!=row.end();
    });
    row = it-currentBoard.begin();
    if(row-1>=0)
        moves.push_back(-3);
    if(col-1>=0)
        moves.push_back(-1);
    if(col+1<=2)
        moves.push_back(1);
    if(row+1<=2)
        moves.push_back(3);
    return moves;
}

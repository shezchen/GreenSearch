//
// Created by 熬夜拧螺丝 on 25-3-17.
//

#ifndef HEADER_H
#define HEADER_H
#include <vector>

struct eightProblem
{
    bool ifFinished = false;
    
    std::vector<std::vector<int>> currentBoard;

    std::vector<std::vector<int>> goalBoard = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
    
    eightProblem();

    void print();

    int getManhattanDistance();

    void move(int index);

    auto getAvailableMoves();
};

struct Astarsearch
{
    Astarsearch();
    
    struct Node
    {
        Node();
        Node& previousNode;
        Node& nextNode;

        std::vector<int> moveHistory;

        int cost = 0;

        void getCost();
        
    };

    Node firstNode;

    bool ifFind;
};
struct AstarsearchOnEightProblem
{
    std::vector<eightProblem> questionList;
    int currentProblemIndex = 0;
    AstarsearchOnEightProblem(int);
    int totalCost = 0;
    Astarsearch astarsearch;
};







#endif //HEADER_H

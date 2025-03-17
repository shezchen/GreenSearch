#include <vector>
#include "header.h"

AstarSearchOnEightProblem::AstarSearchOnEightProblem(int num)
{
    for(int i=0;i<num;i++)
    {
        questionList.emplace_back();
    }
}

Astarsearch::Astarsearch(eightProblem& problem)
{
    searchingNode = std::make_shared<Node>();  // create object as shared_ptr

    viewedList.push_back(problem);
    
    searchingNode->previousNode = nullptr;
    searchingNode->moveHistory = std::vector<int>();
    searchingNode->currentProblem = problem;
    currentNodeList.push_back(searchingNode);    // already a shared_ptr
    searchingNode->historyCost = 0;
    searchingNode->evaluateCost = problem.getManhattanDistance();
    searchingNode->totalCost = searchingNode->historyCost + searchingNode->evaluateCost;
    ifFind = false;
    answerFinalNode = nullptr;
}

std::shared_ptr<Astarsearch::Node> Astarsearch::Node::search(Astarsearch& search)
{
    //搜索当前节点的所有子节点,如果已经找到解，则不再扩展，直接返回最终顶点的指针
    auto availableMoves = currentProblem.getAvailableMoves();
    for(auto move:availableMoves)
    {
        auto newProblem = currentProblem;
        newProblem.move(move);
        
        auto newNode = std::make_shared<Node>();
        newNode->previousNode = shared_from_this();
        
        newNode->moveHistory = moveHistory;
        newNode->moveHistory.push_back(move);

        newNode->currentProblem = newProblem;
        
        newNode->historyCost = historyCost + 1;
        newNode->evaluateCost = newProblem.getManhattanDistance();
        newNode->totalCost = newNode->historyCost + newNode->evaluateCost;

        search.ifFind = newProblem.currentBoard == newProblem.goalBoard;

        if(search.ifFind)
            return newNode;

        //判断当前状态是否已经访问过
        if(std::ranges::find_if(search.viewedList,[newProblem](const eightProblem& problem)
        {
            return problem.currentBoard==newProblem.currentBoard;
        })!=search.viewedList.end())
            continue;//如果已经访问过，则不再扩展
        search.currentNodeList.push_back(newNode);
        search.viewedList.push_back(newProblem);
    }
    return nullptr;
}
std::shared_ptr<Astarsearch::Node> Astarsearch::determineBestNode()
{
    //确定当前节点列表中总代价最小的节点
    auto bestNode = std::min_element(currentNodeList.begin(), currentNodeList.end(),
        [](const std::shared_ptr<Node>& a, const std::shared_ptr<Node>& b)
        {
            return a->totalCost < b->totalCost;
        });
    
    return *bestNode;
}






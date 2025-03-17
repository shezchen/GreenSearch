#ifndef HEADER_H
#define HEADER_H
#include <vector>

struct eightProblem
{
    
    std::vector<std::vector<int>> currentBoard;

    std::vector<std::vector<int>> goalBoard = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
    
    eightProblem();

    void printCurrentBoard();

    int getManhattanDistance();

    void move(int index);

    std::vector<int> getAvailableMoves();
};

struct Astarsearch 
{
    
    //依据当前问题的可达状态，进行A*搜索
    explicit Astarsearch(eightProblem&);
    
    struct Node :public std::enable_shared_from_this<Node>
    {
        Node()=default;
        std::shared_ptr<Node> previousNode;
        std::vector<std::shared_ptr<Node>> nextNodeVector;

        eightProblem currentProblem;

        std::vector<int> moveHistory;

        int historyCost = 0;//历史代价

        int evaluateCost = 0;//启发式评估代价
        
        int totalCost = 0;//总代价

        std::shared_ptr<Node> search(Astarsearch&);//由目标结点开始，搜索当前节点的所有可行子节点，进行扩展，加入currentNodeList
        
    };

    std::vector<std::shared_ptr<Node>> currentNodeList;//当前结点列表

    std::vector<eightProblem> viewedList;//访问过的状态

    std::shared_ptr<Node> determineBestNode();//确定当前节点列表中总代价最小的节点

    std::shared_ptr<Node> searchingNode;//此次搜索的节点

    std::shared_ptr<Node> answerFinalNode;//最终答案节点

    bool ifFind = false;//是否找到解
};


struct AstarSearchOnEightProblem
{
    //八数码问题搜索，问题集
    std::vector<eightProblem> questionList;
    
    int currentProblemIndex = 0;//当前问题索引
    
    AstarSearchOnEightProblem(int);//构造函数
    
    int totalCost = 0;//总代价（包含所有的问题代价）
    
};







#endif //HEADER_H

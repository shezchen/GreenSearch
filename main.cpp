#include <iostream>

#include "header.h"

int main()
{
    AstarSearchOnEightProblem problemArray(10);

    int i=0;
    float totalTime = 0;
    int totalSolved = 0;
    for(auto& problem :problemArray.questionList)
    {
        i++;
        Astarsearch searchInstance(problem);
        int computeCount = 0;
        bool solvable = true;
        auto startTime = std::chrono::high_resolution_clock::now();
        while(!searchInstance.ifFind)
        {
           
            computeCount++;
            if(computeCount > 10000)
            {
                solvable = false;
                break;
            }
            auto ptr = searchInstance.searchingNode->search(searchInstance);//结点开始扩展
            if(ptr!=nullptr)
            {
                searchInstance.answerFinalNode = ptr;
                searchInstance.ifFind = true;
                break;
            }

            auto bestNode = searchInstance.determineBestNode();
            
            searchInstance.searchingNode = bestNode;

            std::erase_if(searchInstance.currentNodeList,
                [bestNode](const std::shared_ptr<Astarsearch::Node>& node)
                {
                    return bestNode==node;
                });
        }
        if(solvable)
        {
            //输出路径
            std::cout<<"------"<<"Problem "<<i<<"------"<<std::endl;
            problemArray.questionList[i-1].printCurrentBoard();
            // End time measurement
            auto endTime = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
            float computeTime = duration / 1000.0f; // Convert to seconds
            std::cout<<"This problem is solved in "<<computeTime<<"s."<<std::endl;
            totalSolved++;
            totalTime += computeTime;
            for (auto errlist : searchInstance.answerFinalNode->moveHistory)
            {
                std::cout<< ((errlist==-3)?"up":(errlist==-1)?"left":(errlist==1)?"right":"down") <<"  ";
            }
            std::cout<<std::endl<<"------------"<<std::endl;
        }else
        {
            std::cout<<"------"<<"Problem "<<i<<"------"<<std::endl;
            std::cout<<"This problem is not solvable.";
            std::cout<<std::endl<<"------------"<<std::endl;
        }
        
    }
    std::cout<<"Total "<<problemArray.questionList.size()<<" problems, "<<totalSolved<<" problems are solved,"<<"average time is "<<totalTime/(float)totalSolved<<"s."<<std::endl;
}

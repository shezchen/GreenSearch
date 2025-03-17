#pragma once
#include <vector>
#include "header.h"

AstarsearchOnEightProblem::AstarsearchOnEightProblem(int num)
{
    for(int i=0;i<num;i++)
    {
        questionList.emplace_back();
    }
}
Astarsearch::Node::Node()
{
    previousNode = Node();
    nextNode = Node();
}
Astarsearch::Astarsearch()
{
    firstNode=Node();
}



#ifndef TKOM_INTERPRETER_ASTNODEPRINTER_H
#define TKOM_INTERPRETER_ASTNODEPRINTER_H

#include <iostream>
#include "ASTNode.h"

void printASTNode(ASTNode::ptr node, int level = 0){
    if(node != nullptr){
        if(level > 0)
        {
            for(int i = 0; i < level-1; i++){
                std::cout << "    ";
            }
            std::cout << "|---";
        }
        std::cout << node->representation() << std::endl;
        for(auto& child: node->getChildren()){
            printASTNode(child, level + 1);
        }
    }

    return;
}

#endif //TKOM_INTERPRETER_ASTNODEPRINTER_H

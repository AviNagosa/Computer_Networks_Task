#pragma once
#include <iostream>
#include <string.h>


namespace prefix_table
{
    struct Node
    {
        char id, data;
        Node* one;
        Node* zero;

        //empty constructor
        Node(){ one = zero = NULL;}
    };
    
    class Tree
    {
        public:
        Node* head;
        Node* pointer;
         
        Tree();
        ~Tree();
        
        int add(std::string&,char&,int&);
        char find(std::string);
        int remove(std::string,char&,int&);
        void destroyTree(Node*);
    };
}
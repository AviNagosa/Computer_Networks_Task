#pragma once
#include <iostream>
#include <string.h>

namespace prefix_table_opt
{
    struct Node
    {
        int mask;
        char id = ' ', data = ' ';
        Node* prev;
        Node* one;
        Node* zero;

        //empty constructor
        Node(){ one = zero = prev = NULL;}
    };
    
    class Tree
    {
        public:
        Node* head;
        Node* pointer;
         
        Tree();
        ~Tree();
        void destroyTree(Node*);
        
        void add(std::string&,char&,int&);
        char find(std::string);
        int remove(std::string,char&,int&);
        void optimize(Node*);
        void optimize(Node*,Node*);
    };
}
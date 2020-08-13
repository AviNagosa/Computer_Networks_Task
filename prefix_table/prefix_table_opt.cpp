#include "prefix_table_opt.hpp"
#include <stdexcept>

namespace prefix_table_opt
{
    //constructor
    Tree::Tree(){head = new Node();}

    //destractor
    Tree::~Tree(){destroyTree(head);} 

    //destractor for every Node
    void Tree::destroyTree(Node* node)
    {
        if (node!=NULL)
        {
            if(node->one!=NULL)
            {
                destroyTree(node->one);
            }
            if(node->zero!=NULL)
            {
                destroyTree(node->zero);
            }
            delete node;
        }
    }



    void Tree::add(std::string& prefix,char& id,int& per)
    {
	    Node *curr = head;
        curr->prev = head;

	    for(int i = 0; i < per; i++)
	    {
		    if(prefix[i]== '1')
		    {
			    if(curr->one) curr = curr->one;
			    else
			    {
				    curr->one = new Node();
                    curr->one->prev = curr;
				    curr = curr->one;
				    curr->data = prefix[i];
			    }
		    }
		    else
		    {
			    if(curr->zero) curr = curr->zero;
			    else
			    {
				    curr->zero = new Node();
                    curr->zero->prev = curr;
				    curr = curr->zero;
				    curr->data = prefix[i];
			    }
		    }
            curr->id = id;
            curr->mask = per;
	    }
        optimize(curr);
    }


    void Tree::optimize(Node *node)
    {
        Node* root = head;
        if(root->one != NULL) optimize(root->one,node);
        if(root->zero != NULL) optimize(root->zero,node);
    }

    void Tree::optimize(Node *root,Node* node)
    {
        if(root == NULL) return;
        if((root->prev != node->prev) && (root->id == node->id))
        {
            if((root->mask) > (node->mask))
            {
                Node* temp = root->prev;
                temp->id = root->id;
                temp->mask = root->mask-1;

                if(root->data == '1') temp->one = NULL;
                else temp->zero = NULL;
                delete root;

                optimize(temp,node);
            }
            else if((root->mask) < (node->mask))
            {
                Node* temp = node->prev;
                temp->id = node->id;
                temp->mask = node->mask-1;
                
                if(node->data == '1') temp->one = NULL;
                else temp->zero = NULL;
                delete node;
                
                optimize(root,temp);
            }
        }
        else if((root->prev == node->prev) && (root->id == node->id) && (root != node))
        {
            Node* temp = root->prev;
            temp->id = root->id;
            temp->mask = root->mask-1;

            delete node;
            delete root;

            temp->one = NULL;
            temp->zero = NULL;
        }
        else
        {
            optimize(root->zero,node);
            optimize(root->one,node);
        }
    }
        


    char Tree::find(std::string ip)
    {
	    Node* curr = head;
        char longetId;
	    for(int i = 0; i < ip.size(); i++)
	    {
		    if(ip[i]== '1')
		    {
			    if(curr->one) curr = curr->one;
			    else break;
		    }
		    else
		    {
			    if(curr->zero) curr = curr->zero;
			    else break;
		    }
            if(curr->id != ' ') longetId = curr->id;
	    }
	    return longetId;
    }



    //get Node action and remove his subtree including him
    int Tree::remove(std::string s,char& id, int& per)
    {
       Node* curr = head;
       int j = per;
       for(int i = 0; i < per; i++)
       {
           if(s[i] == '1') curr = curr->one;
           else if(s[i] == '0') curr = curr->zero;
       }
       Node* temp;
       char val;
       while(j)
       {
           if(curr->data == '1') val = '1';
           else val = '0';

           temp = curr->prev;

           if((val=='1') && (temp->data == 1) && (temp->zero!=NULL))
           {
               delete curr;
               temp->one = NULL;
               break;
           }
           else if((val=='0') && (temp->data == 0) && (temp->zero!=NULL))
           {
                delete curr;
                temp->zero = NULL;
                break;
           }
           else
           {
                curr = temp;
                j--;
           }

       }
       return per;
    }
}
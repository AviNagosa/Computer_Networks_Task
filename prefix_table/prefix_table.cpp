#include "prefix_table.hpp"
#include <stdexcept>

namespace prefix_table
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



    int Tree::add(std::string& prefix,char& id,int& per)
    {
        if(head == NULL) return 0;

	    Node* curr = head;
	    int depth = 0;
	    for(int i = 0; i < per; i++)
	    {
		    if(prefix[i]== '1')
		    {
			    if(curr->one) curr = curr->one;
			    else
			    {
				    curr->one = new Node();
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
				    curr = curr->zero;
				    curr->data = prefix[i];
			    }
		    }
            curr->id = id;
		    depth++;
	    }

	    return depth;
    }



    char Tree::find(std::string ip)
    {
	    Node* curr = head;

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
	    }
	    return curr->id;
    }



    //get Node action and remove his subtree including him
    int Tree::remove(std::string s,char& id, int& per)
    {
       Node* curr = head;
       int depth = 0;
       for(int i = 0; i < per; i++)
       {
           if(s[i] == '1') curr = curr->one;
           else if(s[i] == '0') curr = curr->zero;
           depth++;
           if(curr->id == id) curr->id = ' ';
       }
       return depth;
    }


}
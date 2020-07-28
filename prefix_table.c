#include "prefix_table.h"

static Trie trie;

struct Trie* getNewTrieNode()
{
	struct Trie* node = (struct Trie*)malloc(sizeof(struct Trie));
	node->one = NULL;
	node->zero = NULL;
	return node;
}


void insert(struct Trie *head, char* prefix)
{
	//if(head == NULL) head = getNewTrieNode();

	struct Trie* curr = head;

	for(int i = 0; i < strlen(prefix); i++)
	{
		if(prefix[i]== '1')
		{
			if(curr->one) curr = curr->one;
			else
			{
				curr->one = getNewTrieNode();
				curr = curr->one;
				curr->data = prefix[i];
			}
		}
		else
		{
			if(curr->zero) curr = curr->zero;
			else
			{
				curr->zero = getNewTrieNode();
				curr = curr->zero;
				curr->data = prefix[i];
			}
			
		}
	}
}


void print(Trie *root, int space)
{
    if (root == NULL) return;
    space += COUNT; 
    print(root->zero, space); 
    printf("\n");
    for (int i = COUNT; i < space; i++) printf(" ");
    printf("%c\n", root->data); 
    print(root->one, space); 
}


int* ConvertTo8Bits(int x)
{
	int* ret = (int*) malloc(BYTE*sizeof(int));
	int i=7;
	while(x) {
	    if (x&1) ret[i]=1;
	    else ret[i]=0;
	    i--;
	    x>>=1;  
	}
  	return ret;
}


int* ConvertToBinary(char* s)
{
	int n;
	sscanf(s,"%d",&n);
	return ConvertTo8Bits(n);
}

void ConvertToChar(char* s, int* arr)
{
	char s1[BYTE] = "";
	for(int i = 0; i < BYTE; i++)
	{
	    if(arr[i] == 1) s1[i] = '1';
	    else s1[i] = '0';
	}
	strcat(s,s1);
}



int search(struct Trie* head, char* str)
{
	if (head == NULL) return 0;
	struct Trie* curr = head;
	while (*str)
	{
		curr = curr->one;
		if (curr == NULL) return 0;
		str++;
	}
	return curr->data;
}


/*
int delete(struct Trie **curr, char* str)
{
	if (*curr == NULL) return 0;
	if (*str)
	{
		if(*curr != NULL && (*curr)->next[*str - 'a'] != NULL &&
			deletion(&((*curr)->next[*str - 'a']), str + 1) &&
			(*curr)->data == 0)
		{
			if (!haveChildren(*curr))
			{
				free(*curr);
				(*curr) = NULL;
				return 1;
			}
			else {
				return 0;
			}
		}
	}
	if (*str == '\0' && (*curr)->data)
	{
		if (!haveChildren(*curr))
		{
			free(*curr); 
			(*curr) = NULL;
			return 1; 
		}
		else
		{
			(*curr)->data = 0;
			return 0;	   
		}
	}
	return 0;
}

int haveChildren(struct Trie* curr)
{
	for (int i = 0; i < CHAR_SIZE; i++)
		//if (curr->next[i])
			return 1;	// child found

	return 0;
}
*/
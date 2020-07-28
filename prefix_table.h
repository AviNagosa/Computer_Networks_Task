#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define SIZE 25
#define CHAR_SIZE 26
#define BYTE 8
#define COUNT 1

typedef struct Trie
{
	char data;
	struct Trie *one, *zero;
}Trie;

struct Trie* getNewTrieNode();
void insert(struct Trie *head, char* str);
int search(struct Trie* head, char* str);
//int haveChildren(struct Trie* curr);
//int delete(struct Trie **curr, char* str);

int* ConvertToBinary(char* s);
int* ConvertTo8Bits(int x);
void ConvertToChar(char* s, int* a);

void print(Trie *root, int space);

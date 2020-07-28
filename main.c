#include "prefix_table.h"

int storeData(FILE* f, char fStorage[SIZE][SIZE], char action[SIZE][5], char id[SIZE][5])
{ 
	char delim[] = " ", line[SIZE], *ptr;
	int i = 0;
	while(fgets(line, sizeof(line), f)){
		ptr = strtok(line, delim);
		strcpy(action[i],ptr); 
		ptr = strtok(NULL, delim);
		strcpy(fStorage[i],ptr);
		ptr = strtok(NULL, delim);
		if(ptr != NULL){
			strcpy(id[i],ptr);
			ptr = strtok(NULL, delim);
		}else strcpy(id[i],"");
		i++; 
	}
	return i;
}


int main()
{
	FILE* f;
	char fStorage[SIZE][SIZE], action[SIZE][5],id[SIZE][5];
	char byteChar[32] = "";
	int count, *byteInteger, row;
	struct Trie* head;

    f = fopen("input2.txt", "r");
    if(f == NULL)
    {
		printf("Failed opening the file!! \n");
		return 0;
    }

	row = storeData(f, fStorage, action, id); 
	head = getNewTrieNode();
	
 	for(int i = 0; i < row ; i++)
	{
		printf("%s\n",id[i]);
		char temp[5] = "";
		count = 0;
		if(strcmp(action[i],"ADD") == 0)
		{
			for(int j = 0; j < strlen(fStorage[i]); j++)
			{
				if(fStorage[i][j] == '/') break;
				if(fStorage[i][j] == '.')
				{
					byteInteger = ConvertToBinary(temp);
					ConvertToChar(byteChar,byteInteger);
					count = 0;
					free(byteInteger);
				}
				else 
				{
					temp[count] = fStorage[i][j];
					count++;
				}
			}
			byteInteger = ConvertToBinary(temp);
			ConvertToChar(byteChar,byteInteger);
			free(byteInteger);
			insert(head,byteChar);
		}

		else if(strcmp(action[i],"REMOVE") == 0)
		{
			printf("%s\n",action[i]);
		}
		else if(strcmp(action[i],"FIND") == 0)
		{
			printf("%s\n",action[i]);
		}
		else printf("invalid action !! \n");
	}
    print(head,0);
    return 0;
}



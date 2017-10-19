// C implementation of search and insert operations
// on Trie
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])

// Alphabet size (# of symbols)
#define ALPHABET_SIZE (26)

// Converts key current character into index
// use only 'a' through 'z' and lower case
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

// trie node

typedef struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];
    // isEndOfWord is true if the node represents
    // end of a word
    bool isEndOfWord;
}TRIE;

typedef struct elem{
	char letter;
	int isTerr;//is -1 and 1 for the resp. players 0 for unnoccupied territory  1 blue  -1 red
	bool isWord; //whether the element is part of some word or not
}ELEM;
// Returns new trie node (initialized to NULLs)
bool puts_words(char * string, ELEM *board, int pos);

struct TrieNode *getNode(void)
{
    struct TrieNode *pNode = NULL;

    pNode = (struct TrieNode *)malloc(sizeof(struct TrieNode));

    if (pNode)
    {
        int i;

        pNode->isEndOfWord = false;

        for (i = 0; i < ALPHABET_SIZE; i++)
            pNode->children[i] = NULL;
    }

    return pNode;
}

int LEN_OF_FILE=0;
// If not present, inserts key into trie
// If the key is prefix of trie node, just marks leaf node
void insert(struct TrieNode *root, const char *key)
{
    int level;
    int length = strlen(key);
    int index;

    struct TrieNode *pCrawl = root;

    for (level = 0; level < length; level++)
    {
        index = CHAR_TO_INDEX(key[level]);
        if(index>26 ||index<0)
            break;
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();

        pCrawl = pCrawl->children[index];
    }

    // mark last node as leaf
    pCrawl->isEndOfWord = true;
}

// Returns true if key presents in trie, else false
bool search(struct TrieNode *root, const char *key)
{
    int level;
    int length = strlen(key);
    int index;
    struct TrieNode *pCrawl = root;

    for (level = 0; level < length; level++)
    {
        index = CHAR_TO_INDEX(key[level]);
        if(index<0 || index>25)
            break;
        else if(!pCrawl->children[index])
            return false;

        pCrawl = pCrawl->children[index];
    }

    return (pCrawl != NULL && pCrawl->isEndOfWord);
}

void insert_all_nodes(struct TrieNode *root)
{
    char str[100];
    int count=0;
    FILE *fp=fopen("words.txt","r");
    while(fgets(str,30,fp)!=NULL)
    {
        insert(root,str);
        //puts(str);
        ++count;
    }
    printf("No of words=%d\n",count);
    fclose(fp);
}

char * addInEnd(char * str, char ch)
{
    int len;
    for(len=0;str[len]!='\0';len++);
    str[len]=ch;
    str[len+1]='\0';
    return str;
}

void removeFromEnd(char * s)
{
    int len;
    for(len=0;s[len]!='\0';++len);
    s[len-1]='\0';
}

void strperms(struct TrieNode * noode,int *hashish,char * wsf)
{
    if(noode->isEndOfWord)
    {    printf("%s\n",wsf);
		FILE *fp;

		fp = fopen("test.txt", "a");
		//fprintf(fp, "This is testing for fprintf...\n");
		if(wsf!="\0")
		{	fputs(wsf, fp);
			fputs("\n", fp);
			LEN_OF_FILE+=1;
		}
		fclose(fp);
	}

    for(int i=0;i<ALPHABET_SIZE;++i)
        if(hashish[i]!=0 && noode->children[i]!=NULL)
        {
            hashish[i]--;
            strperms(noode->children[i],hashish,addInEnd(wsf,i+'a'));
            hashish[i]++;
            removeFromEnd(wsf);
        }
    //for(int i=0;i<ALPHABET_SIZE;i++)printf("%d",hashish[i]);
}


void generate_words(struct TrieNode * root, char s[])
{
	LEN_OF_FILE = 0;
	
    int hashish[ALPHABET_SIZE];
    char wsf[100];
    strcpy(wsf,"\0");
    for(int i=0;i<ALPHABET_SIZE;i++)
        hashish[i]=0;
    for(int i=0;s[i]!='\0';i++)
        hashish[s[i]-'a']++;
//    for(int i=0;i<ALPHABET_SIZE;i++)
//        printf("%d,",hashish[i]);
    strperms(root,hashish,wsf);
}


// BOARD FUNCTIONS AND WORK


ELEM* init_board()
{
	ELEM * board = (ELEM *)malloc(sizeof(ELEM)*10*10);
	if(board){
	for(int i =0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			(board+(10*i+j)*sizeof(ELEM))->letter = '*';
			
			//printf("%c", (board+(10*i+j)*sizeof(ELEM))->letter);
			(board+(10*i+j)*sizeof(ELEM))->isWord = 0; // I dont know whether this is neccesary
			//if(i == 0)
				//(board+(10*i+j)*sizeof(ELEM))->isTerr = 1;
			//else if(i==9)
				//(board+(10*i+j)*sizeof(ELEM))->isTerr = -1;
			//else
				(board+(10*i+j)*sizeof(ELEM))->isTerr = 0;
		}
	}
	return board;
	}
	else{
		return NULL;
	}

}

char * possible_orient(char *string, ELEM *board, int pos,char *orient)
{
	int length = 0;
	int k =0;
	//printf("\t %s", orient);
	while(*(string+length*sizeof(char))!='\0')
	{
		length+=1;
	}
	printf(" %d\n",length);
	//printf("%s",string);
	int flag;
	
	if((pos - (pos%10))/10 + 1 >= length)
	{
		
		//enter NORTH
		printf("north");
		flag = 1;
		int j = 0;
		for(int i =pos;j<length  && i>0;i -= 10)
		{
			j+=1;
			if((board+(i)*sizeof(ELEM))->isWord==1){
				printf("prev");
				flag=0;
				break;}
		}
		if(flag==1)
		orient[k++]='N';
	}
	
	
	if(pos%10 + 1 >= length)
	{
		printf("west");
		//enter WEST
		flag = 1;
		int j =0;
		for(int i =pos;j<length && i>0 ; i -= 1)
		{
			j+=1;
			if((board+(i)*sizeof(ELEM))->isWord==1){
				printf("prev");
				flag=0;
				break;}
		}
		if(flag==1)
			orient[k++]='W';
	}
	
	if(10 - (pos%10) >=length)
	{
		
		printf("east");
		//enter EAST
		flag = 1;
		int j =0;
		for(int i =pos;j<length && i<99 ; i += 1)
		{
			j+=1;
			if((board+(i)*sizeof(ELEM))->isWord==1){
				printf("prev");
				flag=0;
				break;}
		}
		if(flag==1)
			orient[k++] = 'E';
	}
	
	if(10 - (pos - pos%10)/10 >=length)
	{
		
		printf("south");
		//enter SOUTH
		flag = 1;
		int j =0;
		for(int i =pos;j<length && i<99; i += 10)
		{
			j+=1;
			if((board+(i)*sizeof(ELEM))->isWord==1){
				printf("prev");
				flag=0;break;}
		}
		if(flag==1)
			orient[k++] = 'S';
		
		}
	
	//strcat(orient,'\0');
	orient[k++] = '\0';
	printf("\t %s", orient);
	return orient;
}

void place_it_in_board(char * string, ELEM *board)
{
	int length;
	int * arr;
	int success = 0;
	int random_pos = rand()%99+1; //random pos to start the word from
	int string_length=0;
	while(*(string+string_length*sizeof(char))!='\0')string_length+=1;
	int count = 0;
	do{
		count ++;
		random_pos = rand()%99+1;
		printf("%d", random_pos);
		char orienti[10];
		char *orient = possible_orient(string, board, random_pos,orienti);
		int length = 0;
		while(*(orient+length*sizeof(char))!='\0')length+=1;
		if(length==0){success=0;continue;}
		int random_dir = rand()%length;
		int j=0;
		printf("\n%d %c \n\n", random_dir,*(orient+random_dir*sizeof(char)) );
		switch(*(orient+random_dir*sizeof(char)))
		{
			case 'N':
			
					for(int i =random_pos;j<string_length;i -= 10,j+=1)
					{
						//printf("%s",string);
						(board+(i)*sizeof(ELEM))->letter = *(string + j*sizeof(char));
						(board + i*sizeof(ELEM))->isWord=1;
						
					}
					success=1;
					break;
			case 'S':
					for(int i =random_pos;j<string_length;i += 10,j+=1)
					{
						(board + i*sizeof(ELEM))->letter = *(string + j*sizeof(char));
						(board + i*sizeof(ELEM))->isWord=1;
					}
					success=1;
					break;
			case 'E':
					for(int i =random_pos; j<string_length;i+=1,j+=1)
					{
						(board + i*sizeof(ELEM))->letter = *(string + j*sizeof(char));
						(board + i*sizeof(ELEM))->isWord=1;
					}
					success=1;
					break;
			case 'W':
					for(int i =random_pos; j<string_length;i-= 1,j+=1)
					{
						(board + i*sizeof(ELEM))->letter = *(string + j*sizeof(char));
						(board + i*sizeof(ELEM))->isWord=1;
					}
					success=1;
					break;
			
		}
		
	}while(!success && count<10);
	//(board+(45)*sizeof(ELEM))->letter = 'E';

}

// Driver
int main()
{
//    int count=0;
	srand(time(NULL));
	
    struct TrieNode *root = getNode();
	
    insert_all_nodes(root);
	generate_words(root, "asia");



	
	ELEM *board = init_board();
	printf("%d", LEN_OF_FILE);
	if(board==NULL){
		//I dont know what to do
	}
	

	
	FILE *fp ;
	
	char line[50];
	
	for(int i =0;i<5;i++)
	{
		fp =fopen("test.txt","r+");
		
		int randnum = rand()%(LEN_OF_FILE-1)+2;
		int linenumber = 0;
		printf("%d", randnum);
		while(fgets(line, 60, fp))
		{
			//printf("\t loop");
			++linenumber;

			if(linenumber == randnum)
			{
				printf("%s", line);
				char word[10];
				int k = 0;
				for(int j = 1;line[j]!='\0';j++)
				{
				//printf("%c", line[j]);
				word[k++] = line[j-1];
				
				}
				strcat(word, "\0");
				place_it_in_board(word, board);
			}
		}
		fclose(fp);	
		printf("done");
	}
		
	printf("\n");
	for(int i = 0; i<10;i++){
		for(int j =0; j<10;j++){
			printf("%c ", (board + (10*i+j)*sizeof(ELEM))->letter);
		}
		printf("\n");
	}
	
	
	
//fill the board non words with random letters





//    char str[30],inp[30];
//    do
//    {
//        puts("\nEnter the word to be searched:");
//        gets(inp);
//        if(search(root,inp))
//            printf("%s is found\n",inp);
//        else
	
//            printf("Not found\n");
//    }while(1);
//    return 0;
     //generate_words(root,"teats");

}
//PRE ROUND
//MAKE the strperms functions write words into a filea at the end of word  ------------done
//Get 10 characters from the 2 players and then pass it to the generate_words function 
//read from the file and call place_it_in_board for random 6 words

//DURING THE ROUND
//Then we will play the game
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
        printf("%s\n",wsf);

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
			if(i == 0)
				(board+(10*i+j)*sizeof(ELEM))->isTerr = 1;
			else if(i==9)
				(board+(10*i+j)*sizeof(ELEM))->isTerr = -1;
			else
				(board+(10*i+j)*sizeof(ELEM))->isTerr = 0;
		}
	}
	return board;
	}
	else{
		return NULL;
	}
	
}
int * territory(ELEM *board,int play,int *length,int * arr)
{
	int n=0;
	for(int i =0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			if((board+(10*i+j)*sizeof(ELEM))->isTerr == play);
				*(arr+(10*i+j)*sizeof(int)) = 10*i+j;
		}
	}
	*length= n;
	return arr;
}

void place_it_in_board(char * string, ELEM *board,int play)
{
	int length;
	int * arr;
	arr = territory(board,play,&length,arr);
	for(int i =0; i<length;i++)
	{
		printf("%d ", *(arr+i*sizeof(int)));
	}
	int random = rand()%length;
	int random_pos = *(arr + sizeof(int)*random);
	//call the recursive function to put the words in the grid
	while(1){
		
	bool sucess = puts_words(string, board, random_pos);//run this and previous line again and again till true
	if (sucess = true)break;
	}
	
	
	
}

bool puts_words(char * string, ELEM *board, int pos)
{
	
	
	
	if(!(*(board+(pos)*sizeof(ELEM))).isWord)
	{
		(*(board+(pos)*sizeof(ELEM))).letter = *string;
		string+=1;
		if(*string=='\0')return true;
		int num ;
		//if(!*(board+(pos+10)*sizeof(ELEM))->isWord)
		while(1)
		{			
			num  = rand()%3;
			if(!(*(board+(pos+10)*sizeof(ELEM))).isWord && !(*(board+(pos+1)*sizeof(ELEM))).isWord && !(*(board+(pos-1)*sizeof(ELEM))).isWord){return false;}
			switch(num)
			{
				case 0: if(!(board+(pos+10)*sizeof(ELEM))->isWord) //up
				{pos+=10;	break;}
				case 1: if(!(board+(pos+1)*sizeof(ELEM))->isWord)//right
				{pos+=1;	break;}
				/*case 2: if(!(board+(pos-1)*sizeof(ELEM))->isWord)//left
				{pos-=1;	break;}*/
			
			}
		}
		bool sucess = puts_words(string, board, pos);
			return sucess;
	}
}


// Driver
int main()
{
//    int count=0;
	srand(time(NULL));
    struct TrieNode *root = getNode();
    insert_all_nodes(root);
    char s[100]="Stanky";
	ELEM* board = init_board();
	for(int i = 0; i<10; i++)
	{
		for(int j = 0; j<10;j++)
		{
			printf("%c ",(board+(10*i+j)*sizeof(ELEM))->letter );
		}
		printf("\n");
	}
	if(board==NULL){
		//I dont know what to do
	}
	place_it_in_board("Hello", board,1);
	for(int i = 0; i<10; i++)
	{
		for(int j = 0; j<10;j++)
		{
			printf("%c ",(board+(10*i+j)*sizeof(ELEM))->letter );
		}
		printf("\n");
	}
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

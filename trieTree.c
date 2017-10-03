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
struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];
    // isEndOfWord is true if the node represents
    // end of a word
    bool isEndOfWord;
};

// Returns new trie node (initialized to NULLs)
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

void strperms(struct TrieNode * root,int *hashish,char * wsf)
{
    if(root->isEndOfWord)
        printf(wsf);
    for(int i=0;i<26;i++)
    {
        if(hashish[i])
        {
            hashish[i]--;
            for(int j=0;wsf[j]!='\0';j++);
            wsf[j]=hashish[i];
            wsf[j+1]='\0';
            strperms(root->children[i],hashish,wsf);
            wsf[j]='\0';
            hashish[i]++;

        }
    }
}


void generate_words(struct TrieNode * root, char s[])
{
    int hashish[26];
    char wsf[100];
    strcpy()
    for(int i=0;i<26;i++)
        hashish[i]=0;
    for(int i=0;s[i]!='\0';i++)
        hashish[s[i]-'a']++;




}



// Driver
int main()
{
//    int count=0;
    struct TrieNode *root = getNode();
    insert_all_nodes(root);
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
    generate_words(root,"poop");
}



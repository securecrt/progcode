#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define OK 1
#define ERROR 0

typedef int Status;

typedef struct Node
{
    char data;
    struct Node *children[26];
    Status end;
} Trie, *TriePtr;

void Init(TriePtr *T)
{
    int i;
    (*T) = (TriePtr)malloc(sizeof(Trie));
    for (i = 0; i < 26; i++)
        (*T)->children[i] = NULL;
    (*T)->data = '/';
    (*T)->end = false;
}

void Insert(TriePtr T, char *str)
{

    int index, i;
    char c;

    while (c = *str++)
    {
        index = c - 'a';
        if (T->children[index] == NULL)
        {
            TriePtr Node;
            Node = (TriePtr)malloc(sizeof(Trie));
            Node->data = c;
            Node->end = false;
            for (i = 0; i < 26; i++)
                Node->children[i] = NULL;
            T->children[index] = Node;
        }

        T = T->children[index];
    }

    T->end = true;
}

Status Search(TriePtr T, char *str)
{

    int index;
    char c;

    while (c = *str++)
    {
        index = c - 'a';
        if (T->children[index] == NULL)
        {
            return false;
        }

        T = T->children[index];
    }

    if (T->end)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main(int argc, char const *argv[])
{
    TriePtr T;
    Init(&T);
    char *str = "hello";
    char *str2 = "hi";
    char *str3 = "helloworld";
    Insert(T, str3);
    Insert(T, str2);
    Insert(T, str);
    printf("str is search %d\n", Search(T, str));
    printf("str2 is search %d\n", Search(T, str2));
    printf("str2 is search %d\n", Search(T, str3));
    return 0;
}
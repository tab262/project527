// project527.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <dos.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <tchar.h>


char str[100];
enum {NOT_FOUND=0,FOUND};
static char *ptr;
const char *del;


#define SIZE 991


struct Word{
	char* c;
	int count;
};


struct Node{
	char* word;
	int count;
	struct Node* next;
	int init;
};


struct Document{
	int docID;
	char* title;
	int wordCount;
	int uniqueWordCount;
};


struct Table{
	int capacity;
	int total;
	int unique;
	Node* nodes;
};

struct Collection{
	int numberOfDocs;
	Document* docs;
};


// Host declarations
char* getDocCharArray(char* fileName);
char *mystrtok(char* string,const char *delim);
void runDelimExample();
void printIndividualWords(char* str);

//void printWords(Stack* S,int* table);
int hash (const char* word);
void getList(char* str, Table* table);
Table* createTable(int capacity);



int _tmain(int argc, _TCHAR* argv[])
{
	char* fileNames[3] =	{"C:\\Users\\gaddis\\Documents\\Visual Studio 2010\\Projects\\project527\\project527\\ReadMe.txt",
							 "C:\\Users\\gaddis\\Documents\\Visual Studio 2010\\Projects\\project527\\project527\\text\\aPrincessOfMars.txt",
							 "C:\\Users\\gaddis\\Documents\\Visual Studio 2010\\Projects\\project527\\project527\\text\\aScientistRises.txt"
							};
	
	Collection* collection = (Collection*)malloc(2*sizeof(Document));

	char* c = getDocCharArray(fileNames[0]);
	
	Table* table = createTable(1000);
	

	getList(c,table);
	

	for(int i = 0; i < SIZE; i++){
		if(table->nodes[i].init == 0){
			//printf("Index %d has not been initialized\n",i);
		}else{
			printf("Index %d has been initialized with word '%s' with a count of %d\n",i,table->nodes[i].word,table->nodes[i].count);
		}

	}



	std::getchar();
	return 0;
}

Table* createTable(int cap)
{
	Table* table = (Table*)malloc(sizeof(Table));
	table->capacity = cap;
	table->total = 0;
	table->unique = 0;
	table->nodes = (Node*)malloc(cap*sizeof(Node));

	int i;
	for(i = 0; i < cap; i++){
		table->nodes[i].init = 0;
	}

	return table;
}

void getList(char* str, Table* table)
{
	long int i,j,k,start,end,length,index;
	i = 0;
	while(str[i] !=NULL){
		start = i;
		while(str[i] != ' ' && str[i] != '\n'){
			i++;
		}
		end = i;
		length = end - start;
		char* w = (char*)malloc(length);
		if(length > 3){
			for(k = start,j=0; k < end;k++,j++){
				w[j] = str[k];
			}
			w[length] = '\0';
			index = hash(w);
			//printf("%s: %d\n",w,index);
			
			//hash table entry is empty
			if((table->nodes[index].init) == 0){
				
				table->nodes[index].word = w;
				table->nodes[index].count = 1;
				table->nodes[index].init = 1;
				table->nodes[index].next = NULL;
				//entry is filled, but with same word	
			}else{
				char* w2 = table->nodes[index].word;
				int result = strcmp(w,w2);
				if(result){
					printf("Collision for %s and %s as they have hashes %d and %d\n",w,w2, hash(w),hash(w2));
				}else{
					printf("Same for %s and % s\n", w,w2);
					table->nodes[index].count++;
				}
			}
			/*}else if(strcmp(w,table->nodes[index].word.c)){
				table->nodes[index].word.count++;
			//COLLISION - create new node (for now just will take one step)
			}else{
				printf("COLLISION for word %s at index %d\n",w,index);
				Node* n = (Node*)malloc(sizeof(Node));
				Word* word = (Word*)malloc(sizeof(word));
				n->word.c = w;
				n->word.count = 1;
				n->init = 1;
				n->next = NULL;
				table->nodes[index].next = n;
			}*/
		}
		i++;
	}
}



int hash (const char* word)
{
    int hash = 0;
    int n;
    for (int i = 0; word[i] != '\0'; i++)
    {
        // alphabet case
        if(isalpha(word[i]))
            n = word [i] - 'a' + 1;

        // comma case
        else
            n = 27;

        hash = ((hash << 3) + n) % SIZE;
    }
    return hash;
}


/*
void printIndividualWords(char* str){
	int start,end,k,length;
	int i = 0;
	int numWords = 0;
	while(str[i] != NULL){
		start = i;
		while(str[i] != ' ' && str[i] != '\n'){
			i++;
		}
		end = i;
		length = end - start;
		
		if(length > 2){
			for(k = start; k < end;k++){
				printf("%c",str[k]);
			}	
			printf(" -- %d", length);
			printf("\n");
			numWords ++;
		}
		i++;
	}
	
	printf("The total number of words is: %d\n", numWords);
}
*/

void runDelimExample()
{
	int i;
	    char *p_str,*token;
    char delim[10];

    printf("\n Enter a string to tokenize: ");
    scanf("%[^\n]",str);
    
    getchar();
    printf("\n Enter a delimiter : ");
    scanf("%[^\n]",delim);

    for (i = 1, p_str = str; ; i++, p_str = NULL)
    {
        token = mystrtok(p_str,delim);
        if (token == NULL)
            break;
        printf("\n%d: %s",i,token);
    }

}


char *mystrtok(char* string,const char *delim)
{
    int j,flag=NOT_FOUND;
    char *p;
    if(string != NULL)
    {
        ptr=string;
        p=string;
    }
    else
    {
        if(*ptr == '\0')
            return NULL;

        p=ptr;
    }

    while(*ptr != '\0')
    {
        del=delim;
        while(*del != '\0')
        {
            if(*ptr == *del)
            {
                if(ptr == p)
                {
                    p++;
                    ptr++;
                }
                else
                {
                    *ptr='\0';
                    ptr++;

                    return p;
                }
            }
            else
            {
                del++;
            }
        }
        ptr++;
    }
    return p;
}


char* getDocCharArray(char* fileName)
{
	FILE *fr;
	fr = fopen(fileName,"r");
	struct stat st;
	stat(fileName, &st);
	int size = st.st_size;
	printf("The size of the file is %d bytes\n",size);
	char* c = (char*)malloc(size*sizeof(char));
	char* c2 = (char*)malloc(size*sizeof(char));
	fread(c,size,1,fr);
	
	int i = 0;
	while(c[i] != 0){
		if((int)c[i] >= 92 && (int)c[i]<= 122){
			c2[i] = c[i];
			i++;
		}else if((int)c[i] >= 65 && (int)c[i] <= 90){
			c2[i] = (char)((int)c[i] + 32);
			i++;
		}else{
			c2[i] = ' ';
			i++;
		}
	}


	return c2;
}


/*
Stack* S = createStack(100000);
	getList(c,S);
	
	Word word1 = top(S);
	printf("%s\n",word1.c);
	int table[1000] = {0};
	Word table2[2000];
	printWords(S, table);

	int total = 0;
	int unique = 0;
	for(int i = 0; i <= SIZE;i++){
		total += table[i];
		if(table[i] != 0){
			unique++;
		}
		//printf("%d: %d\n",i,table[i]);	
	}

	printf("The total number of words is %d, while the total number of unique words is %d\n",total,unique);

	char* y = "project";
	int yy = hash(y);
	printf("The word 'project' appears %d times with the hash %d\n", table[yy],yy); 

	printf("\n");
*/


/*
Stack * createStack(int maxElements){
	Stack * S;
	S = (Stack *)malloc(sizeof(Stack));
	S->elements = (Word *)malloc(sizeof(Word)*maxElements);
	S->size = 0;
	S->capacity = maxElements;
	return S;
}


void printWords(Stack* S, int* table)
{
	int limit = S->size;
	int i;
	Word word;
	for(i = 0; i < limit;i++){
		word = top(S);
		pop(S);
		table[hash(word.c)]++;
		printf("%s -- %d\n",word.c, hash(word.c));
	}
}


void pop(Stack *S)
{
	if(S->size==0){
		printf("Stack is empty\n");
		return;
	}else{
		S->size--;
	}
	return;
}




Word top(Stack *S)
{
	if(S->size == 0){
		printf("Stack is empty\n");
		std::getchar();
		exit(0);
	}

	return S->elements[S->size-1];
}


void push(Stack *S, Word element)
{
	if(S->size == S->capacity){
		printf("Stack is full\n");
	}else{
		S->elements[S->size++] = element;
	}
}




void getList(char* str, Stack* S)
{
	long int i,j,k,start,end,length;
	i = 0;
	int numWords = 0;
	while(str[i] !=NULL){
		start = i;
		while(str[i] != ' ' && str[i] != '\n'){
			i++;
		}
		end = i;
		length = end - start;
		char* w = (char*)malloc(length);
		if(length > 2){
			for(k = start,j=0; k < end;k++,j++){
				w[j] = str[k];
			}
			w[length] = '\0';
			numWords++;
			Word word;
			word.c = w;
			push(S,word);
		}
		i++;
	}
}

*/
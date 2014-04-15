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


struct Node{
	char* word;
	int count;
	struct Node* next;
	int init;
};

struct Table{
	int capacity;
	int total;
	int unique;
	struct Node* nodes;
};

struct Document{
	long size;
	int docID;
	char* title;
	char* text;
	int wordCount;
	int uniqueWordCount;
	struct Table* t;
};



//Host declarations
Document* getDocCharArray(char* fileName);
Table* createTable(int cap);


int main(int argc, _TCHAR* argv[])
{
	char* fileNames[3] =	{"C:\\Users\\gaddis\\Documents\\Visual Studio 2010\\Projects\\project527\\project527\\ReadMe.txt",
							 "C:\\Users\\gaddis\\Documents\\Visual Studio 2010\\Projects\\project527\\project527\\text\\aPrincessOfMars.txt",
							 "C:\\Users\\gaddis\\Documents\\Visual Studio 2010\\Projects\\project527\\project527\\text\\aScientistRises.txt"
								};


	Document* d = getDocCharArray(fileNames[0]);

	printf("The size of document is %ld bytes\n",d->size);
	
	Table* t = createTable(1000);

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

Document* getDocCharArray(char* fileName)
{
	Document* doc = (Document*)malloc(sizeof(doc));
	FILE *fr;
	fr = fopen(fileName,"r");
	
	// Get file size in terms of bytes
	struct stat st;
	stat(fileName, &st);
	long int size = st.st_size;
	doc->size = size;
	//printf("The size of the file is %d bytes\n",size);
	
	// Allocate space
	char* c = (char*)malloc(size*sizeof(char));
	char* c2 = (char*)malloc(size*sizeof(char));
	
	// Read entirety of text file into c
	fread(c,size,1,fr);
	
	// Remove nonalpha as well and go from upper to lower
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

	doc->text = c2;
	
	free(c);
	
	return doc;
}